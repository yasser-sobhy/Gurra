#ifndef ANACACHE_H
#define ANACACHE_H

#include <QTimer>
#include <QString>
#include <QDateTime>
#include <QHash>

#define _30SEC 30*1000

class AnaCache : public QObject
{
    Q_OBJECT

    struct Cache {
        QDateTime created;
        qint64 ttl;
        QString url;
        QByteArray content;
    };

public:
    AnaCache();

    void cache(QByteArray category, QString url, QByteArray content, qint64 ttl = 30000);
    QByteArray get(QByteArray category, QString url);
    void remove(QByteArray category, QString url);
    void clear(QByteArray category);

private:
    void clean();

    QTimer timer;
    //<category, <url, Cache>>
    QHash<QByteArray, QHash<QString, Cache>> caches;
};

#endif // ANACACHE_H
