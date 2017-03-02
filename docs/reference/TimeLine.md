#TimeLine displays a list of `TimeLineItem`s as a timeline 

     TimeLine
        {
            id: carTimeLine
            anchors.fill: parent
            anchors.margins: app.margins.normal
    
            elements: [
    
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
    
                    onEdit: console.log("select a year")
                },
    
                TimeLineItem
                {
                    timeLine: carTimeLine
                    title.text: qsTr("Brand")
                    step.text: "2"
    
                    icon.icon: app.icons.fontAwesome.flag
                    editIcon.icon: app.icons.fontAwesome.pencil
    
                    contentItem: Label {
                        anchors.left: parent.left
                        color: app.colors.darkGrey
                    }
    
                    onEdit: console.log("select a brand")
                },
    
                TimeLineItem
                {
                    timeLine: carTimeLine
                    title.text: qsTr("Model")
                    step.text: "3"
    
                    icon.icon: app.icons.fontAwesome.asterisk
                    editIcon.icon: app.icons.fontAwesome.pencil
    
                    contentItem: Label {
                        color: app.colors.darkGrey
                    }
    
                    onEdit:  console.log("select a model")
                },
       
                TimeLineItem
                {
                    timeLine: carTimeLine
                    title.text: qsTr("Color")
                    step.text: "5"
                    wideClick: false
    
                    icon.icon: app.icons.fontAwesome.paint_brush
    
                    contentItem: TextField {
                        id: colorInput
                        anchors.left: parent.left
                        width: parent.width
                        placeholderText: qsTr("color")
                    }
                },
    
                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Next")
        
                    onClicked: {
                        app.pushPage(app.pages.somePage)
                    }
                }
            ]
        }
        

##Properties

###**stepTextWidth**: real 

    default: app.margins.xLarge * 2

This property holds the width of the `TimeLineItem`'s step text  

###**stepTextMargin**: real

     default: app.margins.small * 2

This property holds the margins arround `TimeLineItem`'s step text  

###**lineSpacing**: real

     default: app.margins.xLarge

This property holds the spacing between `TimeLine`'s vertical line and `TimeLineItem`'s

###**lineWidth**:  real

    default: 2

This property holds the width of the `TimeLine`'s vertical line  

###**spacing**:  real

    default: app.margins.large

This property holds the spacing between `TimeLineItem`'s  in `TimeLine`

###**linePadding**:  real

    default: stepTextWidth + stepTextMargin

This property holds the padding between TimeLine's left edge and it's vertical line

###**contentPading**:  real 

    default: linePadding + lineSpacing + lineWidth

This property holds the padding from`TimeLine`'s left edge to  `TimeLineItem`'s

###**elements**: Array
This property holds an array of `TimeLineItem`'s to be displayed  