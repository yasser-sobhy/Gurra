#Avatar displays a circular image

        Avatar
        {
            anchors.horizontalCenter: parent.horizontalCenter
            size: 200
            picture: "qrc:/assets/images/logo.png"
        }

##Properties

###**url**: string 
This property holds a prefix url to be used with `pictureID` to form image path

###**pictureID**: string
This property holds the picture file name, used in conjuction with `url`

###**size**: int

    default: app.sizes.xLarge * 5
    
This property holds Avatar size

###**picture**: string
This property holds picture full url or path

###**edit**: bool
A convenient property to switch Avatar edit mode, if `edit` is true select signal will be emitted instead of click

##Signals

###**clicked**

If `edit` is false, this signal is emitted when user clicks the avatar 

### **select**

If `edit` is true, this signal is emitted when user clicks the avatar 

