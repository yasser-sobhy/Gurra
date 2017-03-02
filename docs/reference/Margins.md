
#Margins object groups together frequently used margin sizes to increase readability and avoid mistyping.


##Available Sizes

###**none**: 0

###**xxSmall**: 1
###**xSmall**: 3

###**normal**: 10
###**small**: 5
###**medium**: 15
###**large**: 20

###**xLarge**: 30
###**xxLarge**: 40
###**xxxLarge**: 50
    
   
##Usage

    import QtQuick 2.0
    
    Rectangle {
        anchors.fill: parent
        anchors.margins: app.margins.large // instead of hardcoding 20
        color: app.colors.primary
    }
