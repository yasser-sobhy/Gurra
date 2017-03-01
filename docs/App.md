   
#App is Gurra's root component. It manages the lifecycle of a Gurra app.

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
   
###**production**: bool

      default: true
      
This property holds whether the app is running in production mode or debug mode.

Gurra make no use of this property internally right now, but you may use it to change the behavior of your code depending whether it is running in production or debug

    Urls
    {
        root: app.production? "http://www.example.com:8080" :   http://localhost:8080"
        
        pictures: app.production? "http://example.com/uploads/" : "http://localhost/uploads/"
    }

###**api**: QtObject
  
  This property holds all app restful api.

Following the structure of Gurra app, you are encouraged to put your network-related code in one .qml file and reference this file using `api` property, this makes your code more readable and easily maintainable.
  

**Example**:

    var user = {
    			  name: 'Jhon Due',
    			  email: 'some.email@example.com',
    			  password: 'pass'
    			}
    			
    // use app.api to access network-related code			
    app.api.users.create(user).then(function(response){
    	          console.log(response)
            })
        
###**logic**: QtObject

This property holds all app logic 

Just like `api`, following the structure of Gurra app, you are encouraged to put your logic code in one .qml file and reference this file using `logic` property, this makes your code more readable and easily maintainable.

	// log user in
    app.logic.login(user_id)
    
	// do somthing
	app.logic.doSomthing()

###**pages**: Item
 
 This property holds all app pages

*/Custom/Pages.qml*

    import QtQuick 2.0
    
    import Gurra 1.0
    import "../pages"
    
    Item
    {
        property Home home: Home{} // not lazy, need to be loaded at startup
    
	    // lazy pages will be loaded when pushed using app.pushPage()
	    
	    //lazy pages with high priority will be loaded after main.qml is loaded
	    
        property LazyPage contactUsPage: LazyPage{
            source: "qrc:/qml/pages/ContactUsPage.qml"
        }
        property LazyPage aboutPage: LazyPage{
            source: "qrc:/qml/pages/AboutPage.qml"
        }
        property LazyPage loginPage: LazyPage{
            source: "qrc:/qml/pages/LoginPage.qml"
        }
        property LazyPage joinUser: LazyPage{
            source: "qrc:/qml/pages/JoinUser.qml"
        }
        property LazyPage search: LazyPage{
            priority: high //load this after laoding main.qml
            source: "qrc:/qml/pages/Search.qml"
        }
    }
    
   *main.qml*

    import "customs" as Custom
    App
    {
        id: app
       pages: Custom.Pages{}
    }

**Usage**:

    app.pushPage(app.pages.search)

 
###**headers**: Item
 
  This property holds headers for all app pages
  
  */Custom/Headers.qml*

    import QtQuick 2.5
    import Gurra 1.0
    
    Item {
    
        property PageTitle home: PageTitle {
            title: qsTr("Gurra")
            onClose: app.popPage()
        }
    
        property PageTitle listings: PageTitle {
            title: qsTr("Listings")
            rightIcon: app.icons.fontAwesome.bars
            onClose: app.popPage()
        }
    
        property PageTitle search: PageTitle {
            title: qsTr("Search")
            onClose: app.popPage()
        }
    
        property PageTitle contactUs: PageTitle {
            title: qsTr("Contact Gurra")
            onClose: app.popPage()
        }
    
        property PageTitle imageUploader: PageTitle {
            title: qsTr("Images")
            onClose: app.popPage()
        }
        
        property PageTitle about: PageTitle {
            title: qsTr("About Mzadat")
            onClose: app.popPage()
        }
    
        property PageTitle joinUser: PageTitle {
            title: qsTr("Join Gurra")
            onClose: app.popPage()
        }
    
        property PageTitle login: PageTitle {
            title: qsTr("Login")
            onClose: app.popPage()
        }
    }
   
*main.qml*

    import QtQuick 2.7
    import QtQuick.Layouts 1.1
    import QtQuick.Controls 2.0
    import QtQuick.Controls.Material 2.0
   
*/Pages/Search.qml*
 
    import Gurra 1.0
   
    AnaPage
    {
        header: app.headers.search
    }

 > **See** footers

###**footers**: Item

  This property holds footer for all pages of the app

> **See** headers

###**Urls** urls: 
  This property holds all urls of the app

      default: Urls{}

**Example:** 

    Image {
            Layout.fillWidth: true
            Layout.fillHeight: true
            fillMode: Image.PreserveAspectFit
            source = app.urls.pictures + image_id
     }

###**fonts**:  Fonts

      default: Fonts{}

This property holds all app loaded fonts

**Defining Custom fonts**

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

**Usage**

        Label
        {
            text: qsTr("Volla!!")
            font.pointSize: app.sizes.h5
            color: app.colors.white
            font.family: app.fonts.digital
        }


###**icons**: Icons

      default: Icons{}

This property holds all available app icons


