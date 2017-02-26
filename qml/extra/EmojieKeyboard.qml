import QtQuick 2.0
import QtQuick.Layouts 1.1
import "qrc:/fonts/A7lla14.js" as A7lla14Icons
import "qrc:/fonts/Emojis.js" as Emojis
import com.cutehacks.emooj 1.0

Rectangle
{
    property int emojieSize : 24 *app.device.aspectRatio
    property bool shown : false

    signal add (var emojie)
    signal remove

    function create(sheetX, sheetY)
    {
        return "<span><img width=\"" + emojieSize + "\" height=\""+ emojieSize +"\" src=\"image://com.cutehacks.emooj/" + sheetX + "/" + sheetY + "\"></img></span>"
    }

    function process(str)
    {
        var newStr = ""

        for (var i = 0, len = str.length; i < len; i++) {

            var c = str[i]

            if(emojies.indexOf(c) > -1){
                c = "<font face = \"" + emojieFont + "\"" + "size =" + emojieSize + ">" + c + "</font>"
                newStr += c
            }
            else newStr += c
        }

        return newStr
    }

    width: parent.width
    height: shown? 250 *app.device.aspectRatio : 0

    color: appColors.common
    clip: true

    EmojiDataModel{
        id: emojiDataModel
    }

    ColumnLayout
    {
        anchors.fill: parent
        spacing: 10 *app.device.aspectRatio

        Rectangle
        {
            Layout.fillWidth: true
            Layout.preferredHeight: 40 *app.device.aspectRatio

            color: appColors.common

            RowLayout
            {
                anchors.fill: parent
                anchors.margins: 5 *app.device.aspectRatio
                anchors.leftMargin: 10 *app.device.aspectRatio
                anchors.rightMargin: 10 *app.device.aspectRatio
                spacing: 10 *app.device.aspectRatio

                EasyIcon {
                    font.pointSize: 14 *app.device.fontAspectRatio
                    color: appColors.commonFont
                    icon: A7lla14Icons.Icon.AngleLeft

                    onClicked: remove()
                }

                Item {
                    width: 1
                    height: 1
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                Repeater
                {
                    id: toolbar

                    model: 7

                    delegate:  EasyIcon {
                        font.pointSize: 12 *app.device.fontAspectRatio
                        font.family: gEDinarOneFont.name
                        textFormat: Text.RichText
                        color: appColors.commonFont

                        icon: {
                            var emoji = emojiDataModel.categoryIcon(index)
                            return create(emoji.sheetX, emoji.sheetY)
                        }

                        onClicked: {
                            emojiDataModel.category = index
                            eRepaeter.model = ""
                            eRepaeter.model = emojiDataModel
                        }
                    }
                }
            }

            Rectangle
            {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom

                width: parent.width - (20 *app.device.aspectRatio)
                height: 1
                color: appColors.commonFont
            }
        }

        Flickable
        {
            Layout.fillWidth: true
            Layout.fillHeight: true

            contentWidth: width
            contentHeight: egrid.height

            clip: true

            Item
            {
                anchors.fill: parent
                anchors.margins: 15 *app.device.aspectRatio

                Grid
                {
                    id: egrid
                    width: parent.width
                    clip: true

                    columns: 8
                    spacing: 10 *app.device.aspectRatio

                    Repeater
                    {
                        id: eRepaeter

                        model: emojiDataModel

                        delegate: EasyIcon {

                            font.pointSize: 18 *app.device.fontAspectRatio
                            color: appColors.commonFont

                            icon: create(sheetX, sheetY)
                            textFormat: Text.RichText

                            font.family: gEDinarOneFont.name

                            onClicked: add(create(sheetX, sheetY))
                        }
                    }
                }
            }
        }
    }
}
