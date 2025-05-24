class Solution {
public:
    // Optimal Solution: Reverse Approach
    // Time Complexity: O(n), Space Complexity: O(1)
    // Rotates the array to the right by k steps in-place.
    void rotate(vector<int>& nums, int k) {
        /*
        Problem: Rotate an array to the right by k steps.
        Example: nums = [1,2,3,4,5,6,7], k = 3
        Output:  [5,6,7,1,2,3,4]

        Simple Rules to Remember:
        1. Rotating by k > n is the same as k % n
        2. The last k elements move to the front
        3. The first n-k elements move to the back
        4. In-place, O(1) extra space

        Visual Example:
        nums = [1,2,3,4,5,6,7], k = 3
        Step 1: Reverse the whole array
            [7,6,5,4,3,2,1]
        Step 2: Reverse first k elements (first 3)
            [5,6,7,4,3,2,1]
        Step 3: Reverse last n-k elements (from index 3 to 6)
            [5,6,7,1,2,3,4]
        Done!

        Why does this work?
        - Reversing the whole array puts the elements in the right order, but reversed.
        - Reversing the first k elements puts them in the correct order at the front.
        - Reversing the rest puts them in the correct order at the back.

        Key Steps:
        1. Normalize k (k = k % n)
        2. Reverse the whole array
        3. Reverse first k elements
        4. Reverse last n-k elements

        Common Pitfalls:
        - Not normalizing k
        - Off-by-one errors in reverse indices
        - Not handling empty or single-element arrays
        - Using extra space unnecessarily

        Time Complexity: O(n) (each element reversed at most twice)
        Space Complexity: O(1) (in-place)
        */
        int n = nums.size();
        if (n == 0 || n == 1) return;
        k = k % n;
        if (k == 0) return;
        // Helper lambda to reverse a subarray in-place
        auto reverse = [](vector<int>& arr, int l, int r) {
            while (l < r) {
                swap(arr[l], arr[r]);
                l++; r--;
            }
        };
        // Step 1: Reverse the whole array
        reverse(nums, 0, n - 1);
        // Step 2: Reverse first k elements
        reverse(nums, 0, k - 1);
        // Step 3: Reverse last n-k elements
        reverse(nums, k, n - 1);
    }
};

/*
Alternative (Naive) Approach:
- Rotate one step at a time, k times (O(n*k) time, O(1) space)
- For each rotation, move last element to front, shift others right
- Inefficient for large k or n

Key Properties:
- In-place, no extra array needed
- Handles all edge cases (empty, single element, k > n)
- Efficient for large arrays
- Reversal trick is a classic for array rotation

Why is the reversal approach optimal?
- Each element is moved at most twice
- No extra space
- Simple, elegant, and fast
*/