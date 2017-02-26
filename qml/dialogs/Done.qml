import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import Gurra 1.0

Popup
{
    id: popup

    property bool autoHide: true

    contentWidth: 250
    contentHeight: coulmn1.height

    modal: true
    focus: true

    x: (app.width/2) - width / 2
    y: (app.height/2) - height / 2

    onOpened: {
        checkIcon.opacity = 1.0
    }
    onClosed: {
        checkIcon.opacity = 0.0
    }

    Timer
    {
        running: autoHide && visible
        interval: 2000
        onTriggered: close()
    }

    Column
    {
        id: coulmn1
        width: parent.width - app.margins.small * 2
        x: app.margins.small

        spacing: app.spacing.large

        IconLabel
        {
            width: parent.width

            icon.icon: app.icons.fontAwesome.check
            icon.font.pointSize: app.sizes.h4

            label.text: "Done!"
            label.font.bold: true
        }

        Icon
        {
            id: checkIcon

            anchors.horizontalCenter: parent.horizontalCenter

            icon: app.icons.fontAwesome.check
            font.pointSize: app.sizes.h1 * 2
            color: app.colors.primary

            opacity: 0.0 //hidden by default

            Behavior on opacity {
                    NumberAnimation { duration: 500}
            }
        }

        Button
        {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "OK"
            onClicked: close()
        }

    }
}
