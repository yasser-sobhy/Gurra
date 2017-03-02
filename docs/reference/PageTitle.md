#PageTitle displays a page header with title and two icons

> PageTitle is the only page header style that ships with Gurra

    property PageTitle search: PageTitle {
	    title: qsTr("Search")
	    onClose: app.popPage()
    }
    
    property PageTitle myWatchings: PageTitle {
	    title: qsTr("Watchings")
	    onClose: app.popPage()
    }
    
    property PageTitle myListings: PageTitle {
	    title: qsTr("My Listings")
	    onClose: app.popPage()
    }

#Properties

###**title**: string
This property holds the title of the page header
###**icon**: string 

default: app.icons.fontAwesome.arrow_left

This property holds the icon of the page header

###**rightIcon**: string
This property holds the right-hand side icon of the page header

###**titleItem**:  Label
This property holds a reference to the internal title Label

###**iconItem**: Icon
This property holds a reference to the internal Icon item

###**rightIconItem**: Icon
This property holds a reference to the internal right Icon item

###**rightAction**
This property holds a function to be called when right-hand side icon is clicked

###**leftAction**
This property holds a function to be called when left-hand side icon is clicked

##Signals

###**close**
This signal will be emitted when left-hand side icon is clicked

