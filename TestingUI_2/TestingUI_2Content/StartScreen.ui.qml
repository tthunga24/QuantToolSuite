/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick
import QtQuick.Controls
// import TestingUI_2

Rectangle {
    id: startView
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor
    state: "DashboardState"

    Loader {
        id: dashboardLoader
        visible: false
        anchors.fill: parent
        source: "Dashboard.ui.qml"
        active: false
    }
    Loader {
        id: autoHedgeLoader
        visible: false
        anchors.fill: parent
        source: "AutoHedge.ui.qml"
        active: false
    }
    Loader {
        id: settingsLoader
        visible: false
        anchors.fill: parent
        source: "Settings.ui.qml"
        active: false
    }
    states: [
        State {
            name: "DashboardState"

            PropertyChanges {
                target: dashboardLoader
                visible: true
                active: true
            }
        },
        State {
            name: "SettingsState"

            PropertyChanges {
                target: settingsLoader
                visible: true
                active: true
            }
        },

        State {
            name: "AutoHedgeState"

            PropertyChanges {
                target: autoHedgeLoader
                visible: true
                active: true
            }
        }    ]
}
