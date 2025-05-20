class Solution {
public:
    // Greedy Approach
    // Time Complexity: O(n) where n is the length of prices array
    // Space Complexity: O(1) as we only use one variable
    int maxProfit(vector<int>& prices) {
        /*
        Simple Rules to Remember:
        1. Can buy and sell multiple times
        2. Must sell before buying again
        3. Buy low, sell high
        4. Take profit whenever price increases
        5. No need to track buy/sell days
        6. Sum up all possible profits

        Visual Example:
        prices = [7, 1, 5, 3, 6, 4]

        Step 1: Day 0 to 1
               Price change: 7 -> 1
               No profit (price decreased)
               Total profit = 0

        Step 2: Day 1 to 2
               Price change: 1 -> 5
               Profit = 5 - 1 = 4
               Total profit = 0 + 4 = 4

        Step 3: Day 2 to 3
               Price change: 5 -> 3
               No profit (price decreased)
               Total profit = 4

        Step 4: Day 3 to 4
               Price change: 3 -> 6
               Profit = 6 - 3 = 3
               Total profit = 4 + 3 = 7

        Step 5: Day 4 to 5
               Price change: 6 -> 4
               No profit (price decreased)
               Total profit = 7

        Final result: 7 (Buy at 1, sell at 5; Buy at 3, sell at 6)
        */

        // Handle edge case
        if (prices.empty()) return 0;

        int totalProfit = 0;

        // Iterate through prices starting from second day
        for (int i = 1; i < prices.size(); i++) {
            // If current price is higher than previous price, add the difference to profit
            if (prices[i] > prices[i - 1]) {
                totalProfit += prices[i] - prices[i - 1];
            }
        }

        return totalProfit;
    }
};

/*
Simple Memory Aid:

1. Key Variables:
   - totalProfit: Sum of all profits
   - prices[i]: Current day's price
   - prices[i-1]: Previous day's price

2. Key Steps:
   a. Initialize totalProfit as 0
   b. For each price (starting from second day):
      - If price increased: Add difference to profit
      - If price decreased: Do nothing
   c. Return totalProfit

3. Visual Process:
   For prices = [7, 1, 5, 3, 6, 4]:

   Day 0-1: 7->1  -> No profit
   Day 1-2: 1->5  -> Profit = 4
   Day 2-3: 5->3  -> No profit
   Day 3-4: 3->6  -> Profit = 3
   Day 4-5: 6->4  -> No profit
   Total Profit = 7

4. Common Pitfalls:
   - Not handling empty array
   - Not considering all price changes
   - Not adding profits correctly
   - Trying to track buy/sell days
   - Not understanding greedy approach
   - Overcomplicating the solution

5. Time Complexity: O(n)
   - n: length of prices array
   - Single pass through array
   - Constant time operations
   - No nested loops

6. Space Complexity: O(1)
   - Only one variable used
   - No extra data structures
   - Constant space regardless of input size

7. Key Properties:
   - Multiple transactions allowed
   - Must sell before buying again
   - Take profit on every price increase
   - No need to track transactions
   - Greedy approach works
   - Sum of all possible profits

8. Alternative Approaches:
   - Dynamic programming
   - Peak valley approach
   - Two pointers
   - Brute force (O(n²))
   - Using stack

9. Why Greedy Works:
   - Any profit can be broken down into daily profits
   - No need to hold for longer periods
   - Taking profit immediately is optimal
   - No future information needed
   - Local optimal = Global optimal
*/
