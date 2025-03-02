import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 400
    height: 300

    Column {
        anchors.centerIn: parent
        spacing: 10

        TextField {
            id: inputField
            placeholderText: "Enter"
            validator: IntValidator { bottom: -999; top: 1000 }
        }

        Button {
            text: "Submit"
            onClicked: testObj.processNumber(parseInt(inputField.text))
        }

        Text {
            id: outputText
            font.pixelSize: 16
            color: "blue"
        }
    }

    Connections {
        target: testObj
        function onNumberProcessed(result) {
            outputText.text = result
        }
    }
}