###**iconFonts**: IconFonts

      default: IconFonts{}
      
This property holds all available icon fonts. Icon fonts can be used to display icons for labels and buttons. Gurra provides all icon fonts availabe at https://icomoon.io/

> Note: only fontAwesome and icomoon fonts are loaded by default, you can load
> other icon fonts easily.

**Available fonts** 

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

**Loading other icon fonts**

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
    
   **Usage:**

    Icon
    {
      font.pointSize: app.sizes.h3
      color: app.colors.foreground
      font.family: app.iconFonts.meteocons
    }

###**colors**: AppColors

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

###**soundEffects**: SoundEffects

      default: undefined

This property holds app avialable sound effects

###**margins**: Margins

      default: Margins{}

A convenient type that holds some margins sizes

**Available sizes:**

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

**Usage:**

    import QtQuick 2.0
    
    Rectangle {
        anchors.fill: parent
        anchors.margins: app.margins.large // instead of hardcoding 20
        color: app.colors.primary
    }


###**spacing**: Spacing

      default: Spacing{}

A convenient type that holds some spaces sizes

**Available sizes:**

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
    
**Usage**:

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
        
###**sizes**: Sizes

      default: Sizes{}

A convenient type that holds some sizes

      
  **Available sizes:**
      
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

**Usage:**

    import QtQuick 2.0
    import Gurra 1.0
    
    Icon {
        color: app.colors.accent
        font.pointSize: app.sizes.h1
    }

###**settings**: Settings

      default: undefined
      
This property holds common app settings

###**strings**: Strings

      default: Strings{}
This property holds common used strings like Ok, Yes, No, Cancel and so on

> Important: This property may be removed from the next release

###**models**: var

      default: undefined
      
This property holds app available data models 

*/Custom/Models.qml*

    Item
    {
        property var yesNo: [qsTr("Yes"), qsTr("No")]
        property var kmMile: [qsTr("KM"), qsTr("Mile")]
        property var cities: ["Cairo", "Tokyo", "Paris", "New York"]
        property var colors: [qsTr("Blue"), qsTr("White"), qsTr("Green"), qsTr("Yellow"), qsTr("Red"), qsTr("Orange"), qsTr("Black"), qsTr("Brown"), qsTr("Orange")]
    }
*main.qml*

    import "customs" as Custom
    
    App
    {
        id: app
        models: Custom.Models{}
    }
    
**Usage**: 

    app.pick(qsTr("Select City"), app.models.cities, function(index, city){
                        console.log("you selected", index, city)
                    })

###**params**: Params

      default: Params{}
      
This property holds all dialog params available 

**Defining Custom Params**

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

*main.qml*

    import "customs" as Custom
    
    App
    {
        id: app
        params: Custom.Params{}
    }
    
**Usage**: 

       app.confirm(app.params.deletePic, function(){
               app.api.pics.remove(picture_id).then(function(){
                      app.done()
                })
    })



###**layoutDirection**: int

      default: Qt.LeftToRight
      
This property holds the default layout direction of the app

###**layoutMirroring**: bool

      default: false
      
This property holds whether layout mirroring is enabled or not

###**childrenInherit**: bool

      default: false
      
This property holds whether items children should inherit layout mirroring is enabled or not

###**confirmExit**: bool

      default: false
      
If true, App will confirm the user before exit

###**view**: StackView

      default: undefined
      
This property holds the main StackView of the app. Gurra page routing currently supports StackView only

###**restConsumer**: RestConsumer2

      default: RestConsumer2 {}

This property holds the central RESFful network consumer, all Gurra componets use this RestConsumer2 to connect to restful services to do GET, POST, PUT or DELETE operations

###**restConsumer3**: RestConsumer3

      default: RestConsumer3 {}
This property holds the central upload RESFful consumer, it's used by Uploader to upload files 

 
#Functions
 

###**ready(callback)**
Loads `Lazy` items and `LazyPage`'s with `high` priority. You should call this function after the `main.qml` file has completely loaded. `callback` is optional

**Loading order:**

- `Lazy` items with `high` priority
- `Lazy` items with `low` priority 
- `LazyPage` items with `high` priority

> 	`LazyPage` items with `low` priority will be loaded by `app.pushPage()` before they get pushed onto `view`

**Usage**

    // delay creating lazy items until all app Components are ready
    Timer {
        interval: 500
        running: true
        onTriggered: {
            app.ready(function(){
	            //more startup code 
            })
        }
    }


> **Note**:  you shouldn't call this function in main.qml Component.onCompleted because Component.onCompleted running order is undefined and can not be used here.

    

###**pushPage (page)**
Pushs a page onto `view`, page can be normal `AnaPage`, `LazyPage`, or an arrays of pages (normal or lazy or mixed)

    app.pushPage(app.pages.search)
    
If pushed page is `LazyPage` and it is not loaded it will be loaded first before pushed on the view. All parameters found in `LazyPage.params` will be passed to the loaded page

