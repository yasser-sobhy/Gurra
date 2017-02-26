#include "restconsumer.h"

using namespace Gurra;

RestConsumer::RestConsumer()
{
    connect(&networkAccessManager, &QNetworkAccessManager::finished,
            this, &RestConsumer::parseNetworkResponse);
}

RestConsumer::~RestConsumer()
{

}

void RestConsumer::setHeaders(QNetworkRequest &request){

    request.setRawHeader(QByteArray("Accept"), accept);
    request.setRawHeader(QByteArray("Content-Type"), contentType );

    // for services which support this
    if(!idempotencyKey.isEmpty())
        request.setRawHeader(QByteArray(idempotencyKeyString), idempotencyKey );

    addHeaders(request);
}

void RestConsumer::authenticate(QNetworkRequest &request){

    if(!username.isEmpty() && !password.isEmpty()){

        QByteArray data = username + ":" + password;
        request.setRawHeader("Authorization", "Basic " + data.toBase64());
    }
    else if (!token.isEmpty()){
        request.setRawHeader("Authorization", "Bearer " + token);
    }
}

void RestConsumer::setQueryParams(QUrl &url)
{
    QUrlQuery query;

    if(!from.isEmpty() && !to.isEmpty()){
        query.addQueryItem(fromString, from);
        query.addQueryItem(toString, to);
    }

    // example queryParams: from=1, to=10, date=10/8/2016
    if(!queryParams.isEmpty()) {
        QList<QByteArray> list = queryParams.split(',');

        if(list.size() % 2 == 0){
            for(QByteArray qstr : list)
            {
                QList<QByteArray> q = qstr.split('=');
                query.addQueryItem(q[0].trimmed(),q[1].trimmed());
            }
        }
    }

    url.setQuery(query);
}

void RestConsumer::parseNetworkResponse(QNetworkReply *reply){

    QByteArray data = reply->readAll();
    reply->deleteLater();

    if(reply->error() != QNetworkReply::NoError)
    {
        // usually server returns an error object describing the error
        // if no error object returned, the means there is error connecting to server
        if(data.isEmpty())
            emit networkError(reply->error());
        else
            emit serverError(data);

        return;
    }

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    // usually server returns an error in json doc with more details about error
    // that can be parsed from data
    if(statusCode != 200) {

        emit serverError(data);
        return;
    }

    QJsonDocument json;
    QJsonParseError error;
    json = QJsonDocument::fromJson(data, &error);

    if(error.error == QJsonParseError::NoError)
    {
        // if result is the root links of the service, parse it and emit rootReady signal
        if(isRoot(reply, json)){
            parseRoot(reply, json);
            return;
        }

        // if server return list of resources, parse it and emit listReady signal
        if(isList(reply, json)){
            parseList(reply, json);
            return;
        }

        switch (reply->operation()){
        case QNetworkAccessManager::GetOperation:
            emit ready(data); //idGet
            break;
        case QNetworkAccessManager::PostOperation:
            emit posted(data); //idPost
            break;
        case QNetworkAccessManager::PutOperation:
            emit updated(data); //idPut
            break;
        case QNetworkAccessManager::DeleteOperation:
            emit deleted(data); //idDelete
            break;
        }
    }
    else if (processData(reply, data)){
        return;
    }

    //normally object returned from the server is guaranteed to be valid,
    //but in case of any strange behavior emit error signal
    else emit badConentError(); // error parsing json document, corrupted content
}

void RestConsumer::get(QByteArray resource, int from, int to, QByteArray addQuery){

    QUrl url( host + resource );

    this->from = QByteArray::number(from);
    this->to = QByteArray::number(to);
    queryParams = addQuery;
    setQueryParams(url);

    QNetworkRequest request (url);
    setHeaders(request);
    authenticate(request);

    qDebug() << "GET" << url.toString();
    networkAccessManager.get(request);
}

void RestConsumer::post(QByteArray resource, QByteArray data, QByteArray addQuery){

    QUrl url(host + resource);

    queryParams = addQuery;
    setQueryParams(url);

    QNetworkRequest request (url);
    setHeaders(request);
    authenticate(request);

    qDebug() << "POST" << url.toString();
    networkAccessManager.post(request, data);
}

void RestConsumer::idGet(QByteArray resource, QByteArray addQuery){

    QUrl url(host + resource);

    queryParams = addQuery;
    setQueryParams(url);

    QNetworkRequest request (url);
    setHeaders(request);
    authenticate(request);

    qDebug() << "idGET" << url.toString();
    networkAccessManager.get(request);
}

