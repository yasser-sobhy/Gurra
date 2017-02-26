import QtQuick 2.6
import QtQuick.Controls 2.0

Tumbler 
{
    id: control
    property int minYear
    visibleItemCount: 3

    function selectedYear(){
        return minYear + currentIndex + 1
    }

    delegate: Text {
        text: index + minYear + 1
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

