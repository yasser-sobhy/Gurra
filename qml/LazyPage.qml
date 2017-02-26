import QtQuick 2.0

Loader {
    id: lazyPage

    property var params: ({}) // params to pass to page when loaded
    // a wrokarround because QML dosen't support JavaScript's instance of and typeof methods
    // app.pushPage() will check for this property to check whether it's a LoaderPage or not
    property bool _is_lazy: true

    property int priority: low
    property int high: 1
    property int low: 0

    active: false // only load page on demand
    asynchronous: true

    Component.onCompleted: {
        console.log("pc", source)
        if(priority === high) app.addP1LazyPage(lazyPage)
    }
}
