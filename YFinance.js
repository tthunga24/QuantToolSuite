// // fetchYahoo.js - Simple Test Function
// function fetchYahooFinanceData(symbol, callback) {
//     callback(symbol + " JS Script Worked");
// }

function fetchWebsiteContent(callback) {
    fetch('https://example.com', {
        headers: {
            "User-Agent": "Mozilla/5.0"
        }
    })
    .then(response => response.text()) // Convert response to text
    .then(htmlText => {
        callback(htmlText.slice(0, 100)); // Return first 100 characters
    })
    .catch(error => {
        console.error("Error fetching webpage:", error);
        callback(null); // Call callback with null if there was an error
    });
}

