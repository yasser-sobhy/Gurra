
#AppColors object groups some frequently used color names  to increase readability and avoid mistyping.


##Available Colors

    primary: black
    background: grey
    string foreground: grey
    accent: "red"

    primaryFont: "black"
    secondaryFont: "black"
    accentFont: "white"

	// these to increase readability and avoid mistyping  
	
    white: "white"
    black: "black"

    cyan: "cyan"
    darkCyan: "darkCyan"

    red: "red"
    darkRed: "darkRed"

    magenta: "magenta"
    darkMagenta: "darkMagenta"

    green: "green"
    darkGreen: "darkGreen"

    yellow: "yellow"
    darkYellow: "darkYellow"

    orange: "orange"
    darkOrange: "darkOrange"

    blue: "blue"
    darkBlue: "darkBlue"

    grey: "grey"
    darkGrey: "darkGrey"
    lightGrey: "lightGrey"

    transparent: "transparent" 

**Usage:**

    Text
    {
        id: _icon
        font.pointSize: app.sizes.h6
        color: app.colors.blue
    }
     
**Defining Custom Colors**

   */Custom/Colors.qml*
    
    import QtQuick 2.0
    import Gurra 1.0
    
    AppColors
    {
        primary: "#090050"
        background: googlePalette.grey200
        foreground: app.colors.black
        accent: "#89beff"
     }

*main.qml*

    import "customs" as Custom
    App
    {
        id: app
        colors: Custom.Colors{}
    }

