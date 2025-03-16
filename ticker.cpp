#include "ticker.h"
#include <deque>
#include "alphavantage.h"
#include <QNetworkRequest>
#include "polygon.h"


Ticker::Ticker(QString symbol_) {
    symbol = symbol_;
    current_price = 0.0;
}

void Ticker::UpdatePrices() {
    captured_intervals.clear();
    Polygon* polygon_client = new Polygon("HWnObBJKkseYPeVXG11yPHxzoSP9sgJC");
    polygon_client -> fetchAggregatesData(symbol);

    connect(polygon_client, &Polygon::dataReceived, this, [this](const std::vector<std::pair<double, double>>& data) {
        if (data.size() == 0) {
            FallbackOnAlpha();
        } else {
            price_history.reserve(data.size());
            date_history.reserve(data.size());
            for(std::pair<double, double> curr : data) {
                price_history.push_back(curr.first);
                date_history.push_back(curr.second);
            }
        }
        qDebug() << price_history[0];
    });
    //Need to figure out how to delete polygon_client to avoid memory leaks
}

//we only call this with an unsuccessful polygon api call
void Ticker::FallbackOnAlpha() {
    AlphaVantage alpha_client("V0LIITCBJRMWNRO8");

}

const std::vector<double>& Ticker::GetPrices(int interval, int max_entries) {
    if (captured_intervals.find(interval) != captured_intervals.end()) {
        return captured_intervals.at(interval);
    }

    //using a deque for efficiency since we are inserting elements in the front. will convert to vector.
    std::deque<double> new_interval;
    int size = price_history.size();

    for (int i = size - 1; i >= 0; i -= interval) {
        new_interval.push_front(price_history[i]);
    }


    captured_intervals.insert({interval, std::vector<double>(new_interval.begin(), new_interval.end())});
    return captured_intervals.at(interval);
}

void Ticker::fetchPrices() {
    UpdatePrices();
}

double Ticker::GetCurrentPrice() {
    return current_price;
}

//If the map needs to be erased to be updated, remember to delete the vectors to avoid memory leaks.
