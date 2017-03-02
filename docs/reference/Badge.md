
#**Badge** is a convenient component to display an informative number. It is simply an `Icon` with `font.pointSize` set to `app.sizes.h4` 


    Badge
    {
        anchors.verticalCenter: parent.verticalCenter
            
        color: app.colors.primary
        backcolor: app.colors.accent
    
        text: "#125"
        font.bold: true
        font.pointSize: app.sizes.h6
    }