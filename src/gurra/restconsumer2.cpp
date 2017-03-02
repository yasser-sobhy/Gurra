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

QByteArray RestConsumer2::host(){
    return m_host;
}

void RestConsumer2::setHost(QByteArray host){
    m_host = host;
    hostChanged(host);
}

void RestConsumer2::addHeader(QByteArray key, QByteArray value){
    headers.insert(key, value);
}

void RestConsumer2::addHeaders(QByteArray headers)
{
    if(!headers.isEmpty()) {
        QByteArrayList list = headers.split(',');

        for(QByteArray str : list)
        {
            QByteArrayList h = str.split('=');
            if(h.size() == 2) this->headers.insert(h[0].trimmed(), h[1].trimmed());
        }
    }
}

void RestConsumer2::setQueryParams(QUrl &url, QString params)
{
    QUrlQuery query;

    if(!params.isEmpty()) {
        QStringList list = params.split(',');

        for(QString str : list)
        {
            QStringList q = str.split('=');
            if(q.size() == 2) query.addQueryItem(q[0].trimmed(), q[1].trimmed());
        }

        url.setQuery(query);
    }
}

void RestConsumer2::setHeaders(QNetworkRequest &request)
{
    for(QByteArray h : headers.keys()){
        request.setRawHeader(h, headers.value(h));
    }
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

    switch (reply->operation()){

    case QNetworkAccessManager::GetOperation:

        if(rest->_cache) {
            qDebug() << "[][][][ Caching" << reply->url().toString();
            this->cache.cache(rest->_cacheCategory, reply->url().toString(), data, rest->_cacheTtl);
        }

        rest->ready(data);
        rests.remove(reply);
        break;
    case QNetworkAccessManager::PostOperation:

        rest->posted(data);
        rests.remove(reply);
        break;
    case QNetworkAccessManager::PutOperation:

        this->cache.remove(rest->_cacheCategory, reply->url().toString());
        rest->updated(data);
        rests.remove(reply);
        break;
    case QNetworkAccessManager::DeleteOperation:

        this->cache.remove(rest->_cacheCategory, reply->url().toString());
        rests[reply]->deleted(data);
        rests.remove(reply);
        break;
    }

    reply->deleteLater();
}

void RestConsumer2::removeRest(Rest *rest){
    rests.remove(rest->reply);
}

void RestConsumer2::get(Rest *rest, QByteArray resource, QString query){

    QUrl url( m_host + resource );

    setQueryParams(url, query);

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

    qDebug() << "GET" << url.toString();
    QNetworkReply *replay = networkAccessManager.get(request);

    connect(rest, &Rest::destroying, this, &RestConsumer2::removeRest);
    rest->reply = replay;
    rests.insert(replay, rest);
}

void RestConsumer2::post(Rest *rest, QByteArray resource, QByteArray data, QString query){

    QUrl url(m_host + resource);

    setQueryParams(url, query);

    QNetworkRequest request (url);
    setHeaders(request);

    qDebug() << "POST" << url.toString();
    QNetworkReply *replay = networkAccessManager.post(request, data);

    connect(rest, &Rest::destroying, this, &RestConsumer2::removeRest);
    rest->reply = replay;
    rests.insert(replay, rest);
}

void RestConsumer2::put(Rest *rest, QByteArray resource, QByteArray data, QString query){

    QUrl url(m_host + resource);

    setQueryParams(url, query);

    QNetworkRequest request (url);
    setHeaders(request);

    qDebug() << "PUT" << url.toString();
    QNetworkReply *replay = networkAccessManager.put(request, data);

    connect(rest, &Rest::destroying, this, &RestConsumer2::removeRest);
    rest->reply = replay;
    rests.insert(replay, rest);
}

void RestConsumer2::remove(Rest *rest, QByteArray resource, QString query){

    QUrl url(m_host + resource);

    setQueryParams(url, query);

    QNetworkRequest request (url);
    setHeaders(request);

    qDebug() << "DELETE" << url.toString();
    QNetworkReply *replay = networkAccessManager.deleteResource(request);

    connect(rest, &Rest::destroying, this, &RestConsumer2::removeRest);
    rest->reply = replay;
    rests.insert(replay, rest);
}
