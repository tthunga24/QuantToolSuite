#ifndef FINNHUB_H
#define FINNHUB_H

#endif // FINNHUB_H

#include <iostream>
#include <string>
#include <curl/curl.h>

// Callback function for writing received data into a string
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to fetch real-time quote data from Finnhub
std::string fetch_stock_quote(const std::string& ticker, const std::string& api_key) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    // Finnhub API URL for stock quote
    std::string url = "https://finnhub.io/api/v1/quote"
                      "?symbol=" + ticker +
                      "&token=" + api_key;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Set User-Agent to mimic a browser
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64)");

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return readBuffer;
}




int main() {
    std::string ticker = "AAPL";  // Hardcoded ticker for now
    std::string api_key = "cv1336pr01qhkk80eiugcv1336pr01qhkk80eiv0";     // 🔴 INSERT YOUR FINNHUB API KEY HERE

    if (api_key.empty()) {
        std::cerr << "Error: Please provide a valid Finnhub API key.\n";
        return 1;
    }

    std::cout << "Fetching stock quote data for: " << ticker << std::endl;
    std::string stock_data = fetch_stock_quote(ticker, api_key);

    if (!stock_data.empty()) {
        std::cout << "Raw API Response:\n" << stock_data << std::endl;
    } else {
        std::cout << "Failed to fetch stock data.\n";
    }

    return 0;
}
