#include <vector>
#include <algorithm> // For std::max, std::min
#include <numeric>   // For std::accumulate (alternative for totalSum, though not used here)
#include <iostream>  // For main example
#include <limits>    // For std::numeric_limits (not strictly needed with current init)

/*
Problem: Maximum Sum Circular Subarray (LeetCode 918)
Given a circular integer array `nums` of length `n`, return the maximum possible sum of a
non-empty subarray of `nums`.A circular array means the end of the array connects to the beginning. Formally, the next
element of `nums[i]` is `nums[(i + 1) % n]` and the previous element of `nums[i]` is
`nums[(i - 1 + n) % n]`.A subarray may only include each element of the fixed buffer `nums` at most once.Concept:The maximum sum of a circular subarray can arise from two scenarios:1. Case 1: The Maximum Subarray is Non-Wrapping (Standard Kadane\'s)   The subarray with the maximum sum does not wrap around the circular array.   This can be found using the standard Kadane\'s algorithm.   Let this be `max_kadane_sum`.2. Case 2: The Maximum Subarray is Wrapping   The subarray with the maximum sum wraps around (e.g., includes elements from the end
of the array and the beginning).   If a wrapping subarray `A[i...n-1] + A[0...j]` has the maximum sum, then the elements
*not* included in this wrapping subarray (`A[j+1...i-1]`) must form a contiguous non-wrapping
subarray with the *minimum possible sum*.   So, the sum of this wrapping subarray = `Total Sum of Array - Sum of Minimum Contiguous Non-Wrapping Subarray`.   Let this be `wrap_around_sum = total_array_sum - min_kadane_sum`.   The `min_kadane_sum` can be found by adapting Kadane\'s algorithm to find the minimum sum.Overall Solution:The answer is generally `std::max(max_kadane_sum, wrap_around_sum)`.Special Edge Case: All Elements are Negative   If all elements in the array are negative, `max_kadane_sum` will correctly be the largest
(least negative) element. In this scenario, `min_kadane_sum` will be equal to `total_array_sum`
(as the entire array itself is the minimum sum subarray).   This would make `wrap_around_sum = total_array_sum - total_array_sum = 0`.   However, 0 is not the correct answer if all elements are negative (e.g., for `[-1, -2, -3]`, max sum is -1, not 0).   The code handles this: if `max_kadane_sum` is negative, it means this is the best possible sum,   as a wrapping sum (which implies some elements are positive relative to the min subarray to be beneficial)   cannot be better than an already negative `max_kadane_sum`. So, if `max_kadane_sum < 0`, we return `max_kadane_sum`.   This also covers the case where the entire array sums to zero but `max_kadane_sum` is positive, where `totalSum - minSum` could be zero if `minSum` is also `totalSum` (e.g. `[1, -1, 1, -1]`, `totalSum=0, minSum=0`, `maxSum=1`. `max(1, 0-0)=1`).How the Provided Code Implements This:1. Initialization:   - `totalSum = 0`: To store the sum of all elements in `nums`.   - `maxSum = nums[0]`: Stores the result of Kadane\'s algorithm for maximum sum (Case 1).   - `curMax = 0`: Current maximum sum ending at the current element for `maxSum` calculation.   - `minSum = nums[0]`: Stores the result of Kadane-like algorithm for minimum sum (for Case 2).   - `curMin = 0`: Current minimum sum ending at the current element for `minSum` calculation.2. Single Pass Iteration:   - The code iterates through each `num` in `nums` once.   - `totalSum += num`: Accumulates the total sum of the array.   - Standard Kadane for `maxSum`:     - `curMax = std::max(num, curMax + num);` (or `curMax = num + std::max(0, curMax);` if `curMax` was initialized to `num` initially)       The line `curMax = max(num, curMax + num)` correctly implements: the max subarray ending here is either `num` itself, or `num` added to the max subarray ending at the previous element.     - `maxSum = std::max(maxSum, curMax);`   - Kadane-like adaptation for `minSum`:     - `curMin = std::min(num, curMin + num);`       Similarly, the min subarray ending here is `num` itself, or `num` added to the min subarray ending at the previous element.     - `minSum = std::min(minSum, curMin);`3. Handling the Edge Case (All Negatives / `maxSum < 0`):   - `if (maxSum < 0)`:     If `maxSum` is negative, it implies that even the best non-wrapping subarray sum is negative.     In this scenario, any wrapping subarray sum (`totalSum - minSum`) is unlikely to be better
(it would typically be 0 if `minSum == totalSum`, or still negative). The problem requires a non-empty subarray.     Thus, `maxSum` (the largest/least negative element or sum) is the correct answer.4. Return Result:   - `return std::max(maxSum, totalSum - minSum);`     If `maxSum` is not negative, this returns the maximum of the non-wrapping max sum (`maxSum`)     and the potential wrapping max sum (`totalSum - minSum`).Visual Dry Run Example 1: nums = [5, -3, 5]Initial: totalSum=0, maxSum=5, curMax=0, minSum=5, curMin=0| num | totalSum | curMax=max(num,curMax+num) | maxSum=max(maxSum,curMax) | curMin=min(num,curMin+num) | minSum=min(minSum,curMin) ||-----|----------|---------------------------|---------------------------|---------------------------|---------------------------||  5  | 5        | max(5, 0+5)=5             | max(5,5)=5                | min(5, 0+5)=5             | min(5,5)=5                || -3  | 2        | max(-3,5-3)=2             | max(5,2)=5                | min(-3,5-3)=2             | min(5,2)=2                ||  5  | 7        | max(5, 2+5)=7             | max(5,7)=7                | min(5, 2+5)=7             | min(2,7)=2                |End of loop: totalSum=7, maxSum=7, minSum=2.`maxSum` (7) is not < 0.Return `max(maxSum, totalSum - minSum) = max(7, 7 - 2) = max(7, 5) = 7`.Wait, `[5, (skip -3), 5]` -> `5+5=10`. Here `totalSum - minSum` = `7 - (-3)` (if minSum was correctly -3) = 10. Let\'s trace minSum carefully.If num = -3, `curMin = min(-3, 0-3) = -3`. `minSum = min(5, -3) = -3`.Let\'s re-trace `curMin` and `minSum` initialization with `curMin = 0` for consistency with typical Kadane.If `curMin` is current min ending at previous position, then current min ending here is `num + curMin` or `num`.Code has `curMin = min(num, curMin + num)`. Let\'s assume `curMin` is initialized to 0.Revised Dry Run 1: nums = [5, -3, 5]Initial: totalSum=0, maxSum=nums[0]=5, curMax=0, minSum=nums[0]=5, curMin=0| num | totalSum | curMax=max(num,curMax+num) | maxSum=max(maxSum,curMax) | curMin=min(num,curMin+num) | minSum=min(minSum,curMin) ||-----|----------|---------------------------|---------------------------|---------------------------|---------------------------||  5  | 5        | max(5, 0+5)=5             | max(5,5)=5                | min(5, 0+5)=5             | min(5,5)=5                || -3  | 2        | max(-3,5-3)=2             | max(5,2)=5                | min(-3,5-3)=2             | min(5,2)=2                |    If `curMin` for `num=5` was 5: next `curMin` for `num=-3` is `min(-3, 5-3=2) = -3` (Error in table for curMin(-3)). `minSum` becomes `min(5, -3) = -3`.|  5  | 7        | max(5, 2+5)=7             | max(5,7)=7                | min(5, -3+5=2)            | min(-3,2)=-3              |End of loop: totalSum=7, maxSum=7, minSum=-3.`maxSum` (7) is not < 0.Return `max(maxSum, totalSum - minSum) = max(7, 7 - (-3)) = max(7, 10) = 10`. Correct. (Subarray [5,5] wraps around).Visual Dry Run Example 2: nums = [1, -2, 3, -2]Initial: totalSum=0, maxSum=1, curMax=0, minSum=1, curMin=0| num | totalSum | curMax | maxSum | curMin | minSum ||-----|----------|--------|--------|--------|--------||  1  | 1        | 1      | 1      | 1      | 1      || -2  | -1       | -1     | 1      | -1     | -1     | (curMax=max(-2,1-2)=-1, curMin=min(-2,1-2)=-1)|  3  | 2        | 3      | 3      | 2      | -1     | (curMax=max(3,-1+3)=3, curMin=min(3,-1+3)=2)| -2  | 0        | 1      | 3      | 0      | -1     | (curMax=max(-2,3-2)=1, curMin=min(-2,2-2)=0)End: totalSum=0, maxSum=3, minSum=-1.`maxSum` (3) is not < 0.Return `max(maxSum, totalSum - minSum) = max(3, 0 - (-1)) = max(3, 1) = 3`. Correct. (Subarray [1,-2,3] or [3]).Visual Dry Run Example 3: nums = [-3, -2, -1]Initial: totalSum=0, maxSum=-3, curMax=0, minSum=-3, curMin=0| num | totalSum | curMax | maxSum | curMin | minSum ||-----|----------|--------|--------|--------|--------|| -3  | -3       | -3     | -3     | -3     | -3     || -2  | -5       | -2     | -2     | -5     | -5     | (curMax=max(-2,-3-2)=-2, curMin=min(-2,-3-2)=-5)| -1  | -6       | -1     | -1     | -6     | -6     | (curMax=max(-1,-2-1)=-1, curMin=min(-1,-5-1)=-6)End: totalSum=-6, maxSum=-1, minSum=-6.`maxSum` (-1) IS < 0.Return `maxSum = -1`. Correct.Algorithm Properties:1. Time Complexity: O(N)   - A single pass is made through the array `nums`.2. Space Complexity: O(1)   - Only a constant number of extra variables are used.Why This Approach Works:- Kadane\'s algorithm correctly finds the maximum (and adapted, minimum) sum for any *non-wrapping* subarray.- The insight `wrapping_max_sum = total_sum - non_wrapping_min_sum` cleverly covers the circular case.- The edge case `maxSum < 0` correctly identifies scenarios where all elements are negative, ensuring the largest single negative value is returned instead of an incorrect positive value (like 0) that `totalSum - minSum` might produce if `minSum == totalSum`.*/

