import QtQuick 2.7

ListView
{
    anchors.fill: parent
    anchors.margins: app.margins.normal
    spacing: app.spacing.large
    visible: count > 0

    function clear(){
        model = undefined
    }
}
