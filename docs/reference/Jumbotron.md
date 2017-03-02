#A convenient component to add a back color to items. It is a simple rectangle with width set to `parent.width` and color set to `app.colors.white`


    Jumbotron {
    
        anchors.fill: parent
        anchors.margins: app.margins.normal
        
        color: app.colors.red
    
        Label {
    		anchors.centerIn: parent
    		color: app.colors.white
    		text:  "Hello Gurra"
    	}
    }

