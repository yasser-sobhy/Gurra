import QtQuick 2.0
import "assets"

Item
{
    property alias picker: _picker
    property alias snackbar: _snackbar
    property alias msg: _msg
    property alias _msg: _msg2
    property alias cnfrm: _cnfrm
    property alias done: _done
    property alias loading: _loading
    property alias valueInput: _valueInput



    ListPicker {
        id: _picker
        property var callback

        delegate: ListItem {
            title: modelData
            onClicked:  {
                _picker.callback( index, title )
                _picker.close()
            }
        }
    }


    Snackbar {
        id: _snackbar
    }

    Message
    {
        id: _msg
    }

    Message
    {
        id: _msg2
        options.button1: qsTr("Ok")
    }


    Confirm
    {
        id: _cnfrm
    }

    Done
    {
        id: _done
    }

    Loading
    {
        id: _loading
    }

    ValueInput
    {
        id: _valueInput
    }
}

