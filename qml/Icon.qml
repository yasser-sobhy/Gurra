import QtQuick 2.7

Text
{
    id: _icon

    property string icon
    property string backcolor: app.colors.transparent
    property alias background: _background

    signal clicked

    width: paintedWidth + (app.margins.normal * 2)
    height: width //contentHeight + app.margins.normal * 2

    font.family: app.iconFonts.primary
    font.pointSize: app.sizes.h6
    color: app.colors.foreground

    text: icon

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter

    Rectangle
    {
        id: _background
        anchors.fill: parent
        radius: width
        color: backcolor
        z: -1
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked: _icon.clicked()
    }
}
