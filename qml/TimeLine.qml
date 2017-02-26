import QtQuick 2.0
import "assets"

Flickable
{
    id: timeLine
    property int step
    property real stepTextWidth: app.margins.xLarge * 2
    property real stepTextMargin: app.margins.small * 2

    property real lineSpacing: app.margins.xLarge
    property real lineWidth: 2

    property real spacing: app.margins.large

    property real linePadding: stepTextWidth + stepTextMargin
    property real contentPading: linePadding + lineSpacing + lineWidth

    property alias elements: column.data

    contentWidth: width
    contentHeight: column.height
    clip: true

    VerticalLine {
        id: _line
        anchors.left: parent.left
        anchors.leftMargin: linePadding
        width: lineWidth
    }

    Column
    {
        id: column
        anchors.left: _line.right
        anchors.leftMargin: timeLine.lineSpacing
        anchors.verticalCenter: parent.verticalCenter

        width: parent.width - contentPading
        spacing: timeLine.spacing
    }
}
