import QtQuick 2.0

Item {
    id: error
    property string serverErrorMessage
    property color color: "#006aaf"

    function hide(){

        noConnection.visible = false
        serverError.visible = false
        curreptContent.visible = false
        noFavorites.visible = false
    }

    function showServerError (){
        serverError.visible = true
    }

    function showConnectionError (){
        noConnection.visible = true
    }

    function showCurreptContentError (){
        curreptContent.visible = true
    }

    function showNoFavorites(){
        noFavorites.visible = true
    }

    Label
    {
        id: serverError

        anchors.fill: parent
        anchors.margins: 10

        verticalAlignment: Text.AlignVCenter

        text: serverErrorMessage
        visible: false
        wrapMode: Text.Wrap
        color: error.color
    }

    Label
    {
        id: noConnection
        anchors.fill: parent
        anchors.margins: 10

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        text: "عفواً، فشل الاتصال بالخادوم، يرجى التأكد من اتصال الانترنت ثم المحاولة مرة أخرى"
        visible: false
        wrapMode: Text.Wrap
        color: error.color
    }

    Label
    {
        id: curreptContent
        anchors.fill: parent
        anchors.margins: 10

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        text: "عذراً، تم استلام محتوى معطوب من الخادوم، يرجى المحاولة مرة أخرى"
        visible: false
        wrapMode: Text.Wrap
        color: error.color
    }

}
