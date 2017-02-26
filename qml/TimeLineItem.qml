import QtQuick 2.0
import QtQuick.Layouts 1.1

import "assets"

Rectangle
{
    id: timeLineItem
    property TimeLine timeLine: TimeLine{}
    property Item contentItem: Item {}

    property alias title: _title
    property alias icon: _icon
    property alias editIcon: _editIcon
    property alias step: _step

    // if enabled, clicking anywhere will emit edit signal
    property bool wideClick: true

    signal edit

    anchors.left: parent.left

    width: parent.width
    height: column.height + ( wrapper.anchors.margins * 2 )
    color: app.colors.white

    Component.onCompleted: {
        contentItem.parent = contentItemWrapper
    }

    Icon {
        id: _icon
        anchors.left: parent.left
        anchors.leftMargin: -timeLine.lineSpacing -(width/2)
        anchors.top: parent.top
        anchors.topMargin: app.margins.normal
        width: app.sizes.xxxLarge

        icon: app.icons.fontAwesome.circle_o
        color: app.colors.primary
        backcolor: app.colors.white
    }

    Text {
        id: _step
        anchors.left: parent.left
        anchors.leftMargin: -timeLine.contentPading
        anchors.verticalCenter: _icon.verticalCenter

        width: timeLine.stepTextWidth - timeLine.stepTextMargin

        color: app.colors.primary
        font.pointSize: app.sizes.h3
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        minimumPointSize: app.sizes.h8
        fontSizeMode: Text.Fit
        //wrapMode: Text.WordWrap
    }

    Item {
        id: wrapper
        anchors.fill: parent
        anchors.margins: app.margins.normal

        Column {
            id: column
            width: parent.width
            spacing: app.spacing.normal

            RowLayout {
                width: parent.width
                height: app.sizes.xxxLarge
                spacing: app.spacing.small

                Label {
                    id: _title
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    verticalAlignment: Text.AlignVCenter
                }

                Icon {
                    id: _editIcon
                    Layout.preferredWidth: width
                    Layout.preferredHeight: height

                    color: app.colors.primary
                    visible: icon !== ""

                    onClicked: timeLineItem.edit()
                }
            }

            Item {
                id: contentItemWrapper
                width: parent.width
                height: contentItem.height
            }
        }

        MouseArea {
            anchors.fill: parent
            enabled: timeLineItem.wideClick
            onClicked: timeLineItem.edit()
        }
    }
}
