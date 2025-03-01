class Solution {
public:
    vector<int> arrayChange(vector<int>& nums, vector<vector<int>>& operations) {
        unordered_map<int, int> pos;
        
        
        for (int i = 0; i < nums.size(); i++) {
            pos[nums[i]] = i;
        }
        
        for (auto& op : operations) {
            int oldValue = op[0], newValue = op[1];

           
            int index = pos[oldValue];
            nums[index] = newValue;

            
            pos.erase(oldValue);
            pos[newValue] = index;
        }

        return nums;
    }
};