import QtQuick 2.0
import "assets"

Item
{
    property Item centerIn

    Component.onCompleted: {
        parent.x = (app.width/2) - parent.width / 2
        parent.y = (app.height/2) - parent.height / 2
    }
}

