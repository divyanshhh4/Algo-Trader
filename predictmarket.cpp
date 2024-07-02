#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to determine market regime for a sequence of 5 days
char determineMarketRegime(const vector<double>& prices) {
    int n = prices.size();
    if (n < 5) {
        return 'S'; // Not enough data to determine
    }
    
    // Check bull market (prices increasing for 5 consecutive days)
    bool isBull = true;
    for (int i = 1; i < 5; ++i) {
        if (prices[n - i] <= prices[n - i - 1]) {
            isBull = false;
            break;
        }
    }
    if (isBull) return 'B';
    
    // Check bear market (prices decreasing for 5 consecutive days)
    bool isBear = true;
    for (int i = 1; i < 5; ++i) {
        if (prices[n - i] >= prices[n - i - 1]) {
            isBear = false;
            break;
        }
    }
    if (isBear) return 'R';
    
    // Otherwise, it's a sideways market
    return 'S';
}

// Function to build probability density matrix
unordered_map<char, unordered_map<char, double>> buildProbabilityMatrix(const vector<char>& regimes) {
    unordered_map<char, unordered_map<char, double>> transitionMatrix;
    int n = regimes.size();
    
    for (int i = 1; i < n; ++i) {
        transitionMatrix[regimes[i - 1]][regimes[i]]++;
    }
    
    // Convert counts to probabilities
    for (auto& pair1 : transitionMatrix) {
        double total = 0;
        for (auto& pair2 : pair1.second) {
            total += pair2.second;
        }
        for (auto& pair2 : pair1.second) {
            pair2.second /= total;
        }
    }
    
    return transitionMatrix;
}

int main() {
    ifstream infile("closing_prices.txt");
    vector<double> prices;
    
    double price;
    while (infile >> price) {
        prices.push_back(price);
    }
    
    // Determine market regimes
    vector<char> marketRegimes;
    for (int i = 4; i < prices.size(); ++i) {
        char regime = determineMarketRegime({prices[i-4], prices[i-3], prices[i-2], prices[i-1], prices[i]});
        marketRegimes.push_back(regime);
    }
    
    // Build probability density matrix
    unordered_map<char, unordered_map<char, double>> probabilityMatrix = buildProbabilityMatrix(marketRegimes);
    
    // Read 5 closing prices for prediction from file
    ifstream predictfile("prediction_prices.txt");
    vector<double> predictPrices;
    
    while (predictfile >> price) {
        predictPrices.push_back(price);
    }
    
    if (predictPrices.size() != 5) {
        cerr << "Error: Need exactly 5 closing prices for prediction." << endl;
        return 1;
    }
    
    // Determine the initial state
    char initialState = determineMarketRegime({predictPrices[0], predictPrices[1], predictPrices[2], predictPrices[3], predictPrices[4]});
    
    // Predict the probabilities for the next 5 days
    unordered_map<char, double> initialProb = probabilityMatrix[initialState];
    
    cout << "Probability of market regimes for the next 5 days:" << endl;
    cout << "Bull Market: " << initialProb['B'] << endl;
    cout << "Bear Market: " << initialProb['R'] << endl;
    cout << "Sideways Market: " << initialProb['S'] << endl;
    
    return 0;
}
