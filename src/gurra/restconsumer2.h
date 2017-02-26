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
    Q_OBJECT

public:
    RestConsumer2();
    ~RestConsumer2();

public slots:
    void get(Rest *rest, QByteArray resource,  int from = 0, int to = 9, QByteArray addQuery = "");
    void post(Rest *rest, QByteArray resource, QByteArray data, QByteArray addQuery = "");

    void idGet(Rest *rest, QByteArray resource, QByteArray addQuery = "");
    void idPut(Rest *rest, QByteArray resource, QByteArray data, QByteArray addQuery = "");
    void idDelete(Rest *rest, QByteArray resource, QByteArray addQuery = "");

protected:
    // checks whether the returned result is a list of resurces or not
    virtual bool isList(QNetworkReply *reply, QJsonDocument &json);

    // if returned result is list, parse it and emit signal
    virtual void parseList(QNetworkReply *reply, QJsonDocument &json);

    // add any service-specific headers
    virtual void addHeaders(QNetworkRequest &request);

private slots:
    void parseNetworkResponse(QNetworkReply *reply );
    void removeRest(Rest *rest);

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
    QHash<QNetworkReply* ,Rest *> rests;
    AnaCache cache;
};

}

#endif // RESTCONSUMER2_H
