import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Rectangle
{
    id: iconButton

    property int iconWidth: app.sizes.xxxLarge
    property alias icon: _icon
    property alias textField: _field

    implicitHeight: _field.height

    RowLayout
    {
        id: row
        anchors.fill: parent

        spacing: app.spacing.small

        Icon
        {
            id: _icon
            Layout.preferredWidth: iconWidth
            Layout.fillHeight: true

            font.pointSize: app.sizes.h4
        }

        TextField
        {
            id: _field
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
