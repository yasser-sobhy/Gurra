import QtQuick 2.7
import QtQuick.Controls 2.0

Item
{
    property var target: Item {}

    anchors.centerIn: parent
    width: target.width
    height: target.height
}

