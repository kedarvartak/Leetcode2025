class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> sett(nums.begin() , nums.end());
        int maxi = 0;

        for(int num : sett){
            if(sett.find(num - 1) == sett.end()){
                int length = 1;

                while(sett.find(num + length) != sett.end()){
                    length++;
                }

                maxi = max(maxi, length);
            }
        }

        return maxi;
    }
};