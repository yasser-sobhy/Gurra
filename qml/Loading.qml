import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtPositioning 5.2
import Gurra 1.0

Popup
{
    id: popup

    property string message

    contentWidth: column.width
    contentHeight: column.height

    modal: true
    focus: true

    closePolicy: Popup.NoAutoClose

    x: (app.width/2) - width / 2
    y: (app.height/2) - height / 2

    Column {
        id: column
        width: Math.max(indicator.width + app.margins.large, msg.width + app.margins.large)
        spacing: app.spacing.large

        BusyIndicator
        {
            id: indicator
            anchors.horizontalCenter: parent.horizontalCenter
            running: visible
        }

        Label {
            id: msg
            text: message
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
