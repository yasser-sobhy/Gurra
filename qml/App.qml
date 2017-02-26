import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.1
import QtMultimedia 5.6
import Qt.labs.settings 1.0

import Gurra 1.0
import Org.Yasser.Gurra 1.0

ApplicationWindow
{
    property bool production: true

    property QtObject api
    property QtObject logic
    property Item pages
    property Item headers
    property Item footers
    property Urls urls: Urls{}

    property Fonts fonts: Fonts{}
    property Icons icons: Icons{}
    property IconFonts iconFonts: IconFonts{}
    property AppColors colors: AppColors{}

    property SoundEffects soundEffects

    property Margins margins: Margins{}
    property Spacing spacing: Spacing{}
    property Sizes sizes: Sizes{}

    property Device device: Device{}
    property Settings settings
    property Strings strings: Strings{}

    property var models
    property Params params: Params{}

    property int layoutDirection: Qt.LeftToRight
    property bool layoutMirroring: false
    property bool childrenInherit: false

    property bool confirmExit: false

    property StackView view

    property var p1_lazies_pages: []
    property var p1_lazies: []
    property var p2_lazies: []

    function addP1LazyPage(lazy_page) {p1_lazies_pages.push(lazy_page)}
    function addP1Lazy(lazy) {p1_lazies.push(lazy)}
    function addP2Lazy(lazy) {p2_lazies.push(lazy)}

    function _ready(callback){

        //load app ui componnts first
        uiLazy.active = true

        // load lazy items with high priority
        for(var i = 0; i < p1_lazies.length; i++) {
            p1_lazies[i].active = true
        }

        // load lazy items with low priority
        for(var ii = 0; ii < p2_lazies.length; ii++) {
            p2_lazies[ii].active = true
        }

        // load lazy pages with high priority. Low priority pages will be loaded when pushed
        for(var iii = 0; iii < p1_lazies_pages.length; iii++) {
            console.log("loading", p1_lazies_pages[iii].source)
            p1_lazies_pages[iii].active = true
        }

        if(callback) callback()
    }

    function ready(callback){
        Qt.callLater(_ready, callback)
    }

    //    property var pushPage
    //    property var replacePage
    //    property var popPage

    //    property var back

    function pushPage (page, params){

        if(view.currentItem !== page){

            var _page = page

            if(page._is_lazy){

                if(page.status === Loader.Ready) _page = page.item
                else {
                    console.log("App: loading page", page.source)
                    page.asynchronous = false // load this page immadiately
                    page.active = true
                    _page = page.item
                }

                params = page.params
            }

            _page.beforeEnter()
            view.push(_page, params)
            _page.enter()
        }

    }

    function popPage (page){
        if(page) page.beforeLeave()
        view.pop()
        if(page) page.leave()
    }

    function replacePage (pages){

        if(view.currentItem !== pages){
            var pre = view.currentItem
            pre.beforeLeave()
            view.replace(null, pages)
            pre.leave()
        }
    }

    function back (){

        if(view.depth > 1) {
            view.pop()
            event.accepted = true
        }
        else if(confirmExit) {
            app.confirm(app.params.exit, function(){ Qt.quit()})
        }
        else Qt.quit()
    }


    property RestConsumer2 restConsumer: RestConsumer2 {}
    property RestConsumer3 restConsumer3: RestConsumer3 {}

    function snack(message, action, actionCallback)
    {
        ui.snackbar.message = message
        if(action) ui.snackbar.action = action
        if(actionCallback) ui.snackbar.actionCallback = actionCallback
    }

    function inform(params, yesCallback, noCallback)
    {
        if(yesCallback) params.yesCallback = yesCallback
        if(noCallback) params.noCallback = noCallback

        ui.msg.options = params
        ui.msg.open()
    }

    function message(title, message, button, okCallback)
    {
        // reset
        ui._msg.options.button1 = qsTr("Ok")
        ui._msg.options.yesCallback = undefined

        if(okCallback) ui._msg.options.yesCallback = okCallback
        if(button) ui._msg.options.button1 = button

        ui._msg.options.title = title
        ui._msg.options.message = message
        ui._msg.open()
    }

    function confirm2(params, yesCallback, noCallback)
    {
        ui.cnfrm.options.button2 = ""
        ui.cnfrm.options.noCallback = undefined

        // override yesCallback and noCallback if passed
        if(yesCallback) params.yesCallback = yesCallback
        if(noCallback) params.noCallback = noCallback

        // no check, these are mandatory
        ui.cnfrm.options.title = params.title
        ui.cnfrm.options.message = params.message
        ui.cnfrm.options.button1 = params.button1
        ui.cnfrm.options.yesCallback = params.yesCallback

        if(params.button2) ui.cnfrm.options.button2 = params.button2
        if(params.noCallback) ui.cnfrm.options.noCallback = params.noCallback

        ui.cnfrm.open()
    }

    function confirm(params, yesCallback, noCallback)
    {
        if(yesCallback) params.yesCallback = yesCallback
        if(noCallback) params.noCallback = noCallback

        ui.cnfrm.options = params
        ui.cnfrm.open()
    }

    function done()
    {
        ui.done.open()
    }

    function loading(message)
    {
        if(message) ui.loading.message = message
        else ui.loading.message = "" //reset message

        ui.loading.open()
    }

    function notLoading()
    {
        ui.loading.close()
    }

    function _input(params, yesCallback, noCallback)
    {
        if(yesCallback) params.yesCallback = yesCallback
        if(noCallback) params.noCallback = noCallback

        ui.valueInput.options = params
        ui.valueInput.open()
    }

    function input(params, yesCallback, noCallback)
    {
        ui.valueInput.inputMethodHints = Qt.ImhNone
        _input(params, yesCallback, noCallback)
    }

    function inputNumber(params, yesCallback, noCallback){
        ui.valueInput.inputMethodHints = Qt.ImhDigitsOnly
        _input(params, yesCallback, noCallback)
    }

    function inputDate(params, yesCallback, noCallback){
        ui.valueInput.inputMethodHints = Qt.imhDate
        _input(params, yesCallback, noCallback)
    }

    function inputTime(params, yesCallback, noCallback){
        ui.valueInput.inputMethodHints = Qt.ImhTime
        _input(params, yesCallback, noCallback)
    }

    function inputPhone(params, yesCallback, noCallback){
        ui.valueInput.inputMethodHints = Qt.ImhDialableCharactersOnly
        _input(params, yesCallback, noCallback)
    }

    function inputEmail(params, yesCallback, noCallback){
        ui.valueInput.inputMethodHints = Qt.ImhEmailCharactersOnly
        _input(params, yesCallback, noCallback)
    }

    function inputMultiline(params, yesCallback, noCallback){
        ui.valueInput.inputMethodHints = Qt.ImhMultiLine
        _input(params, yesCallback, noCallback)
    }

    function inputUrl(params, yesCallback, noCallback){
        ui.valueInput.inputMethodHints = Qt.ImhUrlCharactersOnly
        _input(params, yesCallback, noCallback)
    }

    function pick(title, model, callback)
    {
        if(callback) ui.picker.callback = callback

        ui.picker.title = title
        ui.picker.model = model
        ui.picker.open()
    }

    Material.theme: Material.Light
    Material.accent: app.colors.accent
    Material.primary: app.colors.primary
    Material.background: app.colors.background
    Material.foreground: app.colors.foreground


    width: 621
    height: 1104
    visible: true

    property AppUi ui: uiLazy.item

    Lazy {
        id: uiLazy
        source: "/home/yasser/Qt/5.7/gcc_64/qml/Gurra/AppUi.qml"
        asynchronous: false
        priority: high
    }

    Connections {
        target: GuGui
        onBack: back()
    }
}

