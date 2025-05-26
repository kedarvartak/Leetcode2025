// 3 cases 
// case 1 - number can be 0 - swap low and mid since we want all 0s in the start
// case 2 - number can be 1 - mid ++
// case 3 - number can be 2 - swap mid and high

class Solution {
public:
    void sortColors(vector<int>& nums) {
       int low = 0;
       int mid = 0;
       int high = nums.size() - 1;

       while(mid <= high){
        if(nums[mid] == 0){
        swap(nums[mid], nums[low]);
        mid++;
        low++;
        }
        else if(nums[mid] == 1)
        mid++;

        else{
            swap(nums[mid], nums[high]);
            high--;
        }
        
       }
    }
};
