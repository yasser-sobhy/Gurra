import QtQuick 2.0
import QtQuick.Controls 2.0

Button
{
    id: iconButton

    property alias space: row.spacing
    property alias icon: _icon
    property alias label: _label

    width: row.width + app.margins.large
   // height: app.sizes.large * 2

    text: ""

    Row
    {
        id: row
        anchors.centerIn: parent

        spacing: app.spacing.normal

        Icon
        {
            id: _icon
            anchors.verticalCenter: parent.verticalCenter
        }

        Label
        {
            id: _label
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
