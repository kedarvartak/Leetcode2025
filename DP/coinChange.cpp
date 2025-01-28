class Solution {
public:
    int helperMemo(vector<int>& coins, int amount, vector<int>& dp){
        //base case
        if(amount == 0) return 0;
        if(amount < 0) return INT_MAX;
        int minCoins = INT_MAX;

        if(dp[amount] != -1) return dp[amount];

        for(int i = 0; i < coins.size(); i++){
            int res = helperMemo(coins, amount - coins[i], dp);
            if(res != INT_MAX){
                minCoins = min(minCoins, 1 + res);
            }
        }

        dp[amount] = minCoins;
        return dp[amount];
    }

    int helperTab(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (int j = 0; j < coins.size(); j++) {
                if (i - coins[j] >= 0 && dp[i - coins[j]] != INT_MAX) {
                    dp[i] = min(dp[i], 1 + dp[i - coins[j]]);
                }
            }
        }
        return dp[amount];
    }

    int coinChange(vector<int>& coins, int amount) {
        int ans = helperTab(coins, amount);
        return (ans == INT_MAX) ? -1 : ans;
    }
};
