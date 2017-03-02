#Icon 

Displays  an icon with default color set to `app.colors.foreground`, font `app.iconFonts.primary` and size set to `app.sizes.h6`

        Icon {
            icon: app.icons.fontAwesome.heart
            onClicked: {
	            //do something
            }
        }
        
###**icon**: string
This property holds the icon to be displayed

    icon: app.icons.fontAwesome.heart

###**backcolor**: string

    default: app.colors.transparent

This property holds Icon back color

###**background**: Rectangle
This property holds a reference to `Icon` internal background 

##Signals
 
###**clicked**

This signal is emitted when icon is clicked
