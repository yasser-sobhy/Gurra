   
#App is Gurra's root component, it manages the lifecycle of a Gurra app.

    import QtQuick 2.7
	import QtQuick.Controls 2.0
	import QtQuick.Controls.Material 2.0
	import Org.Yasser.Gurra 1.0
	import Gurra 1.0

	import "qrc:/qml"
	import "qrc:/qml/pages"

	import "popups"
	import "customs" as Custom
	
    App
    {
        id: app
        title: qsTr("Hello Gurra!")
        view: mainStack
    
        api: Custom.Api{}
        logic: Custom.Logic{}
        pages: Custom.Pages{}
        colors: Custom.Colors{}
        urls: Custom.Urls{}
        headers: Custom.Headers{}
        models: Custom.Models{}
        settings: Custom.Settings{}
        params: Custom.Params{}
        fonts: Custom.Fonts{}
   
        production: true
       }

   
#Properties
   
  **production**: bool

      default: true
      
This property holds whether the app is running in production mode or debug mode.

  **api**: QtObject
  
  This property holds all app restful api 
  

    var user = {
    			  name: 'Jhon Due',
    			  email: 'some.email@example.com',
    			  password: 'pass'
    			}
    			
    app.api.users.create(user).then(function(response){
    	          console.log(response)
            })
        
  **logic**: QtObject

This property holds all app logic 

    app.logic.login(user_id)

 **pages**: Item
 
 This property holds all app pages

    app.pushPage(app.pages.search)

 
 **headers**: Item
 
  This property holds headers for all pages of the app
  

    import QtQuick 2.7
    import QtQuick.Layouts 1.1
    import QtQuick.Controls 2.0
    import QtQuick.Controls.Material 2.0
    
    import Gurra 1.0
    
    AnaPage
    {
        header: app.headers.search
    }

 > **See** footers

 **footers**: Item

  This property holds footer for all pages of the app

> **See** headers

 **Urls** urls: 
  This property holds all urls of the app

      default: Urls{}

Example: 

    Image {
            Layout.fillWidth: true
            Layout.fillHeight: true
            fillMode: Image.PreserveAspectFit
            source = app.urls.pictures + image_id
     }

  **fonts**:  Fonts

      default: Fonts{}

This property holds all app loaded fonts

*/Custom/Fonts.qml*

    Fonts
    {
        property string digital: _digital.name
    
        FontLoader
        {
            id: _digital
            source: "qrc:/assets/fonts/DS-DIGI.TTF"
        }
    }

*main.qml*

    import "customs" as Custom
    App
    {
        id: app
       fonts: Custom.Fonts{}
    }

*Usage*

        Label
        {
            text: qsTr("Volla!!")
            font.pointSize: app.sizes.h5
            color: app.colors.white
            font.family: app.fonts.digital
        }


  **icons**: Icons

      default: Icons{}

This property holds all available app icons


  **iconFonts**: IconFonts

      default: IconFonts{}
      
This property holds all available icon fonts. Icon fonts can be used to display icons for labels and buttons. Gurra provides all icon fonts availabe at https://icomoon.io/

> Note: only fontAwesome and icomoon fonts are loaded by default, you can load
> other icon fonts easily.

Available fonts 

    primary: fontAwesome // default icon font
    afiado
    brankit
    entipoPlus
    feather
    fontAwesome
    hawcons
    icomoon
    linecons
    material
    meteocons
    octicons
    typicons
    wpzoom

Loading other icon fonts

/Custom/Fonts.qml

    IconFonts // inherit default icon fonts
    {
    	meteocons: myloader.name // let meteocons refer to loaded font name
    	
        FontLoader
        {
            id:  myloader
            source: meteocons_file // meteocons_file is a IconFonts property and holds the path of the font file in Gurra's assets
        }
    }
    
   // main.qml
    
	import "customs" as Custom

    App
    {
        id: app
        iconFonts: Custom.IconFonts{}
    }
    
   Usage:

    Icon
    {
      font.pointSize: app.sizes.h3
      color: app.colors.foreground
      font.family: app.iconFonts.meteocons
    }

  **colors**: AppColors

      default: AppColors{}
This property all app colors available:

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

Usage:

    Text
    {
        id: _icon
        font.pointSize: app.sizes.h6
        color: app.colors.blue
    }
     
Custom Colors

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

  **soundEffects**: SoundEffects

      default: undefined

This property holds app avialable sound effects

  **margins**: Margins

      default: Margins{}

A convenient type that holds some margins sizes

Available sizes:

    none: 0

    xxSmall: 1
    xSmall: 3

    normal: 10
    small: 5
    medium: 15
    large: 20

    xLarge: 30
    xxLarge: 40
    xxxLarge: 50

Usage:

    import QtQuick 2.0
    
    Rectangle {
        anchors.fill: parent
        anchors.margins: app.margins.large // instead of hardcoding 20
        color: app.colors.primary
    }


  **spacing**: Spacing

      default: Spacing{}

A convenient type that holds some spaces sizes

Available sizes:

    none: 0

    xxSmall: 1
    xSmall: 3

    normal: 10
    small: 5
    medium: 15
    large: 20

    xLarge: 30
    xxLarge: 40
    xxxLarge: 50
    
