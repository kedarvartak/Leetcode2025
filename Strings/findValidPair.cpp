class Solution {
public:
    string findValidPair(string s) {
        unordered_map<char, int> mp;
        for(char c : s)
        mp[c]++;

        for(int i = 0; i < s.length(); i++){
            if (s[i] != s[i + 1] &&
                mp[s[i]] == s[i] - '0' &&
                mp[s[i + 1]] == s[i + 1] - '0'){
                    return string(1, s[i]) + string(1, s[i + 1]);   
                }
        }
        return "";
    }
};