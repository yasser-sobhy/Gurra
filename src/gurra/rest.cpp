#include "rest.h"
#include "restconsumer2.h"

using namespace Gurra;

Rest::~Rest() {
   emit destroying(this);
}

void Rest::get(QByteArray resource, QString query){
    m_restConsumer->get(this, resource, query);
}

void Rest::post(QByteArray resource, QByteArray data, QString query){
    m_restConsumer->post(this, resource, data, query);
}

void Rest::put(QByteArray resource, QByteArray data, QString query){
    m_restConsumer->put(this, resource, data, query);
}

void Rest::remove(QByteArray resource, QString query){
    m_restConsumer->remove(this, resource, query);
}

RestConsumer2* Rest::getRestConsumer(){
    return m_restConsumer;
}

void Rest::setRestConsumer(RestConsumer2 *consumer)
{
    if(consumer) m_restConsumer = consumer;
}

bool Rest::getCache(){
    return _cache;
}

void Rest::setCache(bool value){
    _cache = value;
}

bool Rest::getCacheTtl(){
    return _cacheTtl;
}

void Rest::setCacheTtl(qint64 value){
    _cacheTtl = value;
}

QByteArray Rest::getCacheCategory(){
    return _cacheCategory;
}

void Rest::setCacheCategory(QByteArray value){
    _cacheCategory = value;
}
