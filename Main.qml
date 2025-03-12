import QtQuick
import QtQuick.Controls

import "YFinance.js" as YFinance

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

        TextField {
            id: dateStart
            placeholderText: "Start Date: YYYY-MM-DD"

        }

        TextField {
            id: dateEnd
            placeholderText: "End Date: YYYY-MM-DD"

        }

        Button {
            text: "Alpha Vantage"
            onClicked: {
                alphavantage.fetchTimeSeriesData(inputField.text)
            }
        }

        Button {
            text: "Polygon"
            onClicked: {
                polygonClient.fetchAggregatesData(inputField.text, dateStart.text, dateEnd.text)
            }
        }

        // Button {
        //     text: "JS Test"
        //     onClicked: {
        //         console.log("Button Clicked: Testing JavaScript file...");
        //         YFinance.fetchYahooFinanceData(inputField.text, function(result) {
        //             console.log("Test Output:", result);
        //             outputText2.text = result;  // Display result in QML UI
        //         });
        //     }
        // }


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
        target: polygonClient
        function onDataReceived(result) {
            outputText2.text = result
        }
    }

}
