#Background is a convenient component to be used add a background to an item

Instead of 

    Rectangle {
        anchors.fill: parent
        color: app.colors.background
    }

Simply use

    Background {}
    
This makes it obvious that you are adding a background to user component

