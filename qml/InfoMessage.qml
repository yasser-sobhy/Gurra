import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Item
{
    id: msg

    property string message
    property bool auto // auto show dialog onMessageChanged
    signal finished


    anchors.fill: parent
    opacity: 0.0

    onMessageChanged: {
        if(message.length > 0 && auto){
            msg.visible = true
            msg.opacity = 1.0
        }
    }

    MouseArea
    {
        anchors.fill: parent
    }

    Behavior on opacity {NumberAnimation {duration: 100}}

    Rectangle
    {
        anchors.centerIn: parent

        width: parent.width - (40 *app.device.aspectRatio)
        height: 145 *app.device.aspectRatio

        color: appColors.alternative

        ColumnLayout
        {
            anchors.fill: parent
            anchors.margins: 10

            Label
            {
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.Wrap

                text: message
                color: appColors.alternativeFont
                font.bold: true
            }

            Button
            {
                Layout.preferredWidth: 60 *app.device.aspectRatio
                Layout.preferredHeight: 40 *app.device.aspectRatio
                Layout.alignment: Qt.AlignCenter

                text: "تم"
                style: ButtonStyle{reversed: true}

                onClicked:{
                    msg.finished()
                    msg.opacity = 0.0
                    msg.visible = false
                    msg.message = "" // to show InfoMessage on message change
                }
            }
        }
    }

}
