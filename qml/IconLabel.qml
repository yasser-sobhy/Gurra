import QtQuick 2.0
import QtQuick.Controls 2.0

Item
{
    id: iconLabel

    property alias icon: _icon
    property alias label: _label
    property alias spacing: row.spacing

    signal clicked

    height: app.sizes.large * 2
    width: row.width

    Row
    {
        id: row
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left

        spacing: app.spacing.normal

        Icon
        {
            id: _icon
            anchors.verticalCenter: parent.verticalCenter
            visible: icon !== ""
        }

        Label
        {
            id: _label
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked: iconLabel.clicked()
    }
}
