#include "restmodel.h"
#include "restconsumer2.h"

using namespace Gurra;

RestModel::RestModel()
{

}



RestModel::~RestModel() {
   emit destroying(this);
}

void RestModel::fetch(QByteArray resource){
    m_restConsumer->get(this, resource, from, to);
}

void RestModel::get(QByteArray resource,  int from, int to, QByteArray addQuery){
    m_restConsumer->get(this, resource, from, to, addQuery);
}

void RestModel::ready(const QByteArray rawData){
    //model.insertRows()
}

void RestModel::listReady(const QVariant rawDataList){

}

RestConsumer2* RestModel::getRestConsumer(){
    return m_restConsumer;
}

void RestModel::setRestConsumer(RestConsumer2 *consumer)
{
    if(consumer) m_restConsumer = consumer;
}

