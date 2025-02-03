class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int nextBuy = 0, nextSell = 0;
        for (int i = prices.size() - 1; i >= 0; --i) {
            int currentBuy = max(-prices[i] + nextSell, nextBuy);
            int currentSell = max(prices[i] + nextBuy, nextSell);
            nextBuy = currentBuy;
            nextSell = currentSell;
        }
        return nextBuy;
    }
};