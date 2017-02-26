import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Page {

    name: ""

    ColumnLayout
    {
        anchors.centerIn: parent
        spacing: 15

        LandportsLabel
        {
            Layout.alignment: Qt.AlignHCenter

            text: LandportsIcons.Icon.LandPort
            font.pointSize: 120
            font.family: landportsFont.name
            color: "white"
        }

        LandportsLabel
        {
            Layout.alignment: Qt.AlignHCenter

            text: "منافذ الخليج"
            font.pointSize: 28
            color: "white"
        }


        LandportsLabel
        {
            Layout.alignment: Qt.AlignHCenter

            text: "عبد الله الهاجري 2016"
            font.pointSize: 18
            color: "white"
        }


        LandportsLabel
        {
            Layout.alignment: Qt.AlignHCenter

            text: "جميع الحقوق محفوظة"
            font.pointSize: 18
            color: "white"
        }
    }
}

