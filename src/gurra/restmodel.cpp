#include "restmodel.h"
#include "restconsumer2.h"

using namespace Gurra;

RestModel::RestModel()
{
    model.setParent(this);

    connect(this, &Rest::networkError, this, &RestModel::p_networkError);
    connect(this, &Rest::serverError, this, &RestModel::p_serverError);
}

RestModel::~RestModel() {
    emit destroying(this);
}

QByteArray RestModel::getResource(){
    return resource;
}

QByteArray RestModel::getResourceName(){
    return resourceName;
}

void RestModel::setResource(QByteArray resource){

    if(resource.isEmpty()) {
        qDebug() << "RestModel invalid resource url";
        return;
    }

    this->resource = resource;
    emit resourceChanged(resource);
}

void RestModel::setResourceName(QByteArray resourceName){

    if(resourceName.isEmpty()) {
        qDebug() << "RestModel invalid resource name";
        return;
    }

    this->resourceName = resourceName;
    emit resourceNameChanged(resourceName);
}

bool RestModel::getNoInternet(){
    return m_noInternet;
}

bool RestModel::getNoContent(){
    return m_noContent;
}

bool RestModel::getNoNetwork(){
    return m_noNetwork;
}
bool RestModel::getLoading(){
    return m_loading;
}
bool RestModel::getFetching(){
    return m_fetcing;
}
void RestModel::fetch(QString query){

    // fetch alwasy resets models data
    reset();

    resetStatus(true);

    // store query to use for further fetch operations
    last_query = query;

    /// fetch initial data with initial query
    m_restConsumer->get(this, resource, query);
}

void RestModel::fetchMore(){

    resetStatus(false, true);

    QString q;
    if(!last_query.isEmpty())
        q = last_query + "," + paginationOptions.write();
    else q = paginationOptions.write();

    m_restConsumer->get(this, resource, q);
}

void RestModel::reset(){
    model.setStringList({});
}

void RestModel::ready(const QByteArray rawData){

    resetStatus();

    QJsonDocument json;
    QJsonParseError error;
    json = QJsonDocument::fromJson(rawData, &error);

    if(error.error == QJsonParseError::NoError && json.isObject()){

        QJsonObject obj = json.object();
        // read pagination options provided by the server
        paginationOptions = PaginationOptions(obj);

        if(obj.contains(resourceName)){
            QJsonArray arr = obj.value(resourceName).toArray();

            for(QJsonValue v : arr){
                model.insertRow(model.rowCount());
                model.setData(model.index(model.rowCount()-1), QJsonDocument(v.toObject()).toJson(), Qt::DisplayRole);
            }
        }
    }
}

void RestModel::p_networkError(){
    resetStatus(false, false, true);
}

void RestModel::p_serverError(){

    if(model.rowCount() == 0){ // only emit noContentChanged when no data in the model, so ui reflects this correctly
        resetStatus(false, false, false, true);
    }
    else resetStatus();
}

QStringListModel *RestModel::getModel(){
    return &model;
}

void RestModel::resetStatus(bool loading, bool fetcing, bool noNetwork, bool noContent, bool noInternet){

    m_loading = loading;
    m_fetcing = fetcing;
    m_noNetwork = noNetwork;
    m_noContent = noContent;
    m_noInternet = noInternet;

    emit loadingChanged(loading);
    emit fetchingChanged(fetcing);
    emit noNetworkChanged(noNetwork);
    emit noContentChanged(noContent);
    emit noInternetChanged(noInternet);
}

