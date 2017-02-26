#ifndef REST_H
#define REST_H

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
#include "restconsumer2.h"

namespace Gurra {

class Rest : public QObject
{
    friend class RestConsumer2;

    Q_PROPERTY(RestConsumer2* restConsumer READ getRestConsumer WRITE setRestConsumer)
    Q_PROPERTY(bool cache READ getCache WRITE setCache)
    Q_PROPERTY(bool cacheTtl READ getCacheTtl WRITE setCacheTtl)
    Q_PROPERTY(QByteArray cacheCategory READ getCacheCategory WRITE setCacheCategory)

    Q_OBJECT

public:
    Rest() {}
    ~Rest();

public slots:
    void get(QByteArray resource,  int from = 0, int to = 9, QByteArray addQuery = "");
    void post(QByteArray resource, QByteArray data, QByteArray addQuery = "");

    void idGet(QByteArray resource, QByteArray addQuery = "");
    void idPut(QByteArray resource, QByteArray data, QByteArray addQuery = "");
    void idDelete(QByteArray resource, QByteArray addQuery = "");

    void setRestConsumer(RestConsumer2 *consumer);
    RestConsumer2* getRestConsumer();

    bool getCache();
    void setCache(bool value);

    bool getCacheTtl();
    void setCacheTtl(qint64 value);

    QByteArray getCacheCategory();
    void setCacheCategory(QByteArray value);

signals:

    void ready(const QByteArray rawData); //idGet
    void listReady(const QVariant rawDataList); //get

    void posted(const QByteArray rawData); // post
    void updated(const QByteArray rawData); // idPut
    void deleted(const QByteArray rawData); // idDelete

    void networkError( QNetworkReply::NetworkError err );
    void serverError(const QByteArray err);
    void badConentError();

    // errors issued by RestConsumer before sending a request
    void error(const QByteArray err);

    void destroying(Rest *rest);

private:

    bool _cache = false;
    bool _cacheTtl = _30SEC;
    QByteArray _cacheCategory;
    QNetworkReply *reply = nullptr;

    RestConsumer2 *m_restConsumer = nullptr;
};

}
#endif // REST_H
