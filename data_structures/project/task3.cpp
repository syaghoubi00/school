#include <iostream>
#include <vector>

struct buySellDayProfit {
  int maxProfit;
  int buyDay;
  int sellDay;
};

buySellDayProfit getMaxProfit(const std::vector<int> &prices) {
  // Ensure there are at least two prices to calculate profit
  if (prices.size() < 2) {
    throw std::invalid_argument(
        "At least two prices are required to calculate profit.");
  }

  // Initialize the minimum price to the first price and max profit to 0
  int minPrice = prices[0];
  int minPriceDay = 0;
  int maxProfit = 0;

  // Initialize the buy and sell days
  int buyDay = 0;
  int sellDay = 0;

  // Iterate through the prices starting from the second day since the first day
  // is the minimum price
  for (size_t i = 1; i < prices.size(); i++) {
    int potentialProfit = prices[i] - minPrice;

    if (potentialProfit > maxProfit) {
      maxProfit = potentialProfit; // Update maxProfit if the current potential
                                   // profit is greater
      buyDay = minPriceDay;        // Update the buy day to the day of minPrice
      sellDay = i;                 // Update the sell day to the current day
    }

    if (prices[i] < minPrice) {
      // Update minPrice if the current price is lower
      minPrice = prices[i];
      minPriceDay = i; // Update the buy day to the current day
    }
  }

  return {maxProfit, buyDay, sellDay};
}

int main() {
  std::vector<int> prices = {10, 7, 5, 8, 11, 2, 6};
  // std::vector<int> prices = {10};

  try {
    buySellDayProfit result = getMaxProfit(prices);
    std::cout << "Maximum profit: " << result.maxProfit << std::endl;
    // Add 1 to buyDay and sellDay to convert from 0-based to 1-based index for
    // more logical 'first day' instead of '0th day'
    std::cout << "Buy on day: " << result.buyDay + 1 << std::endl;
    std::cout << "Sell on day: " << result.sellDay + 1 << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
