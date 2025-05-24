#include <vector>
#include <iostream> // For main example

/*
Problem: Find Peak Element (LeetCode 162)

A peak element is an element that is strictly greater than its neighbors.
Given an integer array `nums`, find a peak element, and return its index.
If the array contains multiple peaks, return the index to **any one** of them.

You may imagine that `nums[-1] = nums[n] = -infinity`. This means for an element `nums[i]`:
- If `i=0`, it's a peak if `nums[0] > nums[1]` (or if `n=1`).
- If `i=n-1`, it's a peak if `nums[n-1] > nums[n-2]` (or if `n=1`).
- Otherwise, it's a peak if `nums[i] > nums[i-1]` AND `nums[i] > nums[i+1]`.

The problem guarantees `nums[i] != nums[i+1]` for all valid `i`.
You must write an algorithm that runs in O(log n) time.

Example 1:
Input: nums = [1,2,3,1]
Output: 2 (Index of element 3, which is a peak)

Example 2:
Input: nums = [1,2,1,3,5,6,4]
Output: 5 (Index of element 6) or 1 (Index of element 2)

Concept (Modified Binary Search):
The array is not necessarily sorted globally, but we can still apply a binary search-like approach.
The key idea is to compare the middle element `nums[mid]` with its right neighbor `nums[mid+1]`
to determine the direction in which a peak must lie.

1. If `nums[mid] > nums[mid+1]`:
   - This means the numbers are decreasing at `mid` towards `mid+1`.
   - `nums[mid]` itself could be a peak (e.g., ...2,5,1...).
   - Or, a peak might exist to the left of `mid` (e.g., ...5,2,1... here 5 is a peak to the left).
   - In this case, we can confidently say that a peak exists in the range `[low, mid]` (inclusive of `mid`).
     So, we can discard the right half by setting `high = mid`.

2. If `nums[mid] < nums[mid+1]`:
   - This means the numbers are increasing at `mid` towards `mid+1`.
   - `nums[mid]` cannot be a peak because its right neighbor is greater.
   - A peak must exist in the range `[mid+1, high]`. This is because the numbers are currently rising,
     and since `nums[n]` is conceptually -infinity, they must eventually fall, creating a peak.
   - So, we can discard the left half (including `mid`) by setting `low = mid + 1`.

The loop `while (low < high)` ensures that the search space `[low, high]` always contains at least two
elements until `low` and `high` converge. When `low == high`, that index must point to a peak element.

How the Code Works:

1. Initialization:
   - `int low = 0;`: `low` pointer initialized to the start of the array.
   - `int high = nums.size() - 1;`: `high` pointer initialized to the end of the array.
     Handles `nums.size()=0` implicitly if such case was allowed (but problem constraints usually say `nums.length >= 1`).
     If `nums.size()=1`, then `low=0, high=0`. The `while` loop condition `low < high` (0 < 0) is false,
     and it directly returns `low = 0`, which is correct for a single-element array (it's a peak).

2. Binary Search Loop:
   - `while (low < high)`: The loop continues as long as `low` is strictly less than `high`,
     meaning the search space has at least two elements.
   - `int mid = low + (high - low) / 2;`: Calculates the middle index.
     This calculation ensures `mid` is always less than `high` when `low < high`.
     Therefore, `mid + 1` is always a valid index within the bounds `[low, high]` during the loop.

3. Comparison and Search Space Reduction:
   - `if (nums[mid] > nums[mid+1])`:
     - If the element at `mid` is greater than its right neighbor `nums[mid+1]`:
       A peak is guaranteed to be in the left part, including `mid` itself.
       - `high = mid;`: Narrow the search space to `[low, mid]`. `mid` is kept as it's a potential peak.
   - `else` (which implies `nums[mid] < nums[mid+1]` because `nums[mid] != nums[mid+1]`):
     - If the element at `mid` is less than its right neighbor `nums[mid+1]`:
       `nums[mid]` cannot be a peak. The peak must lie to the right, where values are increasing.
       - `low = mid + 1;`: Narrow the search space to `[mid + 1, high]`. `mid` is excluded.

4. Return Result:
   - `return low;`: When the loop terminates, `low == high`. This index `low` (or `high`)
     points to a peak element.

Visual Dry Run Example: nums = [1,2,3,1]
Initial: low=0, high=3

1. low=0, high=3: mid = 0 + (3-0)/2 = 1. nums[1]=2, nums[2]=3.
   nums[mid] (2) < nums[mid+1] (3).
   low = mid + 1 = 1 + 1 = 2.
   (low=2, high=3)

2. low=2, high=3: mid = 2 + (3-2)/2 = 2. nums[2]=3, nums[3]=1.
   nums[mid] (3) > nums[mid+1] (1).
   high = mid = 2.
   (low=2, high=2)

3. low=2, high=2: `low < high` (2 < 2) is false. Loop terminates.

Return low = 2. (nums[2] = 3 is a peak). Correct.

Algorithm Properties:

- Time Complexity: O(log N)
  - Where N is the number of elements in `nums`.
  - Each step of the binary search reduces the search space by approximately half.

- Space Complexity: O(1)
  - The search is performed in-place using a few variables.

Edge Cases Handled by the Logic:
- Single Element Array: `nums = [5]`. `low=0, high=0`. Loop `0 < 0` is false. Returns `low=0`. Correct.
- Two Elements:
  - `nums = [1,2]`: low=0, high=1. mid=0. nums[0](1) < nums[1](2). low=1. Loop (1<1) is false. Returns `low=1`. Correct (peak is 2).
  - `nums = [2,1]`: low=0, high=1. mid=0. nums[0](2) > nums[1](1). high=0. Loop (0<0) is false. Returns `low=0`. Correct (peak is 2).
- Strictly Increasing Array: `nums = [1,2,3,4]`. Peak is the last element (index 3).
  - low=0,high=3 -> mid=1. nums[1]<nums[2] -> low=2.
  - low=2,high=3 -> mid=2. nums[2]<nums[3] -> low=3.
  - low=3,high=3. Loop ends. Returns `low=3`. Correct.
- Strictly Decreasing Array: `nums = [4,3,2,1]`. Peak is the first element (index 0).
  - low=0,high=3 -> mid=1. nums[1]>nums[2] -> high=1.
  - low=0,high=1 -> mid=0. nums[0]>nums[1] -> high=0.
  - low=0,high=0. Loop ends. Returns `low=0`. Correct.

Why this Binary Search Variant Works:
The crucial part is that by comparing `nums[mid]` with `nums[mid+1]`, we determine the "slope" of the array at `mid`.
- If slope is downwards (`nums[mid] > nums[mid+1]`), a peak must exist at or before `mid`.
- If slope is upwards (`nums[mid] < nums[mid+1]`), a peak must exist after `mid`.
Since the problem implies `nums[-1]` and `nums[n]` are negative infinity, there must always be at least one peak.
The binary search correctly narrows down the search space to one such peak.
The condition `nums[i] != nums[i+1]` ensures there are no plateaus to complicate the slope detection.
*/

