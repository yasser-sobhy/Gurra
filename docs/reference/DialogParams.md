#DialogParams object groups some properties to be used by popup components

    property DialogParams logout: DialogParams {
        title: qsTr("Logout")
        message: qsTr("Are you sure you want to logout?")
        button1: qsTr("Yes")
        button2: qsTr("No")
        yesCallback: function(){
            app.logic.logout()
            app.replacePage([app.pages.home])
        }
    }

    property DialogParams loginFirst: DialogParams {
        title: qsTr("Sorry")
        message: qsTr("Please login first")
        button1: qsTr("Ok")
    }
    
##Properties

###**title**: string
This property holds dialog title
###**message**: string
This property holds dialog body
###**button1**: string
This property holds the text of dialog accept button
###**button2**: string
This property holds the text of dialog reject button
###**yesCallback**: var
This property holds a reference to a callback function to be call when user accepts the dialog
###**noCallback**: var
This property holds a reference to a callback function to be call when user rejects the dialog