The loaded page will receive `beforeEnter` and `enter` signals before and after pushed on the view respectively .

###**popPage (page)**
Pops a page off `view`, page can be normal `AnaPage`, `LazyPage`, or an arrays of pages (normal or lazy or mixed)

    app.popPage(app.pages.search)

The popped off page will receive `beforeLeave` and `leave` signals before and after popped off the view respectively .

###**replacePage (pages)**
Replaces all pages in `view` with `pages`, `pages` can be normal `AnaPage`, `LazyPage`, or an arrays of pages (normal or lazy or mixed)

    app.replacePage([app.pages.search, app.pages.login])

The current page of `view` will receive `beforeLeave` and `leave` signals before and after popped off the view respectively .

###**back ()**
Pops a page off `view`. No`beforeLeave` nor `leave` signals will be emited
 
###**snack(message, action, actionCallback)**
Displays a Snackbar at the bottom of the app

    app.snack(qsTr("Deleted message"), "UNDO", function(){
		    console.log("undoing...")
	   })
If `action` was provided `actionCallback` signal will be emited if users clicks on the action label

###**inform(params, yesCallback, noCallback)**
Displays a popup to inform the user 
 

     if (app.settings.member_id === 0){
          app.inform(app.params.loginFirst)
          return
        }

> **Note**: if provided, `yesCallback` and `noCallback` will override `params.yesCallback` and `params.noCallback`

###**message(title, message, button, okCallback)**
Displays a popup to inform the user 
 
    app.message(qsTr("Error"), qsTr("Select at least one image."), function(){
		console.log("will be called when popup is dismissed ")
	})

###**confirm(params, yesCallback, noCallback)**
Displays a confirmation dialog 
	
	/Custom/Params.qml
    property DialogParams logout: DialogParams {
        title: qsTr("Logout?")
        message: qsTr("Are you sure you want to logout?")
        button1: qsTr("Yes")
        button2: qsTr("No")
        yesCallback: function(){
            app.logic.logout()
            app.replacePage([app.pages.home])
        }
    }
    
    //usage
    app.confirm( app.params.logout )

> **Note**: if provided, `yesCallback` and `noCallback` will override `params.yesCallback` and `params.noCallback`

###**confirm2(params, yesCallback, noCallback)**
Displays a confirmation dialog, just like `confirm` but params are a JavaScript object instead of DialogParams.

    var params = {
        title: qsTr("Delete image?"),
        message: qsTr("Are you sure you want to delete this image?"),
        button1: qsTr("Yes"),
        button2: qsTr("No")
    }
    app.confirm2(params, function(){
            app.api.images.remove(image_id).then(function(){
                app.done()
            },
            function(){
                app.inform(app.params.imageDeleteError)
            })
    })
    
> **Note**: if provided, `yesCallback` and `noCallback` will override `params.yesCallback` and `params.noCallback`

###**done()**
Displays a popup to inform the user that an operation has been done

###**loading(message)**	
Displays a loading popup with BusyIndicator item along with `message`, `message` is optional

    app.loading()

###**notLoading()**
Hides the loading popup

    app.notLoading()

###**input(params, yesCallback, noCallback)** 
Displays an input dialog to allow user to enter data

**Example**:

	//add this to /Custom/Params.qml
    property DialogParams age: DialogParams {
        title: qsTr("Enter you name")
        message: qsTr("e.g. 60")
        button1: qsTr("Ok")
        button2: qsTr("Cancel")
    }
	
	// usage
	app.input(app.params.age, function(value){
		console.log("your age is", value)
	}

> **Note**: the `inputMethodHints` property of the text field is set to `Qt.ImhNone`

###**inputNumber(params, yesCallback, noCallback)**
Same as `input` with `inputMethodHints` property set to `Qt.ImhDigitsOnly`

###**inputDate(params, yesCallback, noCallback)**
Same as `input` with `inputMethodHints` property set to `Qt.imhDate`

###**inputTime(params, yesCallback, noCallback)**
Same as `input` with inputMethodHints property set to Qt.ImhTime

###**inputPhone(params, yesCallback, noCallback)**
Same as `input` with `inputMethodHints` property set to `Qt.ImhDialableCharactersOnly`

###**inputEmail(params, yesCallback, noCallback)**
Same as `input` with `inputMethodHints` property set to `Qt.ImhEmailCharactersOnly`

###**inputMultiline(params, yesCallback, noCallback)**
Same as `input` with `inputMethodHints` property set to `Qt.ImhMultiLine`

###**inputUrl(params, yesCallback, noCallback)**
Same as `input` with `inputMethodHints` property set to `Qt.ImhUrlCharactersOnly`

###**pick(title, model, callback)**
Displays a popup dialog to allow user to pick one item from `model`

    app.pick(qsTr("Select City"), app.models.cities, function(index, city){
                        console.log("you selected", index, city)
                    })

