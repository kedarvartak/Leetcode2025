class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char, int> mp;
        int i = 0, maxFreq = 0, result = 0; 
        
        for (int j = 0; j < s.size(); j++) {
            mp[s[j]]++;
            maxFreq = max(maxFreq, mp[s[j]]);

            while ((j - i + 1) - maxFreq > k) {
                mp[s[i]]--;
                i++;
            }

            result = max(result, j - i + 1);
        }
        return result;
    }
};
