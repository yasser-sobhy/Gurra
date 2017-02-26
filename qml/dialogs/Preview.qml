import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import Gurra 1.0

Popup
{
    id: popup

    property string picture
    property int preferedWidth: 250
    property int preferedHeight: 400

    property alias image: _image
    property bool auto: true

    contentWidth: Math.min(preferedWidth, _image.sourceSize.width)
    contentHeight: Math.min(preferedHeight, _image.sourceSize.height)

    modal: true
    focus: true
    opacity: 0.0

    x: (app.width/2) - width / 2
    y: (app.height/2) - height / 2

    onPictureChanged: if(auto) open()

    onOpened: {
        opacity = 1.0
    }
    onClosed: {
        opacity = 0.0
    }

    Behavior on opacity {NumberAnimation {duration: 1000}}

    Image
    {
        id: _image
        anchors.centerIn: parent

        width: popup.contentWidth
        height: popup.contentHeight

        source: picture
    }

    Icon
    {
        anchors.left: _image.left
        anchors.top: _image.top

        anchors.leftMargin: -app.margins.normal
        anchors.topMargin: -app.margins.xxxLarge

        icon: app.icons.fontAwesome.times_circle_o
        font.pointSize: app.sizes.h3
        color: app.colors.white

        onClicked: close()
    }
}
