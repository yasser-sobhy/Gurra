#ifndef RESTUPLOADER_H
#define RESTUPLOADER_H

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
#include <QQueue>
#include "mimetypes.h"
#include "restconsumer3.h"


namespace Gurra {

class RestUploader : public QObject
{
    Q_OBJECT

    Q_PROPERTY(RestConsumer3* restConsumer READ getRestConsumer WRITE setRestConsumer)
    Q_PROPERTY(int current READ getCurrent NOTIFY currentChanged)
    Q_PROPERTY(int total READ getTotal NOTIFY totalChanged)

public:
    RestUploader();
    ~RestUploader();

public slots:
    void upload(QByteArray resource, QString file, bool put = false);
    void upload(QByteArray resource, QString file, QByteArray data, bool put = false);

    void upload(QByteArray resource, QList<QString> files, bool put = false);
    void upload(QByteArray resource, QList<QString> files, QByteArray data, bool put = false);

    void setRestConsumer(RestConsumer3 *consumer);
    RestConsumer3* getRestConsumer();

    int getCurrent();
    int getTotal();

signals:

    void uploaded(const QByteArray rawData);
    void progress(qint64 sent, qint64 total);
    void finished(int total);

    void currentChanged(int value);
    void totalChanged(int value);

    void networkError( QNetworkReply::NetworkError err );
    void serverError(const QByteArray err);
    void badConentError();

    // errors issued by RestConsumer before sending a request
    void error(const QByteArray err);

    void destroying(RestUploader *rest);

private:
    void uploadMore();

private:
    QQueue<QString> pending_files;
    bool is_put;
    QByteArray resource;
    int current;
    int total;
    RestConsumer3 *m_restConsumer = nullptr;
};

}

#endif // RESTUPLOADER_H
