import QtQuick 2.7

Image {

    id: _image

    property string marker
    property alias picture: _image.source

    signal clicked

    width: app.sizes.xxxLarge * 3
    height: app.sizes.xxxLarge * 3

    fillMode: Image.PreserveAspectFit

    Rectangle {
        anchors.fill: parent
        anchors.margins: border.width
        color: app.colors.accent
        border.color: app.colors.accent
        border.width: 2
        visible: _image.source.toString() === ""

        Label {
            anchors.centerIn: parent
            font.pointSize: app.sizes.h2
            text: marker
            color: app.colors.foreground
        }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked: _image.clicked()
    }
}
