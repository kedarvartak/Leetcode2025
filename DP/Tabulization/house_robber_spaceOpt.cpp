class Solution {
public:
    int rob(vector<int>& nums) {
        int prev = 0;
        int maxi = 0;

        for(int i = 0; i < nums.size(); i++){
            int temp = max(maxi, prev + nums[i]);
            prev = maxi;
            maxi = temp;
        }

        return maxi;
    }
};