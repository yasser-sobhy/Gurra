#Thumbnail displays a small sized image


    default width: app.sizes.xxxLarge * 3
    default height: app.sizes.xxxLarge * 3
    default fillMode: Image.PreserveAspectFit

###Example

        Thumbnail {
            id: thumb
            picture: uploadThumbnail.picture
            fillMode: Image.Stretch
            onClicked: console.log("Thumbnail clicked")
        }
        

##Properties

###**marker**: string
This property holds a number or a string to be displayed if no image loaded

###**picture**: string
This property holds the path of the image to be displayed

##Signals

###**clicked**
This signal will be emitted when `Thumbnail` is clicked
