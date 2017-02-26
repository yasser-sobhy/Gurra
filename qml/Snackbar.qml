import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle
{
    id: msg
    property string message
    property string action

    property var actionCallback

    anchors.bottom: parent.bottom
    width: parent.width
    height: row.height + app.margins.xLarge

    color: app.colors.primary
    opacity: 0.0
    z: 100000

    onMessageChanged: {

        if(message.length > 0){
            msg.visible = true
            msg.opacity = 1.0
           hideTimer.start()
        }
    }

    Behavior on opacity {NumberAnimation {duration: 200}}

    Timer
    {
        id: hideTimer
        interval: 2000
        onTriggered: {
            msg.opacity = 0.0
            msg.visible = false
            msg.message = ""
        }
    }

    RowLayout {

        id: row

        anchors.centerIn: parent
        width: parent.width - app.margins.large
        height: msg_label.contentHeight
        anchors.margins: app.margins.normal
        spacing: app.spacing.normal

        Label
        {
            id: msg_label
            Layout.fillWidth: true
            Layout.preferredHeight: contentHeight
            wrapMode: Text.Wrap

	    font.pointSize: app.sizes.h4
            color: app.colors.white
            text: message
        }

        Label
        {
            Layout.preferredWidth: contentWidth
            Layout.preferredHeight: contentHeight

            text: action
            color: app.colors.white
            font.bold: true
	    font.pointSize: app.sizes.h4

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    hideTimer.triggered()
                    if(actionCallback) actionCallback()
                }
            }
        }
    }
}
