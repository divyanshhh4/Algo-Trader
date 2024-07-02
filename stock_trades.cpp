#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>

using namespace std;

struct StockData {
    double estimate;
    bool hasTraded;
};

void processIndividualTrade(const string& stockName, double price, char actionType, unordered_map<string, StockData>& stockMap) {
    if (stockMap.find(stockName) == stockMap.end()) {
        // First trade for this stock
        stockMap[stockName] = {price, true};
        cout << stockName << " " << price << " " << (actionType == 'b' ? "sell" : "buy") << endl;
    } else {
        // Subsequent trades
        StockData &data = stockMap[stockName];
        if (actionType == 'b' && price > data.estimate) {
            cout << stockName << " " << price << " sell" << endl;
            data.estimate = price; // Update estimate after the trade
        } else if (actionType == 's' && price < data.estimate) {
            cout << stockName << " " << price << " buy" << endl;
            data.estimate = price; // Update estimate after the trade
        } else {
            cout << "No trade" << endl;
        }
    }
}

int main() {
    unordered_map<string, StockData> stockMap;
    string line;
    
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        // Remove the trailing '#' character
        line.pop_back();
        
        stringstream ss(line);
        string stockName;
        double price;
        char actionType;
        
        if (ss >> stockName >> price >> actionType) {
            // Individual trade
            processIndividualTrade(stockName, price, actionType, stockMap);
        }
    }
    
    return 0;
}