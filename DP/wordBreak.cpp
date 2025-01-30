class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n + 1, false);

        dp[0] = true;
        for (int i = 1; i <= s.size(); i++) {
            for (auto word : wordDict) {
                int len = word.length();
                if (i >= len && dp[i - len] && s.substr(i - len, len) == word) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
};