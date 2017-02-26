#ifndef RESTCONSUMER_H
#define RESTCONSUMER_H

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

namespace Gurra {


class RestConsumer : public QObject
{
    Q_OBJECT

public:
    RestConsumer();
    ~RestConsumer();

public slots:
    void get(QByteArray resource,  int from = 0, int to = 9, QByteArray addQuery = "");
    void post(QByteArray resource, QByteArray data, QByteArray addQuery = "");

    void idGet(QByteArray resource, QByteArray addQuery = "");
    void idPut(QByteArray resource, QByteArray data, QByteArray addQuery = "");
    void idDelete(QByteArray resource, QByteArray addQuery = "");

    void upload(QByteArray resource, QUrl file, bool put);
    void upload(QByteArray resource, QUrl file, QByteArray data, bool put);

signals:

    void ready(const QByteArray rawData); //idGet
    void listReady(const QVariant rawDataList); //get
    void rootReady(const QVariant rawDataList); //Get, service root

    void posted(const QByteArray rawData); // post
    void updated(const QByteArray rawData); // idPut
    void deleted(const QByteArray rawData); // idDelete

    void uploaded(const QByteArray rawData); // post

    void count(int count); // count

    void networkError( QNetworkReply::NetworkError err );
    void serverError(const QByteArray err);
    void badConentError();

    // errors issued by RestConsumer before sending a request
    void error(const QByteArray err);

protected:
    // checks whether the returned result is a list of resurces or not
    virtual bool isList(QNetworkReply *reply, QJsonDocument &json);

    // if returned result is list, parse it and emit signal
    virtual void parseList(QNetworkReply *reply, QJsonDocument &json);

    // checks whether the returned result is the root links of the service
    virtual bool isRoot(QNetworkReply *reply, QJsonDocument &json);

    // if returned result is the service root, parse it and emit signal
    virtual void parseRoot(QNetworkReply *reply, QJsonDocument &json);

    // if couldn't parse json returned from server, try processing it further for service-specific needs
    // e.g. in AnaCloud there is count function which returns the count of resources in a certain url
    // this count function returns a number, which will json fail to parse, and here comes the rule
    // of this function to process the returned result and determine if it's an int or not

    // this function need to return true if successfully parsed data and got a result out of it, otherwise false
    virtual bool processData(QNetworkReply *reply, const QByteArray &data);

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
};

}
#endif // RESTCONSUMER_H
