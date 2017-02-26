import QtQuick 2.0
import QtQuick.Controls 2.0

Label {
    id: label

    signal clicked

    font.pointSize: 12
    color: app.colors.primary

    verticalAlignment: Text.AlignVCenter

    MouseArea
    {
        anchors.fill: parent
        onClicked: label.clicked()
    }
}
