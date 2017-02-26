import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import ".."

Popup
{
    id: popup

    property string title
    property int selectedIndex: -1
    property string selectedText

    property Component delegate
    property alias model: repeater.model
    property alias spacing: column2.spacing

    property int mxaHeight: 250

    contentWidth: 250
    contentHeight: column1.height

    modal: true
    focus: true

    x: (app.width/2) - width / 2
    y: (app.height/2) - height / 2

    Column
    {
        id: column1
        width: parent.width - app.margins.normal * 2
        x: app.margins.normal

        spacing: app.spacing.large

        Label
        {
            width: parent.width
            text: title
            font.bold: true
        }

        Flickable
        {
            width: parent.width
            height: Math.min(mxaHeight, column2.height)

            contentWidth: width
            contentHeight: column2.height
            clip: true

            Column
            {
                id: column2
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - app.margins.small * 2

                spacing: app.spacing.normal

                Repeater {
                    id: repeater

                    delegate: popup.delegate
                }
            }
        }
    }
}
