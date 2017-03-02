#Fonts object groups together all fonts used by the app

> Gurra come with no default loaded fonts

**Loading custom font**

    import QtQuick 2.0
    import Gurra 1.0
    
    Fonts
    {
        property string digital: _digital.name
    
        FontLoader
        {
            id: _digital
            source: "qrc:/assets/fonts/DS-DIGI.TTF"
        }
    }