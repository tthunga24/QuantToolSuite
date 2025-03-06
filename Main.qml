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

        }

        Button {
            text: "Submit"
            onClicked: {
                finnhubClient.fetchQuote(inputField.text)
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
        target: finnhubClient
        function onQuoteReceived(result) {
            outputText.text = result
        }

    }
}
