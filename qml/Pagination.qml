import QtQuick 2.0
import QtQuick.Controls 2.0

Pane
{
    property int count: 5
    property int size: app.sizes.large

    signal page(var page)

    spacing: app.spacing.small
    width: size * count * spacing
    height: size

    Repeater
    {
        model: count
        delegate: Button {
            width: size
            height: size
            text: index
        }
    }
}
