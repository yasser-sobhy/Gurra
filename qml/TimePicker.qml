import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Item
{
    RowLayout
    {
        anchors.fill: parent

        TimeColumn
        {
            model: 12
            Layout.preferredWidth: app.sizes.xxLarge * 2
            Layout.fillHeight: true
        }

        VerticalLine { opacity: 0.3 }

        TimeColumn
        {
            model: 60
            Layout.preferredWidth: app.sizes.xxLarge * 2
            Layout.fillHeight: true
        }

        VerticalLine { opacity: 0.3 }

        TimeColumn
        {
            ampm: true
            model: ["AM", "PM"]
            Layout.preferredWidth: app.sizes.xxLarge * 2
            Layout.fillHeight: true
        }
    }
}
