#include "restconsumer2.h"
#include "rest.h"

using namespace Gurra;

RestConsumer2::RestConsumer2()
{
    connect(&networkAccessManager, &QNetworkAccessManager::finished,
            this, &RestConsumer2::parseNetworkResponse);
}

RestConsumer2::~RestConsumer2()
{

}

void RestConsumer2::setHeaders(QNetworkRequest &request){

    request.setRawHeader(QByteArray("Accept"), accept);
    request.setRawHeader(QByteArray("Content-Type"), contentType );

    // for services which support this
    if(!idempotencyKey.isEmpty())
        request.setRawHeader(QByteArray(idempotencyKeyString), idempotencyKey );

    addHeaders(request);
}

void RestConsumer2::authenticate(QNetworkRequest &request){

    if(!username.isEmpty() && !password.isEmpty()){

        QByteArray data = username + ":" + password;
        request.setRawHeader("Authorization", "Basic " + data.toBase64());
    }
    else if (!token.isEmpty()){
        request.setRawHeader("Authorization", "Bearer " + token);
    }
}

void RestConsumer2::setQueryParams(QUrl &url)
{
    QUrlQuery query;

    if(!from.isEmpty() && !to.isEmpty()){
        query.addQueryItem(fromString, from);
        query.addQueryItem(toString, to);
    }

    // example queryParams: from=1, to=10, date=10/8/2016
    if(!queryParams.isEmpty()) {
        QList<QByteArray> list = queryParams.split(',');

        for(QByteArray qstr : list)
        {
            QList<QByteArray> q = qstr.split('=');
            if(q.size() == 2) query.addQueryItem(q[0].trimmed(),q[1].trimmed());
        }
    }

    url.setQuery(query);
}

void RestConsumer2::parseNetworkResponse(QNetworkReply *reply){

    // get Rest who made the request
    Rest *rest = rests.value(reply);
    if(!rest) return;

    QByteArray data = reply->readAll();

    if(reply->error() != QNetworkReply::NoError)
    {
        // usually server returns an error object describing the error
        // if no error object returned, the means there is error connecting to server
        if(data.isEmpty()){
            rest->networkError(reply->error());
            rests.remove(reply);
        }
        else{
            rest->serverError(data);
            rests.remove(reply);
        }

        return;
    }

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    // usually server returns an error in json doc with more details about error
    // that can be parsed from data
    if(statusCode != 200) {
        rest->serverError(data);
        rests.remove(reply);
        return;
    }

    QJsonDocument json;
    QJsonParseError error;
    json = QJsonDocument::fromJson(data, &error);

    if(error.error == QJsonParseError::NoError)
    {
        // if server return list of resources, parse it and emit listReady signal
        if(isList(reply, json)){
            parseList(reply, json);
            return;
        }
    }

    switch (reply->operation()){

    case QNetworkAccessManager::GetOperation:

        if(rest->_cache) {
            qDebug() << "[][][][ Caching" << reply->url().toString();
            this->cache.cache(rest->_cacheCategory, reply->url().toString(), data, rest->_cacheTtl);
        }

        rest->ready(data); //idGet
        rests.remove(reply);
        break;
    case QNetworkAccessManager::PostOperation:

        rest->posted(data); //idPost
        rests.remove(reply);
        break;
    case QNetworkAccessManager::PutOperation:

        this->cache.remove(rest->_cacheCategory, reply->url().toString());
        rest->updated(data); //idPut
        rests.remove(reply);
        break;
    case QNetworkAccessManager::DeleteOperation:

        this->cache.remove(rest->_cacheCategory, reply->url().toString());
        rests[reply]->deleted(data); //idDelete
        rests.remove(reply);
        break;
    }

    reply->deleteLater();
}

void RestConsumer2::removeRest(Rest *rest){
    rests.remove(rest->reply);
}

void RestConsumer2::get(Rest *rest, QByteArray resource, int from, int to, QByteArray addQuery){

    QUrl url( host + resource );

    this->from = QByteArray::number(from);
    this->to = QByteArray::number(to);
    queryParams = addQuery;
    setQueryParams(url);

    if(rest->_cache) {
        QByteArray c = this->cache.get(rest->_cacheCategory, url.toString());

        if(!c.isEmpty()) {
            qDebug() << "Cache found for" << url.toString();
            rest->ready(c);
            return;
        }
    }

    QNetworkRequest request (url);
    setHeaders(request);
    authenticate(request);

    qDebug() << "GET" << url.toString();
    QNetworkReply *replay = networkAccessManager.get(request);

    connect(rest, &Rest::destroying, this, &RestConsumer2::removeRest);
    rest->reply = replay;
    rests.insert(replay, rest);
}

void RestConsumer2::post(Rest *rest, QByteArray resource, QByteArray data, QByteArray addQuery){

    QUrl url(host + resource);

    queryParams = addQuery;
    setQueryParams(url);

    QNetworkRequest request (url);
    setHeaders(request);
    authenticate(request);

    qDebug() << "POST" << url.toString();
    QNetworkReply *replay = networkAccessManager.post(request, data);
    rests.insert(replay, rest);
}

void RestConsumer2::idGet(Rest *rest, QByteArray resource, QByteArray addQuery){

    QUrl url(host + resource);

    queryParams = addQuery;
    setQueryParams(url);

    QNetworkRequest request (url);
    setHeaders(request);
    authenticate(request);

    qDebug() << "idGET" << url.toString();
    QNetworkReply *replay = networkAccessManager.get(request);

    // remove this rest if it gets deleted before receiving network response
    connect(rest, &Rest::destroying, this, &RestConsumer2::removeRest);
    rest->reply = replay;
    rests.insert(replay, rest);
}

void RestConsumer2::idPut(Rest *rest, QByteArray resource, QByteArray data, QByteArray addQuery){

    QUrl url(host + resource);

    queryParams = addQuery;
    setQueryParams(url);

    QNetworkRequest request (url);
    setHeaders(request);
    authenticate(request);

    QNetworkReply *replay = networkAccessManager.put(request, data);
    rests.insert(replay, rest);
}

void RestConsumer2::idDelete(Rest *rest, QByteArray resource, QByteArray addQuery){

    QUrl url(host + resource);

    queryParams = addQuery;
    setQueryParams(url);

    QNetworkRequest request (url);
    setHeaders(request);
    authenticate(request);

    QNetworkReply *replay = networkAccessManager.deleteResource(request);
    rests.insert(replay, rest);
}

bool RestConsumer2::isList(QNetworkReply *reply, QJsonDocument &json)
{
    for (QString key : json.object().keys())
    {
        if( key != "links") {
            if(json.object().value(key).isArray()){
                return true;
            }
        }
    }

    return false;
}

void RestConsumer2::parseList(QNetworkReply *reply, QJsonDocument &json){

    QJsonArray array;

    // skip links value, and get the array value
    for (QString key : json.object().keys())
    {
        if(key != "links") array = json.object().value(key).toArray();
    }

    QStringList list;
    QStringListModel *model = new QStringListModel();

    // convert every item to a standalone json object
    for( int i =0; i < array.size(); i++){

        QByteArray obj = QJsonDocument(array.at(i).toObject()).toJson();

        list.append(obj);
    }

    model->setStringList(list);
    rests[reply]->listReady(QVariant::fromValue(model));
    rests.remove(reply);
}

void RestConsumer2::addHeaders(QNetworkRequest &request)
{
    return;
}