class Solution {
public:
    int findPeakElement(std::vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;

        // The loop continues as long as there is more than one element in the search space.
        // When low == high, we have found our peak element.
        while (low < high) {
            int mid = low + (high - low) / 2;

            // If nums[mid] is greater than its right neighbor, then mid could be a peak,
            // or a peak is in the left half (including mid).
            if (nums[mid] > nums[mid + 1]) {
                high = mid; // So, we search in the range [low, mid]
            }
            // Otherwise (nums[mid] < nums[mid + 1] because nums[i] != nums[i+1]),
            // nums[mid] is not a peak, and the peak must be in the right half.
            else {
                low = mid + 1; // So, we search in the range [mid + 1, high]
            }
        }

        // When low == high, this index points to a peak element.
        return low;
    }
};

// int main() {
//     Solution sol;
//     std::vector<int> nums;

//     // Test Case 1
//     nums = {1,2,3,1};
//     std::cout << "Nums: [1,2,3,1], Expected Peak Index: 2, Got: " << sol.findPeakElement(nums) << std::endl;

//     // Test Case 2
//     nums = {1,2,1,3,5,6,4};
//     int peak_idx = sol.findPeakElement(nums);
//     std::cout << "Nums: [1,2,1,3,5,6,4], Expected Peak Index: 1 or 5, Got: " << peak_idx << " (Value: " << nums[peak_idx] << ")" << std::endl;

//     // Test Case 3: Single element
//     nums = {10};
//     std::cout << "Nums: [10], Expected Peak Index: 0, Got: " << sol.findPeakElement(nums) << std::endl;

//     // Test Case 4: Two elements, increasing
//     nums = {1,5};
//     std::cout << "Nums: [1,5], Expected Peak Index: 1, Got: " << sol.findPeakElement(nums) << std::endl;

//     // Test Case 5: Two elements, decreasing
//     nums = {5,1};
//     std::cout << "Nums: [5,1], Expected Peak Index: 0, Got: " << sol.findPeakElement(nums) << std::endl;

//     // Test Case 6: Strictly increasing
//     nums = {1,2,3,4,5};
//     std::cout << "Nums: [1,2,3,4,5], Expected Peak Index: 4, Got: " << sol.findPeakElement(nums) << std::endl;

//     // Test Case 7: Strictly decreasing
//     nums = {5,4,3,2,1};
//     std::cout << "Nums: [5,4,3,2,1], Expected Peak Index: 0, Got: " << sol.findPeakElement(nums) << std::endl;

//     // Test Case 8: All elements same (Problem constraint nums[i] != nums[i+1] avoids this)
//     // nums = {3,3,3,3};
//     // This case shouldn't occur based on constraints. If it did, behavior might be specific.

//     // Test Case 9: Peak at the beginning
//     nums = {3,1,2};
//     std::cout << "Nums: [3,1,2], Expected Peak Index: 0, Got: " << sol.findPeakElement(nums) << std::endl;

//     // Test Case 10: Peak at the end
//     nums = {1,2,5};
//     std::cout << "Nums: [1,2,5], Expected Peak Index: 2, Got: " << sol.findPeakElement(nums) << std::endl;
    
//     // Test Case 11: Longer array with multiple peaks
//     nums = {1,5,2,6,3,7,4};
//     peak_idx = sol.findPeakElement(nums);
//     std::cout << "Nums: [1,5,2,6,3,7,4], Potential Peak Indices: 1,3,5, Got: " << peak_idx << " (Value: " << nums[peak_idx] << ")" << std::endl;

//     return 0;
// }