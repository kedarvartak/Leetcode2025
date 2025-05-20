class Solution {
public:
    // One Pass Approach
    // Time Complexity: O(n) where n is the length of prices array
    // Space Complexity: O(1) as we only use two variables
    int maxProfit(vector<int>& prices) {
        /*
        Simple Rules to Remember:
        1. Buy low, sell high
        2. Can only buy once and sell once
        3. Must buy before selling
        4. Track minimum price seen so far
        5. Calculate profit for each day
        6. Keep track of maximum profit

        Visual Example:
        prices = [7, 1, 5, 3, 6, 4]

        Step 1: Day 0 (Price: 7)
               buy_price = 7
               maxi = 0
               No profit possible yet

        Step 2: Day 1 (Price: 1)
               buy_price = 1 (update as it's lower)
               maxi = 0
               No profit possible yet

        Step 3: Day 2 (Price: 5)
               buy_price = 1
               curr_profit = 5 - 1 = 4
               maxi = max(0, 4) = 4

        Step 4: Day 3 (Price: 3)
               buy_price = 1
               curr_profit = 3 - 1 = 2
               maxi = max(4, 2) = 4

        Step 5: Day 4 (Price: 6)
               buy_price = 1
               curr_profit = 6 - 1 = 5
               maxi = max(4, 5) = 5

        Step 6: Day 5 (Price: 4)
               buy_price = 1
               curr_profit = 4 - 1 = 3
               maxi = max(5, 3) = 5

        Final result: 5 (Buy at 1, sell at 6)
        */

        // Handle edge case
        if (prices.empty()) return 0;

        // Initialize variables
        int buy_price = prices[0];  // Track minimum price seen so far
        int maxi = 0;               // Track maximum profit

        // Iterate through prices starting from second day
        for (int i = 1; i < prices.size(); i++) {
            // If current price is lower than buy_price, update buy_price
            if (prices[i] < buy_price) {
                buy_price = prices[i];
            }
            // Otherwise, calculate potential profit and update maxi
            else {
                int curr_profit = prices[i] - buy_price;
                maxi = max(maxi, curr_profit);
            }
        }

        return maxi;
    }
};

/*
Simple Memory Aid:

1. Key Variables:
   - buy_price: Minimum price seen so far
   - maxi: Maximum profit possible
   - curr_profit: Profit if selling today

2. Key Steps:
   a. Initialize buy_price with first price
   b. Initialize maxi as 0
   c. For each price:
      - If price < buy_price: Update buy_price
      - Else: Calculate profit and update maxi
   d. Return maxi

3. Visual Process:
   For prices = [7, 1, 5, 3, 6, 4]:

   Day 0: 7  -> buy_price = 7,  maxi = 0
   Day 1: 1  -> buy_price = 1,  maxi = 0
   Day 2: 5  -> buy_price = 1,  maxi = 4
   Day 3: 3  -> buy_price = 1,  maxi = 4
   Day 4: 6  -> buy_price = 1,  maxi = 5
   Day 5: 4  -> buy_price = 1,  maxi = 5

4. Common Pitfalls:
   - Not handling empty array
   - Not initializing buy_price
   - Not considering all possible buy-sell pairs
   - Not updating buy_price when lower price found
   - Not calculating profit correctly
   - Not maintaining maximum profit

5. Time Complexity: O(n)
   - n: length of prices array
   - Single pass through array
   - Constant time operations
   - No nested loops

6. Space Complexity: O(1)
   - Only two variables used
   - No extra data structures
   - Constant space regardless of input size

7. Key Properties:
   - One buy and one sell
   - Buy must come before sell
   - Track minimum price seen
   - Calculate profit for each day
   - Keep maximum profit
   - No need to track buy/sell days

8. Alternative Approaches:
   - Two pointers approach
   - Dynamic programming
   - Divide and conquer
   - Brute force (O(n²))
   - Using stack
*/