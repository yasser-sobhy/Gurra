
#Spacing object groups together frequently used space sizes to increase readability and avoid mistyping.


##Available Space Sizes

    none: 0
    
    xxSmall: 1
    xSmall: 3
    
    normal: 10
    small: 5
    medium: 15
    large: 20
    
    xLarge: 30
    xxLarge: 40
    xxxLarge: 50
 
##Usage

    Column
    {
        spacing: app.spacing.small

        Label
        {
        text: "Hello Gurra!"
        }

        Row
        {
        height: app.sizes.xxLarge
                spacing: app.spacing.large

                IconLabel
                {
                    spacing: app.spacing.xSmall

                    icon.icon: app.icons.fontAwesome.map_marker
                    icon.color: app.colors.background
                    icon.font.pointSize: app.sizes.h4

                    label.text: "IconLabel"
                    label.font.pointSize: app.sizes.h4
                    label.color: app.colors.primary
                }

                IconLabel
                {
                    spacing: app.spacing.xSmall

                    icon.icon: app.icons.fontAwesome.clock_o
                    icon.color: app.colors.background
                    icon.font.pointSize: app.sizes.h4

                    label.text: "IconLabel"
                    label.font.pointSize: app.sizes.h5
                    label.color: app.colors.primary
                }
            }
        }
        