// two cases - 1. normal kadane algorithm pass where sum does not wrap around
// 2. subarray wrap where sum wraps around subarray in circular manner

class Solution {
public:
    int maxSubarraySumCircular(std::vector<int>& nums) {
        if (nums.empty()) {
            return 0; // Or throw an error, problem constraints say nums.length >= 1
        }

        int totalSum = 0;
        // Kadane for maximum sum (non-wrapping)
        int maxSum = nums[0]; // Initialize with first element, as subarray must be non-empty
        int curMax = 0;       // Current max sum ending at this element

        // Kadane-like for minimum sum (non-wrapping)
        int minSum = nums[0]; // Initialize with first element
        int curMin = 0;       // Current min sum ending at this element

        for (int num : nums) {
            totalSum += num;

            // Standard Kadane's for maximum sum ending at current element
            curMax += num;
            if (num > curMax) { // If num itself is greater than extending the previous sequence
                curMax = num;
            }
            // Or, more commonly: curMax = std::max(num, curMax_from_previous_step + num);
            // The provided code structure: curMax is the running sum, reset if it would be better to start with num.
            // Let's use the standard: curMax = std::max(num, current_running_max_ending_here + num)
            // The original code `curMax = max(num, curMax + num)` assumes `curMax` before this line is the sum ending at previous element.
            // Let's trace `curMax = 0` init: 
            // Loop 1 (num=nums[0]): curMax=nums[0]. maxSum=max(nums[0],nums[0])=nums[0]. (Matches init)
            // Loop 1 (num=nums[0]): curMin=nums[0]. minSum=min(nums[0],nums[0])=nums[0]. (Matches init)
            // This means `curMax` and `curMin` should be reset *inside* the loop if starting a new subarray is better.
            // The original logic `curMax = max(num, curMax + num)` is correct for Kadane'.

            // Calculate curMax and maxSum (Kadane's for max subarray sum)
            curMax = std::max(num, curMax + num); // Max sum ending at current element `num`
            maxSum = std::max(maxSum, curMax);    // Overall maximum non-wrapping subarray sum

            // Calculate curMin and minSum (Kadane's for min subarray sum)
            curMin = std::min(num, curMin + num); // Min sum ending at current element `num`
            minSum = std::min(minSum, curMin);    // Overall minimum non-wrapping subarray sum
        }

        // Edge case: If all numbers are negative (or maxSum is negative).
        // In this case, maxSum (the largest negative number) is the answer.
        // totalSum - minSum might be 0 if minSum == totalSum (e.g. all negatives),
        // which would be incorrect.
        if (maxSum < 0) {
            return maxSum;
        }

        // The maximum circular sum is the maximum of:
        // 1. maxSum (the max sum of a non-wrapping subarray)
        // 2. totalSum - minSum (the max sum of a wrapping subarray)
        return std::max(maxSum, totalSum - minSum);
    }
};

