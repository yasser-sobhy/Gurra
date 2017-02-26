import QtQuick 2.7
import QtQuick.Controls 2.0

Control {
    id: ptr

    property Flickable view
    property string label

    signal refresh

    anchors.horizontalCenter: parent.horizontalCenter
    width: column.width + app.margins.normal
    height: column.height + app.margins.normal
    y: -ptr.view.contentY -70

    Column {
        id: column
        anchors.centerIn: parent
        spacing: app.spacing.small

        Icon {
            id: _icon
            property real _pre_opacity
            anchors.horizontalCenter: parent.horizontalCenter
            icon: app.icons.fontAwesome.repeat
            backcolor: app.colors.white

            font.pointSize: app.sizes.h3
            opacity: -ptr.view.contentY /150
            visible: opacity > 0.3

            onOpacityChanged: {
                if(opacity > 0.9) {
                    if(opacity < _pre_opacity && !ptr.view.dragging) {
                        _pre_opacity = 0.0
                        ptr.refresh()
                        return
                    }
                    _pre_opacity = opacity
                }
            }

            transform: Rotation {
                angle: -ptr.view.contentY * 2
                origin.y: _icon.height /2
                origin.x: _icon.width /2
            }
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: ptr.label
            visible: text !== ""
            opacity: _icon.opacity > 0.9? 1.0 : 0.0
            Behavior on opacity {NumberAnimation{duration: 200}}
        }
    }
}
