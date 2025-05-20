class Solution {
public:
    // Sliding Window Approach
    // Time Complexity: O(n) where n is length of array
    // Space Complexity: O(1) as we only use pointers
    int minSubArrayLen(int target, vector<int>& nums) {
        /*
        Simple Rules to Remember:
        1. Use two pointers: low and high
        2. Expand window by moving high pointer
        3. Shrink window by moving low pointer when sum >= target
        4. Keep track of minimum window size
        5. Return 0 if no valid window found

        Visual Example:
        nums = [2,3,1,2,4,3], target = 7

        Step 1: [2,3,1,2,4,3]  sum = 2
                l
                h

        Step 2: [2,3,1,2,4,3]  sum = 5
                l
                  h

        Step 3: [2,3,1,2,4,3]  sum = 6
                l
                    h

        Step 4: [2,3,1,2,4,3]  sum = 8  len = 4
                l
                      h

        Step 5: [2,3,1,2,4,3]  sum = 6  len = 4
                  l
                      h

        Step 6: [2,3,1,2,4,3]  sum = 7  len = 3
                    l
                      h

        Final answer: 3 (subarray [1,2,4])
        */

        // Initialize pointers and variables
        int low = 0;          // Start of window
        int high = 0;         // End of window
        int n = nums.size();  // Array length
        int len = INT_MAX;    // Minimum window size
        int sum = 0;          // Current window sum

        // Slide window until high reaches end
        while (high < n) {
            // Add current element to sum
            sum = sum + nums[high];

            // Shrink window while sum >= target
            while (sum >= target) {
                // Update minimum window size
                len = min(len, high - low + 1);
                
                // Remove leftmost element
                sum = sum - nums[low];
                
                // Move left pointer
                low++;
            }

            // Expand window
            high++;
        }

        // Return 0 if no valid window found
        return len == INT_MAX ? 0 : len;
    }
};

/*
Simple Memory Aid:

1. Window Management:
   a. Expand window (high++)
   b. Add element to sum
   c. Shrink window if sum >= target
   d. Update minimum length

2. Key Steps:
   a. Initialize pointers and variables
   b. Slide window until high reaches end
   c. Shrink window while sum >= target
   d. Update minimum length
   e. Return result

3. Visual Process:
   For nums = [2,3,1,2,4,3], target = 7:

   Window 1: [2,3,1,2]  sum = 8  len = 4
   Window 2: [3,1,2]    sum = 6  len = 4
   Window 3: [1,2,4]    sum = 7  len = 3
   Window 4: [2,4,3]    sum = 9  len = 3
   Window 5: [4,3]      sum = 7  len = 2
   Window 6: [3]        sum = 3  len = 2

   Final answer: 2 (subarray [4,3])

4. Common Pitfalls:
   - Not handling empty array
   - Not handling no valid window
   - Incorrect window size calculation
   - Not updating minimum length correctly

5. Time Complexity: O(n)
   - Each element visited at most twice
   - Once by high pointer
   - Once by low pointer
   - Linear time overall

6. Space Complexity: O(1)
   - Only uses a few variables
   - No extra space needed
   - Constant space regardless of input

7. Key Properties:
   - Window always contains sum >= target
   - Window size is minimized
   - All elements are positive
   - Window is contiguous
   - Window can be any size
*/