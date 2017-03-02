#Lazy delays loading app components until app is fully loaded and shown to the user

##Lazy items may have `high` or `low`*(default)* priority to control when items should be loaded. Items With `high` priority will be loaded before items with `low` priority

> `Lazy` Items will be loaded when calling `app.ready()`

    Lazy {
        id: colorLazy
        source: "qrc:/qml/popups/ColorPicker.qml"
    }
	
	// with high priority
    Lazy {
        id: rightDrawerLazy
        priority: high
        source: "qrc:/qml/RightDrawer.qml"
    }
    
##Properties

###**priority**:  int
This property holds the priority of loading the item. Items With `high` priority will be loaded before items with `low` priority

    default: low

###**high**: 0
Use this property to change `priority`

###**low**: 1
Use this property to change `priority`

##Signals

###**ready**
This signal will be emitted when the lazy item is fully loaded
