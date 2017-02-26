import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import ".."

Popup
{
    id: popup

    property DialogParams options: DialogParams{}
    property string password

    contentWidth: 250
    contentHeight: coulumn1.height

    modal: true
    focus: true

    closePolicy: Popup.NoAutoClose

    Column
    {
        id: coulumn1
        width: parent.width - app.margins.small * 2
        x: app.margins.small

        spacing: app.spacing.normal

        Label
        {
            width: parent.width
            text: options.title
            font.bold: true
        }

        TextField {
            id: passwordField
            width: parent.width
            placeholderText: options.message
            echoMode: showPassword.checked? TextField.Normal : TextField.Password
        }

        CheckBox {
            id: showPassword
            text: "Show Password"
        }

        Row
        {
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: app.spacing.normal

            Button
            {
                text: options.button1
                onClicked: {
                    password = passwordField.text
                    popup.close()
                    if(options.yesCallback) options.yesCallback()
                }
            }

            Button
            {
                text: options.button2
                visible: options.button2 !== ""
                onClicked: {
                    password = ""
                    popup.close()
                    if(options.noCallback) options.noCallback()
                }
            }
        }
    }
}
