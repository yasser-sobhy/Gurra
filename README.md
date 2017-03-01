
#Gurra is a QML ui framework, it has many easy-to-use components and unified structure

##Installation

Download app.tar.gz template, extract it and start coding :)

##Screenshots
[screenshots](/screenshots/README.md)

##Getting Started

##App Structure

    .
    |__ App
    |	|__ android
	|   |__ ios
    |	|__ assets
    |	|	|__fonts
    |	|	|__Gurra
    |	|	|__images
    |	|	|__languages
    |	|	|__sounds
    |	|__ qml
    |	|	|__	customs
    |	|	|	|__	api
    |	|	|		|__ moreApi.qml
    |	|	|	|__ Api.qml
    |	|	|	|__ Colors.qml
    |	|	|	|__ Fonts.qml
    |	|	|	|__ Headers.qml
    |	|	|	|__ Logic.qml
    |	|	|	|__ Models.qml
    |	|	|	|__ Pages.qml
    |	|	|	|__ Params.qml
    |	|	|	|__ Settings.qml
    |	|	|	|__ SoundEffects.qml
    |	|	|	|__ Urls.qml
	|	|   |__ pages
	|	|   |	|__ components
	|	|   |	|__ delegates
	|	|   |	|__ Home.qml
    |	|	|__ main.qml
	|   |__ src
	|   |__ app.pro
	|   |__ app.pro.user
	|   |__ main.cpp
	|   |__ qml.qrc
	|   |__ qtquickcontrols2.conf

##Example App

*main.qml*

    import QtQuick 2.7
    import QtQuick.Controls 2.0
    import QtQuick.Controls.Material 2.0
    import Org.Yasser.Gurra 1.0
    import Gurra 1.0
    
    import "qrc:/qml"
    import "qrc:/qml/pages"
    
    import "customs" as Custom
    
    App
    {
        id: app
        title: qsTr("Gurra")
        view: mainStack
    
        api: Custom.Api{}
        logic: Custom.Logic{}
        pages: Custom.Pages{}
        colors: Custom.Colors{}
        urls: Custom.Urls{}
        headers: Custom.Headers{}
        models: Custom.Models{}
        settings: Custom.Settings{}
        params: Custom.Params{}
        fonts: Custom.Fonts{}
        soundEffects: Custom.SoundEffects {}
    
        production: true
    
    
        // delay creating lazy items until all app Components are ready
        Timer {
            interval: 500
            running: true
            onTriggered: {
                app.ready(function(){
                    console.log("app ready")
                })
            }
        }
    
        StackView
        {
            id: mainStack
            anchors.fill: parent
    
            Component.onCompleted: {
                push(app.pages.home)
            }
        }
    }

*Home.qml*

    import QtQuick 2.7
    import QtQuick.Layouts 1.1
    import QtQuick.Controls 2.0
    import QtQuick.Controls.Material 2.0
    
    import Gurra 1.0
    
    AnaPage
    {
    
        Grid
        {
            id: grid
            anchors.centerIn: parent
            layoutDirection: Qt.RightToLeft
    
            columns: 3
            rowSpacing: app.spacing.xLarge
            columnSpacing: app.spacing.xLarge
    
            BigIcon {
                icon.icon: app.icons.fontAwesome.check
                label.text: qsTr("Auctions")
                onClicked: app.pushPage(app.pages.auctionTypeSelect)
            }
    
            BigIcon {
                icon.icon: app.icons.fontAwesome.th_list
                label.text: qsTr("Listings")
                onClicked: {
                    app.pages.listings.params.search_query = ""
                    app.pushPage(app.pages.listings)
                }
            }
    
            BigIcon {
                icon.icon: app.icons.fontAwesome.search
                label.text: qsTr("Search")
                onClicked: app.pushPage(app.pages.search)
            }
    
            BigIcon {
                icon.icon: app.icons.fontAwesome.user
                label.text: qsTr("My Account")
                onClicked: {
                    if(app.settings.member_id === 0)
                        app.pushPage(app.pages.loginPage)
                    else
                        app.pushPage(app.pages.userAccountPage)
                }
            }
    
            BigIcon {
                icon.icon: app.icons.fontAwesome.heart
                label.text: qsTr("Watchings")
                onClicked: {
                    if(app.settings.member_id === 0)
                        app.pushPage(app.pages.loginPage)
                    else
                        app.pushPage(app.pages.watchings)
                }
            }
    
            BigIcon {
                icon.icon: app.icons.fontAwesome.list
                label.text: qsTr("Rules")
                onClicked: {
                    app.pages.tosPage.params.tos = false
                    app.pushPage(app.pages.tosPage)
                }
            }
    
            BigIcon {
                icon.icon: app.icons.fontAwesome.ticket
                label.text: qsTr("Tos")
                onClicked: {
                    app.pages.tosPage.params.tos = true
                    app.pushPage(app.pages.tosPage)
                }
            }
    
            BigIcon {
                icon.icon: app.icons.fontAwesome.envelope
                label.text: qsTr("Contact Us")
                onClicked: app.pushPage(app.pages.contactUsPage)
            }
    
            BigIcon {
                icon.icon: app.icons.fontAwesome.info
                label.text: qsTr("About")
                onClicked: app.pushPage(app.pages.aboutPage)
            }
        }
    }



##Reference

##License 
Gurra is freely distributable under the terms of the MIT license.
