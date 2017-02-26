#ifndef RESTMODEL_H
#define RESTMODEL_H

#include <QObject>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringListModel>
#include <QHttpPart>
#include <QFile>
#include <QFileInfo>

#include "mimetypes.h"
#include "restconsumer2.h"

namespace Gurra {

class RestModel: public QObject
{
    Q_OBJECT

    friend class RestConsumer2;

public:
    RestModel();
    ~RestModel();

    Q_PROPERTY(RestConsumer2* restConsumer READ getRestConsumer WRITE setRestConsumer)
    Q_PROPERTY(bool cache READ getCache WRITE setCache)
    Q_PROPERTY(bool cacheTtl READ getCacheTtl WRITE setCacheTtl)
    Q_PROPERTY(QByteArray cacheCategory READ getCacheCategory WRITE setCacheCategory)

public slots:
    void fetch(QByteArray resource);

    void setRestConsumer(RestConsumer2 *consumer);
    RestConsumer2* getRestConsumer();

private slots:
    void listReady(const QVariant rawDataList);

signals:

    void networkError( QNetworkReply::NetworkError err );
    void serverError(const QByteArray err);
    void badConentError();

    // errors issued by RestConsumer before sending a request
    void error(const QByteArray err);

    void destroying(Rest *rest);

private:

    QStringListModel model;
    int start, index;
    int _page = 20;
    bool _cacheTtl = _30SEC;
    QByteArray _cacheCategory;
    QNetworkReply *reply = nullptr;

    RestConsumer2 *m_restConsumer = nullptr;
};

}

#endif // RESTMODEL_H
