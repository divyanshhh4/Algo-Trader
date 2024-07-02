# Algo Trader

## Overview
Algo Trader is a C++ program designed for algorithmic trading applications. It features specialized functions aimed at optimizing trading decisions based on market depth data and forecasting market trends using Markov Chain analysis.

## Features
- **Optimal Trade Strategy:**
  - Implements a buy low, sell high approach to identify optimal trading opportunities.
  - Uses a simple strategy of storing the last traded price and executing trades if the current price is favorable: buying if the price is lower than the last traded price and selling if the price is higher.
- **Market Trend Forecasting:**
  - Uses a probability density matrix derived from historical closing prices (1000 days) to forecast market trends.
  - Applies Markov Chain analysis to predict the probability of future market trend.
  - Classifies market conditions based on price movements: a bull market if prices increase for 5 consecutive days, a bear market if prices decrease for 5 consecutive days, and sideways if there is no consistent movement.

- **Unified Program:** Integrated functionalities into a unified program structure using Makefile for seamless execution.

## Tech Stack
- **Language:** C++
- **Tools:** Makefile

## File Descriptions
- **'predictmarket.cpp':** Contains code for predicting market trends.
- **'stocktrades.cpp':** Contains code for identifying optimal trades.
- **'trades_input.txt':** Contains the input for stock trades in the form of market depth data.
- **'closing_price.txt':** Contains 1000 days of closing prices to create a probability density matrix.
- **'prediction_price.txt':** Contains the current 5 days of closing prices, which are used to predict the market trend for the next 5 days.
- **'Makefile':** Unifies and runs the desired functions, building the program and managing dependencies.


