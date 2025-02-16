class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int total = 0;
        int leftMax = 0;
        int rightMax = 0;

        int left = 0;
        int right = n - 1;

        while(left < right){

            if(height[left] <= height[right]){

                if(leftMax > height[left]){
                    total += leftMax - height[left];
                }

                else leftMax = height[left];

                left = left + 1;

            }

            else{
                if(rightMax > height[right]) {
                    
                    
                    total += rightMax - height[right];
                }
                else rightMax = height[right];

                right = right - 1;
            }
        }
        return total;
    }
};