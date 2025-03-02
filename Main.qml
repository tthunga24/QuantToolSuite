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
            validator: IntValidator { bottom: -1000; top: 1000 }
        }

        Button {
            text: "Submit"
            onClicked: {
                testObj.processNumber(parseInt(inputField.text));
                testObj.processNumber2(parseInt(inputField.text))
            }
        }

        Text {
            id: outputText
            font.pixelSize: 16
            color: "blue"
        }
        Text {
            id: outputText2
            font.pixelSize: 16
            color: "blue"
        }
    }

    Connections {
        target: testObj
        function onNumberProcessed(result) {
            outputText.text = result
        }
        function onNumberProcessed2(result) {
            outputText2.text = result
        }
    }
}
