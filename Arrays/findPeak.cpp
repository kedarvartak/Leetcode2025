class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;

        while(low < high){
            int mid = low + (high - low)/2;

            if(nums[mid] > nums[mid+1]){
                high = mid; //peak in left half
            }
            else{
                low = mid+1; //peak in right half
            }
        }

        return low;
    }
};