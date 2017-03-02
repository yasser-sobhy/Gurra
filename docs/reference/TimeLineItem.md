#TimeLineItem represents a content inside a `TimeLine`


    TimeLineItem
    {
        timeLine: carTimeLine
        title.text: qsTr("Year")
        step.text: "1"
    
        icon.icon: app.icons.fontAwesome.calendar
        editIcon.icon: app.icons.fontAwesome.pencil
    
        contentItem: Label {
            anchors.left: parent.left
            color: app.colors.darkGrey
        }
    
        onEdit: console.log("edit icon clicked")
    }

##Properties

###**timeLine**: TimeLine
This property holds a reference to the `TimeLine` containing this `TimeLineItem` 

###**contentItem**: Item
This property holds the content item of this `TimeLineItem` 

###**step**: Text
This property holds the step text of this `TimeLineItem` 

###**icon**:  Icon
This property holds the icon of this `TimeLineItem` 

###**editIcon**: Icon
This property holds the edit icon of this `TimeLineItem` 

###**title**: Label
This property holds the title this `TimeLineItem` 

###**wideClick**: bool 

    default: true

If true, clicking anywhere inside `contentItem` will emit `edit` signal


##Signals

###**edit**
This signal will be emitted when `editIcon` is clicked or when `contentItem` is clicked if `wideClick` is true

