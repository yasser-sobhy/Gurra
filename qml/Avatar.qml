import QtQuick 2.0
import QtQuick.Dialogs 1.0
import QtGraphicalEffects 1.0

Item
{
    id: pic

    property string url // picture url prefix
    property string pictureID

    property int size: app.sizes.xLarge * 5
    property alias picture: profilepic.source
    property bool edit

    signal clicked
    signal select

    onPictureIDChanged: {
        if(pictureID !== "") profilepic.source = url + pictureID
    }

    width: size
    height: size

    Rectangle
    {
        anchors.fill: parent

        border.color: "white"
        border.width: 2 *app.device.aspectRatio

        Image {
            id: profilepic
            anchors.fill: parent
        }

        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Item {
                width: profilepic.width
                height: profilepic.height
                Rectangle {
                    anchors.centerIn: parent
                    width: profilepic.width
                    height: profilepic.height
                    radius: profilepic.width /2
                }
            }
        }

        MouseArea
        {
            anchors.fill: parent
            onClicked: {
                if(edit) pic.select()
                else pic.clicked()
            }
        }
    }
}
