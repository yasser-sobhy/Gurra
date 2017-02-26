import QtQuick 2.0
import QtQuick.Controls 2.0

Item
{
    id: bigIcon

    property string color: app.colors.transparent

    property alias icon: _icon
    property alias label: _label
    property alias spacing: column.spacing

    signal clicked

    width: Math.max(_icon.width, _label.paintedWidth) + (app.margins.small * 2)
    height: column.height


    Column
    {
        id: column
        anchors.horizontalCenter: parent.horizontalCenter

        spacing: app.spacing.small

        Icon
        {
            id: _icon
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: app.sizes.h3
            color: app.colors.foreground
            backcolor: bigIcon.color
        }

        Label
        {
            id: _label
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: app.sizes.h6
            color: app.colors.primary
        }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked: bigIcon.clicked()
    }
}
