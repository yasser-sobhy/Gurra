
#Sizes object groups together frequently used sizes to increase readability and avoid mistyping.


##Available Sizes

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
        

   
##Usage

    BigIcon {
        
        color: app.colors.accent
        icon.color: app.colors.primary
    
        icon.width: pp.sizes.xxxLarge
        icon.font.pointSize: app.sizes.h1
        label.font.pointSize: app.sizes.h4
    }