// int main() {
//     Solution sol;
//     std::vector<int> nums1 = {1, -2, 3, -2};
//     std::cout << "Input: [1,-2,3,-2], Output: " << sol.maxSubarraySumCircular(nums1) << std::endl; // Expected: 3

//     std::vector<int> nums2 = {5, -3, 5};
//     std::cout << "Input: [5,-3,5], Output: " << sol.maxSubarraySumCircular(nums2) << std::endl; // Expected: 10

//     std::vector<int> nums3 = {3, -1, 2, -1};
//     std::cout << "Input: [3,-1,2,-1], Output: " << sol.maxSubarraySumCircular(nums3) << std::endl; // Expected: 4 (3+ -1 + 2 = 4 or 3+ -1 + 2 + -1 then wrap for 3 => 3 + -1 = 2)
//                                                                                                 // total=3, max=4 (3,-1,2), min=-1. max(4, 3 - (-1)) = max(4,4)=4.

//     std::vector<int> nums4 = {3, -2, 2, -3};
//     std::cout << "Input: [3,-2,2,-3], Output: " << sol.maxSubarraySumCircular(nums4) << std::endl; // Expected: 3 (wrap [3] or [3,-2,2]) total=0, max=3, min=-3. max(3, 0 - (-3))=max(3,3)=3

