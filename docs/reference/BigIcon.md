#**BigIcon** is an `Icon` with label underneath 

        BigIcon {
            icon.icon: app.icons.fontAwesome.ticket
            label.text: qsTr("Buy")
            onClicked: {
                app.pushPage(app.pages.buyTicket)
            }
        }

##Properties

###**color**:  string

    default: app.colors.transparent
    
This property holds the back color of `BigIcon`

###**icon**: Icon
This property holds a reference to inner `Icon` item

###**label**: Label
This property holds a reference to inner `Label` item

###**spacing**: int

    default: app.spacing.small

This property holds spacing between icon and label

##Signals

###**clicked**

This signal will be emitted when `BigIcon` is clicked



