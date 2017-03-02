#Displays an item with icon, title and description


    ListItem {
        title: qsTr("My Listings")
        icon: app.icons.fontAwesome.th_list
        color: app.colors.white
        onClicked: app.pushPage(app.pages.myListings)
    }
    
    ListItem {
        title: qsTr("My Account")
        icon: app.icons.fontAwesome.user
        color: app.colors.white
        onClicked: app.pushPage(app.pages.myAccount)
    }
    
    ListItem {
        title: qsTr("My Favorites")
        icon: app.icons.fontAwesome.heart
        color: app.colors.white
        onClicked: app.pushPage(app.pages.favorites)
    }

###**icon**: string
this property holds the `ListItem's` icon
###**title**: string
this property holds the `ListItem's` title
###**description**: string
this property holds the `ListItem's` description
###**separatorVisible**: bool

    default: false

this property holds whether to show a seperator at the bottom of ListItem or not

###**iconItem**: Icon
this property holds a regerence to the internal icon

###**titleItem**: Label
this property holds a regerence to the internal title label

###**descriptionItem**: Label
this property holds a regerence to the internal description label

###**rowSpacing**: int
this property holds the spacing between icon and labels

###**columnSpacing**: int
this property holds the spacing between title and description labels

###**backcolor**: string

    default: app.colors.transparent

this property holds the backcolor of `ListItem`

##Signals

###**clicked**
This signal will be emitted when `ListItem` is clicked



