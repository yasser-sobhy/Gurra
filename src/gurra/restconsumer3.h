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
    Q_PROPERTY(QByteArray host READ host WRITE setHost NOTIFY hostChanged)

    Q_OBJECT

public:
    RestConsumer3();
    ~RestConsumer3();

public slots:

    QByteArray host();
    void setHost(QByteArray host);

    void addHeader(QByteArray key, QByteArray value);

    void upload(RestUploader *rest, QByteArray resource, QString file, bool put);
    void upload(RestUploader *rest, QByteArray resource, QString file, QByteArray data, bool put);

signals:
    void hostChanged(QByteArray host);

private slots:
    void parseNetworkResponse(QNetworkReply *reply );

private:
    void setQueryParams(QUrl &url, QString params);
    void addHeaders(QByteArray headers);
    void setHeaders(QNetworkRequest &request);

    MimeTypes mimeTypes;

    QByteArray m_host;
    QHash<QByteArray, QByteArray> headers;

    QNetworkAccessManager networkAccessManager;
    QHash<QNetworkReply* ,RestUploader *> rests;
};

}

#endif // RESTCONSUMER3_H
