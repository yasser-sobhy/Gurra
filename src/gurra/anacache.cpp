#include "anacache.h"

AnaCache::AnaCache()
{
    connect(&timer, &QTimer::timeout, this, &AnaCache::clean);
    timer.start(_30SEC);
}

void AnaCache::cache(QByteArray category, QString url, QByteArray content, qint64 ttl){

    this->caches[category][url] = { QDateTime::currentDateTime(), ttl, url, content };
}

QByteArray AnaCache::get(QByteArray category, QString url){

    if(caches.contains(category)){
        if(caches[category].contains(url))
            return caches[category][url].content;
    }

    return QByteArray();
}

void AnaCache::remove(QByteArray category, QString url){
    caches[category].remove(url);
}

void AnaCache::clear(QByteArray category){
    caches.remove(category);
}

void AnaCache::clean(){

    for(QByteArray &cat : caches.keys()){

        for(QString &url : caches[cat].keys()){

            Cache &cache = caches[cat][url];
            if( QDateTime::currentDateTime().msecsTo( cache.created) > cache.ttl ){
                caches[cat].remove(url);
            }
        }
    }
}
