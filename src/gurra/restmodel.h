#ifndef RESTMODEL_H
#define RESTMODEL_H

#include <QObject>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringListModel>

#include "restconsumer2.h"
#include "paginationoptions.h"

#include "rest.h"

namespace Gurra {

class RestModel: public Rest
{
    friend class RestConsumer2;

    Q_PROPERTY(QStringListModel* model READ getModel NOTIFY modelChanged)
    Q_PROPERTY(QByteArray resource READ getResource WRITE setResource NOTIFY resourceChanged)
    Q_PROPERTY(QByteArray resourceName READ getResourceName WRITE setResourceName NOTIFY resourceNameChanged)

    Q_PROPERTY(bool loading READ getLoading NOTIFY loadingChanged)
    Q_PROPERTY(bool fetching READ getFetching NOTIFY fetchingChanged)
    Q_PROPERTY(bool noInternet READ getNoInternet NOTIFY noInternetChanged)
    Q_PROPERTY(bool noContent READ getNoContent NOTIFY noContentChanged)
    Q_PROPERTY(bool noNetwork READ getNoNetwork NOTIFY noNetworkChanged)

    Q_OBJECT

public:
    RestModel();
    ~RestModel();

public slots:
    void fetch(QString query = "");
    void fetchMore();
    void reset();

    QStringListModel *getModel();
    QByteArray getResource();
    QByteArray getResourceName();
    void setResource(QByteArray resource);
    void setResourceName(QByteArray resourceName);

    bool getLoading();
    bool getFetching();
    bool getNoInternet();
    bool getNoContent();
    bool getNoNetwork();

signals:
    void modelChanged(QStringListModel* model);
    void resourceChanged(QByteArray value);
    void resourceNameChanged(QByteArray value);

    void loadingChanged(bool value);
    void fetchingChanged(bool value);
    void noInternetChanged(bool value);
    void noContentChanged(bool value);
    void noNetworkChanged(bool value);

private slots:
    virtual void ready(const QByteArray rawData);
    void p_networkError();
    void p_serverError();

private:
    void resetStatus(bool loading = false, bool fetcing = false, bool noNetwork = false, bool noContent = false, bool noInternet = false);
    bool m_loading = false;
    bool m_fetcing = false;
    bool m_noInternet = false;
    bool m_noContent = false;
    bool m_noNetwork = false;

    QString last_query;
    QByteArray resource;
    QByteArray resourceName;

    PaginationOptions paginationOptions;

    QStringListModel model;
    QNetworkReply *reply = nullptr;
};

}

#endif // RESTMODEL_H
