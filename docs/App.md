   
#App is Gurra's root component it manages the lifecycle of a Gurra app.

#Properties
   
  **production**: bool

      default: true
      
 Defines whether is app is running in production mode or debug mode. Most useful when working app urls 

  **api**: QtObject
  
  Contains all app restful api 
  
  **logic**: QtObject

A wrapper for all app logic 

 **pages**: Item
 
 Conatins all app pages
 
 **headers**: Item
 
  This property holds headers for all pages of the app
 > **See** footers

 **footers**: Item

  This property holds footer for all pages of the app

> **See** headers

 **Urls** urls: 
  Contains all urls of the app

      default: Urls{}

  **fonts**:  Fonts

      default: Fonts{}

  **icons**: Icons

      default: Icons{}

  **iconFonts**: IconFonts

      default: IconFonts{}

  **colors**: AppColors

      default: AppColors{}

  **soundEffects**: SoundEffects

      default: undefined

  **margins**: Margins

      default: Margins{}

  **spacing**: Spacing

      default: Spacing{}

  **sizes**: Sizes

      default: Sizes{}

  **settings**Settings

      default:

  **strings**: Strings

      default: Strings{}

  **models**: var

      default:

  **params**: Params

      default: Params{}

  **layoutDirection**: int

      default: Qt.LeftToRight

  **layoutMirroring**: bool

      default: false

  **childrenInherit**: bool

      default: false

  **confirmExit**: bool

      default: false

  **view**: StackView

      default:

  alias ui: uiLazy.item
  var p1_lazies_pages: []
  var p1_lazies: []
  var p2_lazies: []
  **restConsumer**: RestConsumer2

      default: RestConsumer2 {}

  **restConsumer3**: RestConsumer3

      default: RestConsumer3 {}

 
#Functions
 
   function addP1LazyPage(lazy_page) {p1_lazies_pages.push(lazy_page)}
   function addP1Lazy(lazy) {p1_lazies.push(lazy)}
   function addP2Lazy(lazy) {p2_lazies.push(lazy)}
   function ready(callback)
   function pushPage (page, params)
   function popPage (page)
   function replacePage (pages)
   function back ()
   function snack(message, action, actionCallback)
   function inform(params, yesCallback, noCallback)
   function message(title, message, button, okCallback)
   function confirm2(params, yesCallback, noCallback)
   function confirm(params, yesCallback, noCallback)
   function done()
   function loading(message)
   function notLoading()
   function _input(params, yesCallback, noCallback)
   function input(params, yesCallback, noCallback) 
   function inputNumber(params, yesCallback, noCallback)
   function inputDate(params, yesCallback, noCallback)
   function inputTime(params, yesCallback, noCallback)
   function inputPhone(params, yesCallback, noCallback)
   function inputEmail(params, yesCallback, noCallback)
   function inputMultiline(params, yesCallback, noCallback)
   function inputUrl(params, yesCallback, noCallback)
   function pick(title, model, callback)





















