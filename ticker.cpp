#include "ticker.h"
#include <deque>

Ticker::Ticker(QString symbol_) {
    symbol = symbol_;
    UpdatePrices();
    current_price = 0.0;
}

void Ticker::UpdatePrices() {\
    captured_intervals.clear();
    //TODO: Implement price fetching from API and store in the vector price_history
    //Store latest price in current_price
    current_price = 0.0;
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

double Ticker::GetCurrentPrice() {
    return current_price;
}

//If the map needs to be erased to be updated, remember to delete the vectors to avoid memory leaks.
