#include "restconsumer3.h"
#include "restuploader.h"

using namespace Gurra;

RestConsumer3::RestConsumer3()
{
    connect(&networkAccessManager, &QNetworkAccessManager::finished,
            this, &RestConsumer3::parseNetworkResponse);
}

RestConsumer3::~RestConsumer3()
{

}

QByteArray RestConsumer3::host(){
    return m_host;
}

void RestConsumer3::setHost(QByteArray host){
    m_host = host;
    hostChanged(host);
}

void RestConsumer3::addHeader(QByteArray key, QByteArray value){
    headers.insert(key, value);
}

void RestConsumer3::addHeaders(QByteArray headers)
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

void RestConsumer3::setQueryParams(QUrl &url, QString params)
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
void RestConsumer3::setHeaders(QNetworkRequest &request)
{
    for(QByteArray h : headers.keys()){
        request.setRawHeader(h, headers.value(h));
    }
}


void RestConsumer3::parseNetworkResponse(QNetworkReply *reply){

    RestUploader *rest = rests.value(reply);
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

    case QNetworkAccessManager::PostOperation:
        rest->uploaded(data);
        rests.remove(reply);
        break;
    case QNetworkAccessManager::PutOperation:
        rest->uploaded(data);
        rests.remove(reply);
        break;
    }

    reply->deleteLater();
}

void RestConsumer3::upload(RestUploader *rest, QByteArray resource, QString file, bool put)
{
    upload(rest, resource, file, "", put);
}

void RestConsumer3::upload(RestUploader *rest, QByteArray resource, QString file, QByteArray data, bool put)
{
    QString filename = QUrl(file).toLocalFile();

    if(put)
        qDebug() << "Uploading" << filename << "(edit)";
    else
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
            qDebug() << "upload file couldn't be opened";
            rest->error("upload file couldn't be opened");
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

    if(put){
        QNetworkReply *replay = networkAccessManager.put(request, multiPart);
        connect(replay, &QNetworkReply::uploadProgress, rest, &RestUploader::progress);
        rests.insert(replay, rest);
    }
    else {
        QNetworkReply *replay = networkAccessManager.post(request, multiPart);
        connect(replay, &QNetworkReply::uploadProgress, rest, &RestUploader::progress);
        rests.insert(replay, rest);
    }
}
