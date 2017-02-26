import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import ".."

Popup
{
    id: popup

    property string title
    property alias elements: grid.children
    property int mxaHeight: 250
    property alias columns: grid.columns

    contentWidth: 250
    contentHeight: column1.height

    modal: true
    focus: true

    Column
    {
        id: column1
        width: parent.width - app.margins.normal * 2
        x: app.margins.normal

        spacing: app.spacing.large

        Label
        {
            width: parent.width
            text: title
            font.bold: true
        }

        Flickable
        {
            width: parent.width
            height: Math.min(mxaHeight, grid.height)

            contentWidth: width
            contentHeight: grid.height
            clip: true

            Grid
            {
                id: grid
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - app.margins.small * 2

                spacing: app.spacing.large
            }
        }
    }
}
