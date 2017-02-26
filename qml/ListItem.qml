import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import Gurra 1.0

Rectangle
{
    id: listItem
    property string icon
    property string title
    property string description
    property bool separatorVisible: false

    property alias iconItem: _icon
    property alias titleItem: _title
    property alias descriptionItem: _description

    property alias rowSpacing: row.spacing
    property alias columnSpacing: column.spacing
    property alias backcolor: listItem.color

    signal clicked

    width: parent.width
    height: row.height + (app.margins.normal * 2)
    color: app.colors.transparent
    clip: true

    Row
    {
        id: row
        anchors.left: parent.left
        anchors.leftMargin: app.margins.normal
        anchors.verticalCenter: parent.verticalCenter

        width: parent.width
        height: Math.max(column.height, _icon.height)

        spacing: app.spacing.normal

        Icon
        {
            id: _icon
            anchors.verticalCenter: parent.verticalCenter

            icon: listItem.icon
            color: app.colors.primary
            font.pointSize: app.sizes.h4

            visible: listItem.icon !== ""
        }

        Column
        {
            id: column
            anchors.verticalCenter: parent.verticalCenter

            spacing: app.spacing.small

            Label
            {
                id: _title
                anchors.left: parent.left

                text: listItem.title
                color: app.colors.foreground
                visible: listItem.title !== ""
            }

            Label
            {
                id: _description
                anchors.left: parent.left

                text: listItem.description
                color: app.colors.foreground
                font.pointSize: app.sizes.small

                visible: listItem.description !== ""
            }
        }
    }

    HorizontalLine {
        id: separator
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: app.margins.xxLarge
        anchors.right: parent.right
        anchors.rightMargin: app.margins.small
        visible: separatorVisible
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked: listItem.clicked()
    }
}

