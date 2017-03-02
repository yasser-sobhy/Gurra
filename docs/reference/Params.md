#Params holds some frequently used `DialogParam`'s






##Available `DialogParam`

    property DialogParams postSuccess: DialogParams {
        title: qsTr("Success")
        message: qsTr("Successfully posted.")
        button1: qsTr("Ok")
    }

    property DialogParams updateSuccess: DialogParams {
        title: qsTr("Success")
        message: qsTr("Successfully updated.")
        button1: qsTr("Ok")
    }

    property DialogParams deleteSuccess: DialogParams {
        title: qsTr("Success")
        message: qsTr("Successfully deleted.")
        button1: qsTr("Ok")
    }

    property DialogParams noInternet: DialogParams {
        title: qsTr("Error")
        message: qsTr("Could't connect to server, Please chech your internet connection.")
        button1: qsTr("Ok")
    }

    property DialogParams getError: DialogParams {
        title: qsTr("Error")
        message: qsTr("Error retrieving data.")
        button1: qsTr("Ok")
    }

    property DialogParams serverError: DialogParams {
        title: qsTr("Error")
        message: qsTr("Sorry, error occured.")
        button1: qsTr("Ok")
    }

    property DialogParams exit: DialogParams {
        title: qsTr("Exit?")
        message: qsTr("are you sure you want to exit")
        button1: qsTr("Yes")
        button2: qsTr("No")
        yesCallback: function() {
            Qt.quit()
        }
    }

    property DialogParams invalidLogin: DialogParams {
        title: qsTr("Error")
        message: qsTr("Either username or password are incorrect")
        button1: qsTr("Ok")
    }
