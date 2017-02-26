#ifndef RESTCONSUMER3_H
#define RESTCONSUMER3_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QHttpPart>
#include <QFile>
#include <QFileInfo>

#include "mimetypes.h"

namespace Gurra {

class RestUploader;

class RestConsumer3 : public QObject
{
    Q_OBJECT

public:
    RestConsumer3();
    ~RestConsumer3();

public slots:
    void upload(RestUploader *rest, QByteArray resource, QString file, bool put);
    void upload(RestUploader *rest, QByteArray resource, QString file, QByteArray data, bool put);

protected:
    // add any service-specific headers
    virtual void addHeaders(QNetworkRequest &request);

private slots:
    void parseNetworkResponse(QNetworkReply *reply );

private:
    void setHeaders(QNetworkRequest &request);
    void setQueryParams(QUrl &url);
    void authenticate(QNetworkRequest &request);

    MimeTypes mimeTypes;

    QByteArray idempotencyKey, idempotencyKeyString = "Idempotency-Key";
    QByteArray from, to, fromString = "from", toString = "to";
    QByteArray username, password, token, queryParams;
    QByteArray accept = "application/json", contentType = "application/json";

    QByteArray host = "http://saooom.com:8080";
    //QByteArray host = "http://localhost:8080";

    QNetworkAccessManager networkAccessManager;
    QHash<QNetworkReply* ,RestUploader *> rests;
};

}

#endif // RESTCONSUMER3_H
