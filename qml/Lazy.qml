import QtQuick 2.0

Loader {
    id: lazy

    property int priority: low

    property int high: 0
    property int low: 1

    active: false // only load item on demand
    asynchronous: true

    Component.onCompleted: {
        if(priority === high) app.addP1Lazy(lazy)
        else app.addP2Lazy(lazy)
    }
}
