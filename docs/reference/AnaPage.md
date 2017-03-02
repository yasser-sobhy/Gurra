#AnaPage displays a page


    import QtQuick 2.0
    import QtQuick.Controls 2.0
    import QtQuick.Layouts 1.1
    import Gurra 1.0
    
    AnaPage
    {
        id: page
        header: app.headers.about
    
        Background {
            color: app.colors.primary
        }
    
        Column
        {
            anchors.centerIn: parent
            spacing: app.sizes.normal
    
            Avatar
            {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 200
                height: 200
                picture: "qrc:/assets/images/logo.png"
            }
    
            Space { height: app.sizes.large}
    
            Label
            {
                anchors.horizontalCenter: parent.horizontalCenter
    
                text: qsTr("Gurra 1.0")
                font.pointSize: app.sizes.h3
                color: app.colors.white
            }
    
            Label
            {
                anchors.horizontalCenter: parent.horizontalCenter
    
                text: qsTr("Copyright © 2016-2017 Yasser Sobhy")
                font.pointSize: app.sizes.h4
                color: app.colors.white
            }
    
            Label
            {
                anchors.horizontalCenter: parent.horizontalCenter
    
                text: qsTr("All right reserved")
                font.pointSize: app.sizes.h5
                color: app.colors.white
            }
        }
    }

##Properties

###**edit**: bool
A convenient property, should be true when editing a resource

###**loading**: bool
If true AnaPage will display a busy indicator to inform the user that something is going on
	    
###**fetching**: bool
if true AnaPage will display a busy indicator at the bottom of the page to inform the user that data is being fetched
    	    
###**noInternet**: bool
if true AnaPage will display an icon along with a text and button to all the user to try again 
    	    
###**noContent**: bool
if true AnaPage will display an icon along with a text and button to all the user to try again 
        	    
###**noNetwork**: bool
if true AnaPage will display an icon along with a text and button to all the user to try again 

###**noInternet_button**: bool     

    default: true

If true a TRY AGAIN button will be displayed if `noInternet` is true
		   
###**noContent_button**: bool     

    default: true

If true a TRY AGAIN button will be displayed if `noContent` is true
		   
###**noNetwork_button**: bool     

    default: true

If true a TRY AGAIN button will be displayed if `noNetwork` is true
		   
###**loading_message**: string
A text message to be displayed if `loading` is true
		    
###**noInternet_message**: string 

    default: No Connection

A text message to be displayed if `noInternet` is true
		    
###**noContent_message**: string 

    default: Sorry, no results that matchs your cretiera

A text message to be displayed if `noContent` is true
		    
###**noNetwork_message**: string 

    default: Network connection error

A text message to be displayed if `noNetwork` is true
		    
###**noInternet_icon**: string  

    default: app.icons.fontAwesome.exclamation

An icon be displayed if `noInternet` is true
		    
###**noContent_icon**:  string 

    default: app.icons.fontAwesome.exclamation

An icon to be displayed if `noContent` is true
		    
###**noNetwork_icon**:  string

    default: app.icons.fontAwesome.exclamation

An icon to be displayed if `noNetwork` is true

#Signals

###**retry**
This signal will be emitted when the user click `noContent_button` button 
	
###**retryConnection**
This signal will be emitted when the user click `noInternet_button` button 
	
###**retryNetwork**
This signal will be emitted when the user click `noNetwork_message` button 
	
###**active**
This signal will be emitted when AnaPage is pushed on or popped of StackView. In many situation `enter` signal is preferred over `active`

###**activating**
This signal will be emitted when AnaPage is bieng pushed on or popped of StackView. In many situation `beforeEnter` signal is preferred over `activating`
    	   
###**inactive**
This signal will be emitted when AnaPage is poped of StackView. In many situation `leave` signal is preferred over `inactive`
    	   
###**beforeEnter**
This signal will be emitted before AnaPage is pushed on StackView. 
     	   
###**enter**
This signal will be emitted after AnaPage is pushed on StackView. 

###**beforeLeave**
This signal will be emitted before AnaPage is popped of StackView. 

###**leave**
This signal will be emitted after AnaPage is popped of StackView. 










