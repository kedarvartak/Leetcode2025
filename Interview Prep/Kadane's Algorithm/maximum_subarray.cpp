#include <vector>
#include <algorithm> // For std::max
#include <iostream>  // For main example
#include <limits>    // For std::numeric_limits (optional, for alternative initialization)

/*
Problem: Maximum Subarray (LeetCode 53)
Given an integer array `nums`, find the contiguous subarray (containing at least one number)
which has the largest sum and return its sum.

Example:
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Concept of Kadane's Algorithm:
Kadane's Algorithm is a dynamic programming approach to solve this problem efficiently.
It iterates through the array, keeping track of two main variables:
1. `current_max_ending_here` (represented as `sum` in the provided code):
   This is the maximum sum of a subarray that ends at the current position `i`.
   At each step `i`, we decide whether to extend the previous subarray (by adding `nums[i]`
   to `current_max_ending_here` of the previous step) OR to start a new subarray beginning
   with `nums[i]`. We choose whichever is larger.
   More simply, `current_max_ending_here = std::max(nums[i], current_max_ending_here + nums[i])`.
   The provided code uses a slight variation: it accumulates `sum += nums[i]`, and if this `sum`
   becomes negative, it resets `sum = 0`, effectively starting a new subarray from the next element.
   This reset is key: if `sum` (the sum of a subarray ending at the current position) is negative,
   it will only detract from any larger subarray that includes it as a prefix. So, it's better
   to discard it and consider a new subarray starting from the next element.

2. `max_so_far` (represented as `maxi` in the provided code):
   This is the global maximum sum found across all subarrays encountered so far during the iteration.
   After updating `current_max_ending_here` at each step, `max_so_far` is updated to be the
   maximum of its current value and `current_max_ending_here`.

How the Provided Code Implements Kadane's Algorithm:

1. Initialization:
   - `int maxi = nums[0];`
     `maxi` (our `max_so_far`) is initialized with the first element of the array.
     This handles the case where all numbers are negative (the max subarray would be the largest single negative number)
     or when the array has only one element. If the array could be empty, `maxi` might be initialized
     to `std::numeric_limits<int>::min()`, but LeetCode constraints often ensure `nums` is not empty.
   - `int sum = 0;`
     `sum` (our `current_max_ending_here`, though used slightly differently) is initialized to 0.
     This variable will accumulate the sum of the current subarray being considered.

2. Iteration:
   - `for(int i = 0; i < nums.size(); i++)`:
     The code iterates through each element of the array `nums`.

3. Updating Current Subarray Sum and Global Maximum:
   - `sum += nums[i];`
     The current element `nums[i]` is added to `sum`. `sum` now represents the sum of a
     contiguous subarray ending at index `i` (potentially starting from a previous point where `sum` was reset).
   - `maxi = std::max(maxi, sum);`
     The global maximum `maxi` is updated if the current `sum` (sum of subarray ending at `i`)
     is greater than the `maxi` found so far.

4. Resetting Current Subarray Sum if Negative:
   - `if(sum < 0) sum = 0;`
     This is the core of Kadane's. If `sum` becomes negative, it means that the subarray
     ending at the current position `i` has a negative sum. Including this subarray as a prefix
     to any future subarray will only decrease the future subarray's sum.
     Therefore, we discard this current subarray by resetting `sum` to 0, effectively indicating
     that the next potential maximum subarray should start from the next element (`nums[i+1]`).

5. Return Result:
   - `return maxi;`
     After iterating through the entire array, `maxi` will hold the maximum sum of any
     contiguous subarray found.

Visual Dry Run Example: nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
Initial: maxi = -2, sum = 0

| i | nums[i] | sum += nums[i] | maxi = max(maxi, sum) | if(sum < 0) sum = 0 | Notes                     |
|---|---------|----------------|-----------------------|---------------------|---------------------------|
| 0 | -2      | 0 + (-2) = -2  | max(-2, -2) = -2      | sum is -2 (<0) -> sum=0 |                           |
| 1 |  1      | 0 + 1    =  1  | max(-2, 1)  =  1      | sum is 1 (>=0)      |                           |
| 2 | -3      | 1 + (-3) = -2  | max(1, -2)  =  1      | sum is -2 (<0) -> sum=0 | Discard [-3], [1,-3]      |
| 3 |  4      | 0 + 4    =  4  | max(1, 4)   =  4      | sum is 4 (>=0)      | Start new: [4]            |
| 4 | -1      | 4 + (-1) =  3  | max(4, 3)   =  4      | sum is 3 (>=0)      | Extend: [4,-1]            |
| 5 |  2      | 3 + 2    =  5  | max(4, 5)   =  5      | sum is 5 (>=0)      | Extend: [4,-1,2]          |
| 6 |  1      | 5 + 1    =  6  | max(5, 6)   =  6      | sum is 6 (>=0)      | Extend: [4,-1,2,1]        |
| 7 | -5      | 6 + (-5) =  1  | max(6, 1)   =  6      | sum is 1 (>=0)      | Extend: [4,-1,2,1,-5]     |
| 8 |  4      | 1 + 4    =  5  | max(6, 5)   =  6      | sum is 5 (>=0)      | Extend: [4,-1,2,1,-5,4]   |

End of loop. Return maxi = 6.

Algorithm Properties:

1. Time Complexity: O(N)
   - The algorithm involves a single pass through the array `nums`.
   - Each operation inside the loop (addition, comparison, assignment) takes constant time.

2. Space Complexity: O(1)
   - Only a few extra variables (`maxi`, `sum`, loop counter `i`) are used, regardless of the input array size.

Edge Cases:
- Array with all negative numbers: e.g., `nums = [-2, -1, -5, -3]`
  - maxi = -2, sum = 0
  - i=0, num=-2: sum=-2, maxi=-2, sum=0
  - i=1, num=-1: sum=-1, maxi=max(-2,-1)=-1, sum=0
  - i=2, num=-5: sum=-5, maxi=max(-1,-5)=-1, sum=0
  - i=3, num=-3: sum=-3, maxi=max(-1,-3)=-1, sum=0
  - Returns -1 (correct, the largest single number).
- Array with all positive numbers: e.g., `nums = [1, 2, 3]`
  - sum will accumulate, maxi will track the cumulative sum. Returns 6 (correct).
- Array with one element: e.g., `nums = [5]`
  - maxi=5, sum=0
  - i=0, num=5: sum=5, maxi=5. sum is not <0.
  - Returns 5 (correct).
- Array with mixed positive and negative values: Handled by the standard logic as shown in the dry run.
- Empty Array: The current code `maxi = nums[0]` would fail. If empty arrays are possible per constraints,
  a check `if (nums.empty()) return 0;` (or appropriate value) would be needed at the beginning.
  LeetCode problem 53 constraints state `nums.length >= 1`.

Why Kadane's Algorithm Works (Intuition):
At any point `i` in the array, the maximum subarray ending at `i` is either `nums[i]` itself or `nums[i]` combined with the maximum subarray ending at `i-1`.
Kadane's algorithm simplifies this. The `sum` variable tracks the sum of the current, potentially optimal, subarray ending at `i`.
If `sum` becomes negative, it means that this current prefix (the subarray ending at `i` with sum `sum`) is detrimental to any subarray that would extend further. Starting a new subarray from `nums[i+1]` (by resetting `sum` to 0 and then adding `nums[i+1]` in the next iteration) has a better chance of yielding a larger sum than extending a subarray that already has a negative total.
The `maxi` variable simply keeps track of the largest such `sum` encountered at any point, ensuring that even if a later subarray is smaller, we've already recorded the overall maximum.

*/

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        // Constraints: nums.length >= 1, so nums[0] is safe.
        int maxi = nums[0]; // Stores the maximum subarray sum found so far.
                            // Initialized with the first element to handle cases like all negatives or single element array.
        int sum = 0;        // Stores the sum of the current contiguous subarray ending at the current position.
                            // This is Kadane's current_max_ending_here, reset when it goes negative.

        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i]; // Add the current element to the current subarray sum.

            // Update the overall maximum sum if the current subarray's sum is greater.
            if (sum > maxi) {
                maxi = sum;
            }
            // This can also be written as: maxi = std::max(maxi, sum);
            // (The original code had maxi = max(maxi, sum); which is fine after sum is updated)
            // For clarity with the provided code structure, I'll keep the if, but will adjust the original code's order slightly for flow.
            // Let's revert to the original structure, as it's common: update sum, then maxi, then reset sum if needed.

            // The original code structure was effectively:
            // sum += nums[i];
            // maxi = std::max(maxi, sum);
            // if (sum < 0) sum = 0;
            // This is correct. I'll use this structure below.
        }

        // Re-implementing the loop with the standard Kadane logic flow for clarity based on the provided solution:
        maxi = nums[0]; // Re-initialize for this clear loop, as `sum` behavior matters.
        sum = 0;
        for(int i = 0; i < nums.size(); i++){
            sum += nums[i];         // Extend the current subarray or start a new one implicitly if sum was 0.
            maxi = std::max(maxi, sum); // Update the global maximum found so far.

            if(sum < 0) {           // If the sum of the current subarray (ending at nums[i]) is negative,
                sum = 0;            // it cannot be part of any future optimal subarray. Reset to 0.
                                    // This means the next subarray will start fresh from nums[i+1].
            }
        }
        return maxi;
    }
};

// int main() {
//     Solution sol;

//     std::vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
//     std::cout << "Input: [-2, 1, -3, 4, -1, 2, 1, -5, 4], Output: " << sol.maxSubArray(nums1) << std::endl; // Expected: 6

//     std::vector<int> nums2 = {1};
//     std::cout << "Input: [1], Output: " << sol.maxSubArray(nums2) << std::endl; // Expected: 1

//     std::vector<int> nums3 = {5, 4, -1, 7, 8};
//     std::cout << "Input: [5, 4, -1, 7, 8], Output: " << sol.maxSubArray(nums3) << std::endl; // Expected: 23

//     std::vector<int> nums4 = {-1, -2, -3, -4};
//     std::cout << "Input: [-1, -2, -3, -4], Output: " << sol.maxSubArray(nums4) << std::endl; // Expected: -1

//     std::vector<int> nums5 = {0, 0, 0, 0};
//     std::cout << "Input: [0,0,0,0], Output: " << sol.maxSubArray(nums5) << std::endl; // Expected: 0

//     std::vector<int> nums6 = {-2, -1};
//     std::cout << "Input: [-2, -1], Output: " << sol.maxSubArray(nums6) << std::endl; // Expected: -1

//     return 0;
// }