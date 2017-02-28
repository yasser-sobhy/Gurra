##AnaView is simply a ListView item with some default properties.

All default properties can be modified.

       ListView
        {
            anchors.fill: parent
            anchors.margins: app.margins.normal
            spacing: app.spacing.large
            visible: count > 0 // only show if ListView has items
        }
    
#Example

      AnaView
      {
           id: myView    
	       delegate: MyDelegate {
                Component.onCompleted: {
                    console.log("Hello Gurra!")
                }
            }
        }

