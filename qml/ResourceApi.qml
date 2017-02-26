import QtQuick 2.0

import Org.Yasser.Gurra 1.0

QtObject {

    property string resource
    property SimplePromise promise: SimplePromise{}
    property bool autoInform: true

    function get(what, from, to, query){
        _rest.get(resource + what, from, to, query)
        return promise
    }

    function get_one(id, query){

        _rest.idGet(resource + "/id/" + id, query)
        return promise
    }

    function list(from, to , query){

        _rest.get(resource, from, to, query)
        return promise
    }

    function create(data, query){

        _rest.post(resource, data, query)
        return promise
    }

    function save(id, data, query){

        _rest.idPut(resource + "/id/" + id, data, query)
        return promise
    }

    function remove(id, query){

        _rest.idDelete(resource + "/id/" + id, query)
        return promise
    }


    property Rest _rest: Rest {
        restConsumer: app.restConsumer

        onReady: {
            app.notLoading()
            if(promise.successCallback) promise.successCallback(rawData)
        }

        onListReady: {
            app.notLoading()
            if(promise.successCallback) promise.successCallback(rawDataList)
        }

        onPosted: {
            app.notLoading()
            if(promise.successCallback) promise.successCallback(rawData)
        }

        onUpdated: {
            app.notLoading()
            if(promise.successCallback) promise.successCallback(rawData)
        }

        onDeleted: {
            app.notLoading()
            if(promise.successCallback) promise.successCallback(rawData)
        }

        onNetworkError: {
            app.notLoading()
            if(promise.networkErrorCallback) promise.networkErrorCallback(err)
        }

        onServerError: {
            console.log("ResourceApi", resource, err)
            app.notLoading()
            if(promise.serverErrorCallback) promise.serverErrorCallback(err)
        }
    }
}
