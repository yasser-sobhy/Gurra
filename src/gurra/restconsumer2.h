#ifndef RESTCONSUMER2_H
#define RESTCONSUMER2_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QQmlListProperty>
#include <QStringListModel>
#include <QHttpPart>
#include <QFile>
#include <QFileInfo>

#include "mimetypes.h"
#include "anacache.h"

namespace Gurra {

class Rest;

class RestConsumer2 : public QObject
{
    Q_PROPERTY(QByteArray host READ host WRITE setHost NOTIFY hostChanged)

    Q_OBJECT

public:
    RestConsumer2();
    ~RestConsumer2();

public slots:

    QByteArray host();
    void setHost(QByteArray host);

    void addHeader(QByteArray key, QByteArray value);

    void get(Rest *rest, QByteArray resource, QString query = "");
    void post(Rest *rest, QByteArray resource, QByteArray data, QString query = "");

    void put(Rest *rest, QByteArray resource, QByteArray data, QString query = "");
    void remove(Rest *rest, QByteArray resource, QString query = "");

signals:
    void hostChanged(QByteArray host);

private slots:
    void parseNetworkResponse(QNetworkReply *reply );
    void removeRest(Rest *rest);

private:
    void setQueryParams(QUrl &url, QString params);
    void addHeaders(QByteArray headers);
    void setHeaders(QNetworkRequest &request);

    MimeTypes mimeTypes;

    QByteArray m_host;
    QHash<QByteArray, QByteArray> headers;

    AnaCache cache;
    QHash<QNetworkReply* ,Rest *> rests;
    QNetworkAccessManager networkAccessManager;
};

}

#endif // RESTCONSUMER2_H
