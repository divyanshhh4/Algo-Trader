CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: stock_trades predictmarket

trade: stock_trades
	./stock_trades < trades_input.txt

predict: predictmarket
	./predictmarket < prediction_prices.txt

stock_trades: stock_trades.o
	$(CXX) $(CXXFLAGS) -o stock_trades stock_trades.o

predictmarket: predictmarket.o
	$(CXX) $(CXXFLAGS) -o predictmarket predictmarket.o

stock_trades.o: stock_trades.cpp
	$(CXX) $(CXXFLAGS) -c stock_trades.cpp

predictmarket.o: predictmarket.cpp
	$(CXX) $(CXXFLAGS) -c predictmarket.cpp

clean:
	rm -f *.o stock_trades predictmarket

.PHONY: all clean trade predict