void RestConsumer::idPut(QByteArray resource, QByteArray data, QByteArray addQuery){

    QUrl url(host + resource);

    queryParams = addQuery;
    setQueryParams(url);

    QNetworkRequest request (url);
    setHeaders(request);
    authenticate(request);

    networkAccessManager.put(request, data);
}

void RestConsumer::idDelete(QByteArray resource, QByteArray addQuery){

    QUrl url(host + resource);

    queryParams = addQuery;
    setQueryParams(url);

    QNetworkRequest request (url);
    setHeaders(request);
    authenticate(request);

    networkAccessManager.deleteResource(request);
}

void RestConsumer::upload(QByteArray resource, QUrl file, bool put)
{
    upload(resource, file, "", put);
}

void RestConsumer::upload(QByteArray resource, QUrl file, QByteArray data, bool put)
{
    QString filename = file.toString(QUrl::PreferLocalFile);

    qDebug() << "Uploading" << filename;

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    multiPart->setBoundary("boundary_.oOo._56354654654654321768987465413574634354658");

    if(!data.isEmpty()){
        QHttpPart textPart;
        textPart.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
        textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"text\""));
        textPart.setBody(data);
        multiPart->append(textPart);
    }

    if(!filename.isEmpty()){

        QFileInfo info(filename);

        QHttpPart filePart;
        qDebug() << "info.suffix" << mimeTypes.type(info.suffix());
        filePart.setHeader(QNetworkRequest::ContentTypeHeader, mimeTypes.type(info.suffix()));
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uploadedfile\"; filename=\""+ info.fileName() + "\""));

        QFile *file = new QFile(filename);

        if(!file->open(QIODevice::ReadOnly))
        {
            emit error("upload file couldn't be opened");
            delete file;
            return;
        }

        filePart.setBodyDevice(file);
        file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

        multiPart->append(filePart);
    }

    QUrl url(host + resource);
    setQueryParams(url);

    QNetworkRequest request (url);

    request.setRawHeader(QByteArray("Accept"), accept);
    request.setRawHeader(QByteArray("Content-Type"), "multipart/form-data; boundary=boundary_.oOo._56354654654654321768987465413574634354658" );

    authenticate(request);

    if(put)
        networkAccessManager.put(request, multiPart);
    else
        networkAccessManager.post(request, multiPart);
}

bool RestConsumer::isList(QNetworkReply *reply, QJsonDocument &json)
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

void RestConsumer::parseList(QNetworkReply *reply, QJsonDocument &json){

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
    listReady(QVariant::fromValue(model));
}

bool RestConsumer::isRoot(QNetworkReply *reply, QJsonDocument &json)
{
    // root links of the service, this is how AnaCloud returns the root links of the service
    // if object contains links and version, so it's the root of the service
    if(json.object().size() == 2 && json.object().keys().at(0) == "links" && json.object().keys().at(1) == "version")
    {
        return true;
    }

    return false;
}

void RestConsumer::parseRoot(QNetworkReply *reply, QJsonDocument &json){

    QStringList list;
    QStringListModel *model = new QStringListModel();

    for (QString key : json.object().keys())
    {
        QJsonObject objectName;
        objectName.insert("resourceName", QJsonValue(key));

        QJsonArray array = json.object().value(key).toArray();
        array.insert(0, QJsonValue(objectName));

        QByteArray obj = QJsonDocument(array).toJson();

        list.append(obj);
    }

    model->setStringList(list);

    rootReady(QVariant::fromValue(model));
}

bool RestConsumer::processData(QNetworkReply *reply, const QByteArray &data){

    // no object returned in DELETE operation, by some services, only 200 OK status code
    if (data.isEmpty() && reply->operation() == QNetworkAccessManager::DeleteOperation){
        emit deleted(""); //idDelete
        return true;
    }
    // try int value for count, AnaCloud style
    else if (reply->operation() == QNetworkAccessManager::GetOperation)
    {
        bool countOK;

        int cnt = data.toInt(&countOK);
        if(countOK) emit count(cnt);

        return true;
    }
    else if (!data.isEmpty() && reply->operation() == QNetworkAccessManager::PostOperation)
    {
        emit uploaded(data);
    }

    return false;
}

void RestConsumer::addHeaders(QNetworkRequest &request)
{
    return;
}
