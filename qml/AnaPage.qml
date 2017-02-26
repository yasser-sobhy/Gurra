import QtQuick 2.0
import QtQuick.Controls 2.0

import Org.Yasser.Gurra 1.0

Page
{
    id: page

    property bool edit: false // a convenient property, should be true when editing a resourse

    property bool noInternet
    property bool noContent
    property bool noNetwork
    property bool loading

    property bool noInternet_button: true
    property bool noContent_button: true
    property bool noNetwork_button: true

    property string noInternet_message: qsTr("No Connection")
    property string noContent_message: qsTr("Sorry, no results that matchs your cretiera")
    property string noNetwork_message: qsTr("Network connection error")
    property string loading_message

    property string noInternet_icon: app.icons.fontAwesome.exclamation
    property string noContent_icon: app.icons.fontAwesome.exclamation
    property string noNetwork_icon: app.icons.fontAwesome.exclamation

    signal retry // search again
    signal retryConnection
    signal retryNetwork

    signal active
    signal activating
    signal inactive

    // these functions will be invoked when page is pushed or poped
    signal beforeEnter
    signal enter
    signal beforeLeave
    signal leave

    LayoutMirroring.enabled: app.layoutMirroring
    LayoutMirroring.childrenInherit: app.childrenInherit

    onLoadingChanged: {
        // reset
        if(loading){
            noContent = false
            noNetwork = false
            noInternet = false
        }
    }

    StackView.onStatusChanged: {

        if(StackView.status === StackView.Activating)
            activating()
        else if(StackView.status === StackView.Active)
            active()
        else if(StackView.status === StackView.Inactive)
            inactive()
    }

    Margins2 {
        id: _loading
        anchors.margins: app.margins.large
        visible: loading

        Column {
            id: column
            anchors.centerIn: parent
            spacing: app.spacing.large

            BusyIndicator
            {
                id: indicator
                anchors.horizontalCenter: parent.horizontalCenter
                running: loading
            }

            Label {
                id: msg
                anchors.horizontalCenter: parent.horizontalCenter
                text: loading_message
            }
        }

    }

    Margins2 {
        id: _noNetwork
        anchors.margins: app.margins.large
        visible: noNetwork

        Column {

            anchors.centerIn: parent
            width: parent.width
            spacing: app.spacing.large

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: app.spacing.normal

                Icon {
                    anchors.verticalCenter: parent.verticalCenter
                    icon: noNetwork_icon
                    font.pointSize: app.sizes.h4
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    text: noNetwork_message
                    font.pointSize: app.sizes.h4
                }
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Retry"
                visible: noNetwork_button
                onClicked: retryNetwork()
            }
        }
    }

    Margins2 {
        id: _noContent
        anchors.margins: app.margins.large
        visible: noContent

        Column {

            anchors.centerIn: parent
            width: parent.width
            spacing: app.spacing.large

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: app.spacing.normal

                Icon {
                    anchors.verticalCenter: parent.verticalCenter
                    icon: noContent_icon
                    font.pointSize: app.sizes.h4
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    text: noContent_message
                    font.pointSize: app.sizes.h4
                    wrapMode: Text.Wrap
                }
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Try Again"
                visible: noContent_button
                onClicked: retry()
            }
        }
    }

    Margins2 {
        id: _noInternet
        anchors.margins: app.margins.large
        visible: noInternet

        Column {

            anchors.centerIn: parent
            width: parent.width
            spacing: app.spacing.large

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: app.spacing.normal

                Icon {
                    anchors.verticalCenter: parent.verticalCenter
                    icon: noInternet_icon
                    font.pointSize: app.sizes.h4
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    text: noInternet_message
                    font.pointSize: app.sizes.h4
                }
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Retry"
                visible: noInternet_button
                onClicked: retryConnection()
            }
        }
    }

}
