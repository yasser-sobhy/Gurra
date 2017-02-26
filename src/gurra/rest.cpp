#include "rest.h"
#include "restconsumer2.h"

using namespace Gurra;

Rest::~Rest() {
   emit destroying(this);
}

void Rest::get(QByteArray resource,  int from, int to, QByteArray addQuery){
    m_restConsumer->get(this, resource, from, to, addQuery);
}

void Rest::post(QByteArray resource, QByteArray data, QByteArray addQuery){
    m_restConsumer->post(this, resource, data, addQuery);
}

void Rest::idGet(QByteArray resource, QByteArray addQuery){
    m_restConsumer->idGet(this, resource, addQuery);
}

void Rest::idPut(QByteArray resource, QByteArray data, QByteArray addQuery){
    m_restConsumer->idPut(this, resource, data, addQuery);
}

void Rest::idDelete(QByteArray resource, QByteArray addQuery){
    m_restConsumer->idDelete(this, resource, addQuery);
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
