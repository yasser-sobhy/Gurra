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
    void get(QByteArray resource, QString query = "");
    void post(QByteArray resource, QByteArray data, QString query = "");

    void put(QByteArray resource, QByteArray data, QString query = "");
    void remove(QByteArray resource, QString query = "");

    void setRestConsumer(RestConsumer2 *consumer);
    RestConsumer2* getRestConsumer();

    bool getCache();
    void setCache(bool value);

    bool getCacheTtl();
    void setCacheTtl(qint64 value);

    QByteArray getCacheCategory();
    void setCacheCategory(QByteArray value);

signals:

    virtual void ready(const QByteArray rawData);

    virtual void posted(const QByteArray rawData);
    virtual void updated(const QByteArray rawData);
    virtual void deleted(const QByteArray rawData);

    virtual void networkError( QNetworkReply::NetworkError err );
    virtual void serverError(const QByteArray err);

    // errors issued by RestConsumer before sending a request
    virtual void error(const QByteArray err);
    virtual void destroying(Rest *rest);

protected:

    bool _cache = false;
    bool _cacheTtl = _30SEC;
    QByteArray _cacheCategory;
    QNetworkReply *reply = nullptr;

    RestConsumer2 *m_restConsumer = nullptr;
};

}
#endif // REST_H
