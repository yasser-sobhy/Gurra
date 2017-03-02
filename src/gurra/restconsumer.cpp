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

QByteArray RestConsumer::host(){
    return m_host;
}

void RestConsumer::setHost(QByteArray host){
    m_host = host;
    hostChanged(host);
}

void RestConsumer::addHeader(QByteArray key, QByteArray value){
    headers.insert(key, value);
}

void RestConsumer::addHeaders(QByteArray headers)
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

void RestConsumer::setQueryParams(QUrl &url, QString params)
{
    QUrlQuery query;

    if(!params.isEmpty()) {
        QStringList list = params.split(',');

        for(QString str : list)
        {
            QStringList q = str.split('=');
            if(q.size() == 2) query.addQueryItem(q[0].trimmed(), q[1].trimmed());
        }
    }

    url.setQuery(query);
}

void RestConsumer::setHeaders(QNetworkRequest &request)
{
    for(QByteArray h : headers.keys())
        request.setRawHeader(h, headers.value(h));
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

    switch (reply->operation()){
    case QNetworkAccessManager::GetOperation:
        emit ready(data);
        break;
    case QNetworkAccessManager::PostOperation:
        emit posted(data);
        break;
    case QNetworkAccessManager::PutOperation:
        emit updated(data);
        break;
    case QNetworkAccessManager::DeleteOperation:
        emit deleted(data);
        break;
    }
}

void RestConsumer::get(QByteArray resource, QString query){

    QUrl url( m_host + resource );

    setQueryParams(url, query);

    QNetworkRequest request (url);
    setHeaders(request);

    qDebug() << "GET" << url.toString();
    networkAccessManager.get(request);
}

void RestConsumer::post(QByteArray resource, QByteArray data, QString query){

    QUrl url(m_host + resource);

    setQueryParams(url, query);

    QNetworkRequest request (url);
    setHeaders(request);

    qDebug() << "POST" << url.toString();
    networkAccessManager.post(request, data);
}

void RestConsumer::put(QByteArray resource, QByteArray data, QString query){

    QUrl url(m_host + resource);

    setQueryParams(url, query);

    QNetworkRequest request (url);
    setHeaders(request);

    qDebug() << "PUT" << url.toString();
    networkAccessManager.put(request, data);
}

void RestConsumer::remove(QByteArray resource, QString query){

    QUrl url(m_host + resource);

    setQueryParams(url, query);

    QNetworkRequest request (url);
    setHeaders(request);

    qDebug() << "DELETE" << url.toString();
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

    QUrl url(m_host + resource);
    setQueryParams(url, "");

    QNetworkRequest request (url);

    request.setRawHeader(QByteArray("Content-Type"), "multipart/form-data; boundary=boundary_.oOo._56354654654654321768987465413574634354658" );

    if(put)
        networkAccessManager.put(request, multiPart);
    else
        networkAccessManager.post(request, multiPart);
}
