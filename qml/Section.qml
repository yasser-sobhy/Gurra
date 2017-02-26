import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {

    property string title
    property alias label: _label

    anchors.horizontalCenter: parent.horizontalCenter

    width: parent.width//_label.contentWidth + app.margins.large
    height: _label.contentHeight + app.margins.large

    color: app.colors.background

    Label {
        id: _label
        anchors.centerIn: parent
        text: title
    }
}
