

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
    id: root
    width: Constants.width
    height: Constants.height

    Text {
        id: headerText
        y: 60
        text: qsTr("Settings Page Edited Test")
        anchors.left: parent.left
        anchors.leftMargin: 520
        font.pixelSize: 30
    }

    Frame {
        id: frame
        x: 0
        y: 0
        width: 236
        height: 1080
        Button {
            id: nav1
            x: -12
            y: -12
            width: 236
            height: 96
            text: qsTr("Dashboard Page")
            icon.source: "../Dependencies/Components/examples/TransitionItem/images/svg/area-chart.svg"
            highlighted: true
            flat: true
            Connections {
                target: nav1
                function onClicked() {
                        startView.state = "DashboardState"
                    }
            }
        }

        Button {
            id: nav2
            x: -12
            y: 83
            width: 236
            height: 96
            text: qsTr("AutoHedgeTool")
            icon.color: "#3c3f41"
            highlighted: true
            flat: true
            Connections {
                target: nav2
                function onClicked() {
                        startView.state = "AutoHedgeState"
                    }
            }
        }

        Button {
            id: nav3
            x: -12
            y: 178
            width: 236
            height: 96
            text: qsTr("Settings")
            icon.source: "../Dependencies/Components/examples/TransitionItem/images/svg/arrows.svg"
            icon.color: "#5b5c5e"
            highlighted: true
            flat: true
            Connections {
                target: nav3
                function onClicked() {
                        startView.state = "SettingsState"
                    }
            }
        }

        Rectangle {
            id: rectangle
            x: -12
            y: 271
            width: 236
            height: 797
            color: "#5b5a5a"
        }
    }
}
