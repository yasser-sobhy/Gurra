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

void RestConsumer3::setHeaders(QNetworkRequest &request){

    request.setRawHeader(QByteArray("Accept"), accept);
    request.setRawHeader(QByteArray("Content-Type"), contentType );

    // for services which support this
    if(!idempotencyKey.isEmpty())
        request.setRawHeader(QByteArray(idempotencyKeyString), idempotencyKey );

    addHeaders(request);
}

void RestConsumer3::authenticate(QNetworkRequest &request){

    if(!username.isEmpty() && !password.isEmpty()){

        QByteArray data = username + ":" + password;
        request.setRawHeader("Authorization", "Basic " + data.toBase64());
    }
    else if (!token.isEmpty()){
        request.setRawHeader("Authorization", "Bearer " + token);
    }
}

void RestConsumer3::setQueryParams(QUrl &url)
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
            qDebug() << "upload file couldn't be opened";
            rest->error("upload file couldn't be opened");
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

void RestConsumer3::addHeaders(QNetworkRequest &request)
{
    return;
}
