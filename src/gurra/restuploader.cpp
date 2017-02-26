#include "restuploader.h"
#include "restconsumer3.h"

using namespace Gurra;

RestUploader::RestUploader()
{
    // to upload pending file, if any
    connect(this, &RestUploader::uploaded, this, &RestUploader::uploadMore);
}

RestUploader::~RestUploader(){
    emit destroying(this);
}

void RestUploader::upload(QByteArray resource, QString file, bool put){
    m_restConsumer->upload(this, resource, file, put);
}

void RestUploader::upload(QByteArray resource, QString file, QByteArray data, bool put){
    m_restConsumer->upload(this, resource, file, data, put);
}

void RestUploader::upload(QByteArray resource, QList<QString> files, bool put){

    is_put = put;
    this->resource = resource;

    current = 1;
    currentChanged(current);

    this->total = files.size();
    totalChanged(total);

    pending_files.clear();
    for(QString url : files)  pending_files.enqueue(url);
    m_restConsumer->upload(this, resource, pending_files.dequeue(), put);
}

void RestUploader::upload(QByteArray resource, QList<QString> files, QByteArray data, bool put){

    is_put = put;
    this->resource = resource;

    current = 1;
    currentChanged(current);

    this->total = files.size();
    totalChanged(total);

    pending_files.clear();
    for(QString url : files)  pending_files.enqueue(url);
    upload(resource, pending_files.dequeue(), data, put);
}

void RestUploader::uploadMore(){

    if(pending_files.size() > 0){
        current +=1;
        currentChanged(current);
        upload(resource, pending_files.dequeue(), is_put);
    }
    else if(current == total) finished(total);
}

RestConsumer3 *RestUploader::getRestConsumer(){
    return m_restConsumer;
}

void RestUploader::setRestConsumer(RestConsumer3 *consumer)
{
    if(consumer) m_restConsumer = consumer;
}

int RestUploader::getCurrent(){
    return this->current;
}

int RestUploader::getTotal(){
    return this->total;
}
