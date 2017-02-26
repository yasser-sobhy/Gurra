import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import ".."

Popup
{
    id: popup

    property DialogParams options: DialogParams{}

    contentWidth: 250
    contentHeight: coulumn1.height

    modal: true
    focus: true

    x: (app.width/2) - width / 2
    y: (app.height/2) - height / 2

    closePolicy: Popup.NoAutoClose

    Column
    {
        id: coulumn1
        width: parent.width - app.margins.small * 2
        x: app.margins.small

        spacing: app.spacing.large

        Label
        {
            width: parent.width
            text: options.title
            font.bold: true
        }

        Label
        {
            width: parent.width
            text: options.message
            wrapMode: Text.WordWrap
        }

        Row
        {
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: app.spacing.normal

            Button
            {
                text: options.button1
                onClicked: {
                    popup.close()
                    if(options.yesCallback) options.yesCallback()
                }
            }

            Button
            {
                text: options.button2
                visible: options.button2 !== ""
                onClicked: {
                    popup.close()
                    if(options.noCallback) options.noCallback()
                }
            }
        }
    }
}
