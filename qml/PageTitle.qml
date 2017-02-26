import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0


Rectangle
{
    id: tb

    property string title
    property string icon: app.icons.fontAwesome.arrow_left
    property string rightIcon

    property alias titleItem: _title
    property alias iconItem: _icon
    property alias rightIconItem: _right_icon

    property var rightAction
    property var leftAction

    signal close

    height: 60
    color: app.colors.primary

    Label
    {
        id: _title

        anchors.fill: parent
        anchors.margins: 5
        anchors.leftMargin: app.margins.large

        text: title
        color: app.colors.white

        font.bold: true
        font.pointSize: app.sizes.h4

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        Icon
        {
            id: _icon

            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter

            icon: tb.icon
            font.pointSize: app.sizes.h4
            color: app.colors.white

            onClicked: {
                if(leftAction) leftAction()
                close()
            }
        }

        Icon
        {
            id: _right_icon

            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            icon: tb.rightIcon
            font.pointSize: app.sizes.h4
            color: app.colors.white

            onClicked: {
                if(rightAction) rightAction()
            }
        }
    }
}

