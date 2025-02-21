class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
         vector<string> ans;
         map<string, int> mp;

       
        for (const string& word : words) {
            mp[word]++;
        }

        vector<pair<int, string>> v;

        
        for (const auto& it : mp) {
            v.push_back({it.second, it.first});
        }

       
        sort(v.begin(), v.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
            if (a.first == b.first) return a.second < b.second;  
            return a.first > b.first; 
        });


        for (int i = 0; i < k; i++) {
            ans.push_back(v[i].second);
        }

        return ans;
    }
};