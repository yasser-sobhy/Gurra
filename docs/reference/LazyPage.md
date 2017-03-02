#LazyPage delays loading a page until app is fully loaded and shown to the user

##LazyPage pages may have `high` or `low`*(default)* priority to control when page should be loaded. Pages With `high` priority will be loaded immediately after `main.qml` is fully loaded and shown to the user. Pages With `low` priority will be loaded when pushed on App's main StackView using `app.pushPage()`

> `LazyPage` can be only used through  `app.pushPage()` to ensure they are loaded before pushed on StackView

    property LazyPage search: LazyPage{
	    priority: high
        source: "qrc:/qml/pages/Search.qml"
    }
    property LazyPage contactUsPage: LazyPage{
        source: "qrc:/qml/pages/ContactUsPage.qml"
    }
    property LazyPage aboutPage: LazyPage{
        source: "qrc:/qml/pages/AboutPage.qml"
    }
    
##Properties

###**params**: var

    default: ({}) 

This property holds parameters to be passed to the page when loaded

		//search_query is a property in app.pages.search
        app.pages.search.params.search_query = "some query"
        app.pushPage(app.pages.search)

###**priority**:  int

    default: low

This property holds the priority of loading the page.  Pages With `high` priority will be loaded immediately after `main.qml` is fully loaded and shown to the user. Pages With `low` priority will be loaded when pushed on App's main StackView using `app.pushPage()`

###**high**: 0
Use this property to change `priority`

###**low**: 1
Use this property to change `priority`

##Signals

###**ready**
This signal will be emitted when the lazy page is fully loaded