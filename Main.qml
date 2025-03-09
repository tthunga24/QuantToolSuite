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
                alphavantage.fetchTimeSeriesData(inputField.text)
            }
        }

        Button {
            text: "YFinance"
            onClicked: {
                yfinanceClient.fetchQuote(inputField.text)
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
        target: alphavantage
        function onDataReceived(result) {
            outputText.text = result
        }

    }

    // Connections for YFinance Client
    Connections {
        target: yfinanceClient
        function onQuoteReceived(result) {
            outputText2.text = "YFinance Price: " + result
        }
    }

}
