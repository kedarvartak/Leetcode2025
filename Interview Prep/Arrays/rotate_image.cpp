class Solution {
public:
    // Function to rotate an array to the right by k steps.
    // nums: The input array (passed by reference, so modifications are done in-place).
    // k: The number of steps to rotate the array.
    void rotate(vector<int>& nums, int k) {
        // Get the number of elements in the array.
        int n = nums.size();

        // If the array is empty or has only one element, no rotation is needed.
        if (n == 0 || n == 1) {
            return;
        }

        // Normalize k: If k is greater than n, rotating k times
        // is the same as rotating k % n times.
        // For example, rotating an array of size 5 by 7 steps
        // is equivalent to rotating it by 2 steps (7 % 5 = 2).
        k = k % n;  
        
        // This outer loop performs the rotation k times.
        // In each iteration of this loop, the array is rotated by one step to the right.
        for(int i = 0; i < k; i++) {
           
            // Store the last element of the array in a temporary variable.
            // This element will become the first element after one right rotation.
            int temp = nums[n - 1];
           
            // Shift all elements one position to the right.
            // This loop starts from the second to last element (index n-1)
            // and moves towards the beginning of the array (index 1).
            for(int j = n - 1; j > 0; j--) {
                // The element at index j gets the value of the element to its left (index j-1).
                nums[j] = nums[j - 1];
            }
            
            // Place the stored last element (from 'temp') at the beginning of the array (index 0).
            nums[0] = temp;
        }
        // After k iterations, the array 'nums' will be rotated to the right by k steps.
    }
};