//     std::vector<int> nums5 = {-2, -3, -1};
//     std::cout << "Input: [-2,-3,-1], Output: " << sol.maxSubarraySumCircular(nums5) << std::endl; // Expected: -1

//     std::vector<int> nums6 = {1};
//     std::cout << "Input: [1], Output: " << sol.maxSubarraySumCircular(nums6) << std::endl; // Expected: 1

//     std::vector<int> nums7 = {-1};
//     std::cout << "Input: [-1], Output: " << sol.maxSubarraySumCircular(nums7) << std::endl; // Expected: -1
   
//     std::vector<int> nums8 = {2, -2, 2, -2, 2};
//     // totalSum = 2
//     // curMax: 2, 0, 2, 0, 2 -> maxSum = 2
//     // curMin: 2, 0, 2, 0, 2 -> minSum = 0 (from empty prefix if curMin started at 0 for those)
//     // Let's re-check curMin trace. curMin is min(num, curMin+num)
//     // num | curMin_before | curMin_after | minSum
//     // 2   | 0             | min(2,0+2)=2 | 2 (init with nums[0]=2)
//     // -2  | 2             | min(-2,2-2)=0| 0
//     // 2   | 0             | min(2,0+2)=2 | 0
//     // -2  | 2             | min(-2,2-2)=0| 0
//     // 2   | 0             | min(2,0+2)=2 | 0
//     // So, minSum = 0.
//     // maxSum = 2. totalSum = 2.
//     // max(2, 2 - 0) = max(2,2) = 2. This is correct. Subarrays are [2], [2,-2,2], etc.
//     std::cout << "Input: [2,-2,2,-2,2], Output: " << sol.maxSubarraySumCircular(nums8) << std::endl; // Expected: 2

//    std::vector<int> nums9 = {8, -1, 3, 4};
//    // total: 14
//    // max: 8 -> 7 -> 10 -> 14. maxSum = 14
//    // min: 8 -> -1 -> 2 -> 6. minSum = -1
//    // result: max(14, 14 - (-1)) = max(14, 15) = 15.
//    // Wrapping: [8, (skip -1), 3, 4] => 8+3+4 = 15.
//    std::cout << "Input: [8,-1,3,4], Output: " << sol.maxSubarraySumCircular(nums9) << std::endl; // Expected: 15

//     return 0;
// }