Usage:

        Column
        {
            spacing: app.spacing.small

            Label
            {
                text: "Hello Gurra!"
            }

            Row
            {
                height: app.sizes.xxLarge
                spacing: app.spacing.large

                IconLabel
                {
                    spacing: app.spacing.xSmall

                    icon.icon: app.icons.fontAwesome.map_marker
                    icon.color: app.colors.background
                    icon.font.pointSize: app.sizes.h4

                    label.text: "IconLabel"
                    label.font.pointSize: app.sizes.h4
                    label.color: app.colors.primary
                }

                IconLabel
                {
                    spacing: app.spacing.xSmall

                    icon.icon: app.icons.fontAwesome.clock_o
                    icon.color: app.colors.background
                    icon.font.pointSize: app.sizes.h4

                    label.text: "IconLabel"
                    label.font.pointSize: app.sizes.h5
                    label.color: app.colors.primary
                }
            }
        }
        
  **sizes**: Sizes

      default: Sizes{}

A convenient type that holds some sizes

Available sizes:

      default: Sizes{}
      
    none: 0

    xxSmall: 6
    xSmall: 8

    normal: 12
    small: 10
    medium: 14
    large: 16

    xLarge: 20
    xxLarge: 24
    xxxLarge: 28

    h1: 28
    h2: 24
    h3: 18
    h4: 14
    h5: 12
    h6: 10

    h7: 8
    h8: 6

Usage:

    import QtQuick 2.0
    import Gurra 1.0
    
    Icon {
        color: app.colors.accent
        font.pointSize: app.sizes.h1
    }

  **settings**: Settings

      default:

  **strings**: Strings

      default: Strings{}
This property holds common used strings like Ok, Yes, No, Cancel and so on

> Important: This property may be removed from the next release

  **models**: var

      default: undefined
      
This property holds app available data models 

/Custom/Models.qml

    Item
    {
        property var yesNo: [qsTr("Yes"), qsTr("No")]
        property var kmMile: [qsTr("KM"), qsTr("Mile")]
        property var cities: ["Cairo", "Tokyo", "Paris", "New York"]
        property var colors: [qsTr("Blue"), qsTr("White"), qsTr("Green"), qsTr("Yellow"), qsTr("Red"), qsTr("Orange"), qsTr("Black"), qsTr("Brown"), qsTr("Orange")]
    }
main.qml

    import "customs" as Custom
    
    App
    {
        id: app
        models: Custom.Models{}
    }
    
Usage: 

    app.pick(qsTr("Select City"), app.models.cities, function(index, city){
                        console.log("you selected", index, city)
                    })

  **params**: Params

      default: Params{}
This property holds all dialog params available 

import QtQuick 2.0
import Gurra 1.0

Params
{
    property DialogParams logout: DialogParams {
        title: qsTr("Logout")
        message: qsTr("Are you sure you want to logout?")
        button1: qsTr("Yes")
        button2: qsTr("No")
        yesCallback: function(){
            app.logic.logout()
            app.replacePage([app.pages.home])
        }
    }

   property DialogParams invalidEmail: DialogParams {
        title: qsTr("Invalid")
        message: qsTr("Please type a valid email.")
        button1: qsTr("Ok")
    }

   property DialogParams deletePic: DialogParams {
        title: qsTr("Delete?")
        message: qsTr("Are you sure you want to delete your picture?")
        button1: qsTr("Ok")
        button2: qsTr("Cancel")
    }

main.qml

    import "customs" as Custom
    
    App
    {
        id: app
        params: Custom.Params{}
    }
    
Usage: 

       app.confirm(app.params.deletePic, function(){
               app.api.pics.remove(picture_id).then(function(){
                      app.done()
                })
    })



  **layoutDirection**: int

      default: Qt.LeftToRight
      
This property holds the default layout direction of the app

  **layoutMirroring**: bool

      default: false
      
This property holds whether layout mirroring is enabled or not

  **childrenInherit**: bool

      default: false
      
This property holds whether items children should inherit layout mirroring is enabled or not

  **confirmExit**: bool

      default: false
      
If true, App will confirm the user before exit

  **view**: StackView

      default:
      
This property holds the main StackView of the app. Gurra page routing currently supports StackView only

  **restConsumer**: RestConsumer2

      default: RestConsumer2 {}

This property holds the central RESFful network consumer, all Gurra componets use this RestConsumer2 to connect to restful services to do GET, POST, PUT or DELETE operations

  **restConsumer3**: RestConsumer3

      default: RestConsumer3 {}
This property holds the central upload RESFful consumer, it's used by Uploader to upload files 

 
#Functions
 

   **ready(callback)**
   **pushPage (page, params)**
   **popPage (page)**
   **replacePage (pages)**
   **back ()**
   **snack(message, action, actionCallback)**
   **inform(params, yesCallback, noCallback)**
   **message(title, message, button, okCallback)**
   **confirm2(params, yesCallback, noCallback)**
   **confirm(params, yesCallback, noCallback)**
   **done()**
   **loading(message)**
   **notLoading()**
   **input(params, yesCallback, noCallback)** 
   **inputNumber(params, yesCallback, noCallback)**
   **inputDate(params, yesCallback, noCallback)**
   **inputTime(params, yesCallback, noCallback)**
   **inputPhone(params, yesCallback, noCallback)**
   **inputEmail(params, yesCallback, noCallback)**
   **inputMultiline(params, yesCallback, noCallback)**
   **inputUrl(params, yesCallback, noCallback)**
   **pick(title, model, callback)**
