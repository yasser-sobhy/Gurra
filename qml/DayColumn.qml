import QtQuick 2.6
import QtQuick.Controls 2.0

Tumbler 
{
    id: control
    visibleItemCount: 3

    delegate: Text {
        text: modelData + 1
        font: control.font
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        opacity: 1.0 - Math.abs(Tumbler.displacement) / (visibleItemCount / 2)
    }

    HorizontalLine {
        y: control.height * 0.33
	height: 2
    }

    HorizontalLine {
        y: control.height * 0.66
	height: 2
    }
}

