#include <vector>
#include <iostream>  // For main example
// #include <algorithm> // For std::lower_bound (for comparison, not used in this specific solution)

/*
Problem: Search Insert Position (LeetCode 35)
Given a sorted array of distinct integers `nums` and a target value `target`,
return the index if the target is found. If not, return the index where it would be
if it were inserted in order.

You must write an algorithm with O(log n) runtime complexity.

Example 1:
Input: nums = [1,3,5,6], target = 5
Output: 2 (Target 5 is found at index 2)

Example 2:
Input: nums = [1,3,5,6], target = 2
Output: 1 (Target 2 would be inserted at index 1: [1,2,3,5,6])

Example 3:
Input: nums = [1,3,5,6], target = 7
Output: 4 (Target 7 would be inserted at index 4: [1,3,5,6,7])

Example 4:
Input: nums = [1,3,5,6], target = 0
Output: 0 (Target 0 would be inserted at index 0: [0,1,3,5,6])

Example 5:
Input: nums = [1], target = 0
Output: 0

Concept (Binary Search for Lower Bound):
The problem asks us to find the index of the target if it exists, or the index where it
should be inserted to maintain the sorted order if it doesn't exist.
This is equivalent to finding the "lower bound" of the target value.
The lower bound is the index of the first element in the sorted array that is greater
than or equal to the target.

Binary search is the appropriate algorithm here because the input array `nums` is sorted,
allowing us to achieve the required O(log N) time complexity.

How the Code Works:

1. Initialization:
   - `int low = 0;`: `low` pointer is initialized to the start of the array (index 0).
   - `int high = nums.size() - 1;`: `high` pointer is initialized to the end of the array.
     If `nums` is empty, `nums.size()` is 0, so `high` becomes -1.
   - `int ans = nums.size();`: `ans` is initialized to `nums.size()`. This is a crucial step.
     If the target is greater than all elements in `nums`, it should be inserted at the very end,
     which is index `nums.size()`. This default value for `ans` handles this case correctly.
     During the search, `ans` will be updated to `mid` whenever `nums[mid] >= target`, effectively
     tracking the smallest index found so far where the target could be inserted or is located.

2. Binary Search Loop:
   - `while (low <= high)`: The loop continues as long as the search space defined by `low` and `high`
     is valid (i.e., `low` has not crossed `high`).
   - `int mid = low + (high - low) / 2;`: Calculates the middle index of the current search space.
     This way of calculating `mid` is preferred over `(low + high) / 2` to prevent potential
     integer overflow if `low` and `high` are very large (though `(low + high) / 2` is used in the original code and often fine for typical constraints).

3. Comparison and Search Space Reduction:
   - `if (nums[mid] >= target)`:
     - If the element at `nums[mid]` is greater than or equal to the `target`:
       This means `nums[mid]` could be the target itself, or it's an element greater than the target.
       In either scenario, `mid` is a potential candidate for the insertion position (or the index of the target).
       - `ans = mid;`: We update `ans` with this `mid` because it's a valid position (or better than the previous `ans`).
       - `high = mid - 1;`: Since we are looking for the *first* such element (the lower bound),
         we try to find if an even earlier (smaller index) position exists. So, we narrow the search
         to the left half of the current space (excluding `mid` because `mid` is already considered in `ans`).
   - `else` (i.e., `nums[mid] < target`):
     - If the element at `nums[mid]` is strictly less than the `target`:
       The target (or its correct insertion point) must be in the right half of the current search space,
       as all elements up to and including `nums[mid]` are too small.
       - `low = mid + 1;`: We narrow the search to the right half (excluding `mid`).

4. Return Result:
   - `return ans;`: After the loop terminates (when `low > high`), `ans` will hold the index of the
     first element that was greater than or equal to `target`. If all elements in `nums` were
     smaller than `target`, `ans` remains `nums.size()`. This value is precisely the required
     insertion position according to the problem statement.

Visual Dry Run Example: nums = [1,3,5,6], target = 2
Initial: low=0, high=3, ans=4

1. low=0, high=3: mid = 0+(3-0)/2 = 1. nums[1]=3.
   nums[1] (3) >= target (2) is true.
   ans = 1.
   high = mid - 1 = 1 - 1 = 0.
   (low=0, high=0, ans=1)

2. low=0, high=0: mid = 0+(0-0)/2 = 0. nums[0]=1.
   nums[0] (1) >= target (2) is false.
   low = mid + 1 = 0 + 1 = 1.
   (low=1, high=0, ans=1)

3. low=1, high=0: `low <= high` (1 <= 0) is false. Loop terminates.

Return ans = 1. Correct, 2 would be inserted at index 1: [1, *2*, 3, 5, 6].

Visual Dry Run Example: nums = [1,3,5,6], target = 7
Initial: low=0, high=3, ans=4

1. low=0, high=3: mid=1. nums[1]=3.
   nums[1] (3) >= target (7) is false.
   low = mid + 1 = 2.
   (low=2, high=3, ans=4)

2. low=2, high=3: mid = 2+(3-2)/2 = 2. nums[2]=5.
   nums[2] (5) >= target (7) is false.
   low = mid + 1 = 3.
   (low=3, high=3, ans=4)

3. low=3, high=3: mid = 3+(3-3)/2 = 3. nums[3]=6.
   nums[3] (6) >= target (7) is false.
   low = mid + 1 = 4.
   (low=4, high=3, ans=4)

4. low=4, high=3: `low <= high` (4 <= 3) is false. Loop terminates.

Return ans = 4. Correct, 7 would be inserted at index 4: [1,3,5,6,*7*].

Algorithm Properties:

- Time Complexity: O(log N)
  - Where N is the number of elements in `nums`.
  - Each step of the binary search reduces the search space by approximately half.

- Space Complexity: O(1)
  - The search is performed in-place using only a few variables (`low`, `high`, `mid`, `ans`).

Edge Cases Handled by the Logic:
- Target is present in the array: `ans` will be updated to the index of the target if `nums[mid] == target`,
  and then `high` will be `mid-1`. If other occurrences of target exist to the left, `ans` will find the first one.
- Target is not present and needs to be inserted at the beginning: e.g., `nums=[1,3], target=0`. `ans` initialized to `nums.size()=2`.
  - mid=0, nums[0]=1 >= 0. ans=0, high=-1. Loop ends. Returns 0.
- Target is not present and needs to be inserted in the middle: (Covered by `target=2` example).
- Target is not present and needs to be inserted at the end: (Covered by `target=7` example, `ans` remains `nums.size()`).
- Empty Array `nums=[]`:
  - `low=0`, `high = 0-1 = -1`, `ans=0`.
  - `while(0 <= -1)` is false. Loop doesn't run.
  - Returns `ans = 0`. This is correct; an element inserted into an empty array goes to index 0.

Why this Binary Search Variant Works (Finding Lower Bound):
The key is the behavior when `nums[mid] >= target`:
- `ans = mid;`: We record `mid` as a potential answer because `nums[mid]` is either the target or an element where the target could be inserted before it.
- `high = mid - 1;`: We then try to find an even better (smaller index) answer in the left part.
If the loop finishes, `ans` holds the smallest index `i` such that `nums[i] >= target`. If no such element exists (target is larger than all elements), `ans` correctly remains `nums.size()`.
This is precisely the definition of the lower bound insertion point.
*/

class Solution {
public:
    int searchInsert(std::vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;
        // ans is initialized to nums.size(). This handles the case where the target
        // is greater than all elements in the array, or if the array is empty.
        int ans = nums.size(); 

        while (low <= high) {
            // Using (low + high) / 2 is common; low + (high - low) / 2 avoids potential overflow for very large low/high.
            int mid = low + (high - low) / 2; 
            // Original code used: int mid = (low + high)/2;

            if (nums[mid] >= target) {
                // If nums[mid] is the target or greater than target, then mid is a potential insertion point.
                // We store it and try to find an even smaller index in the left half.
                ans = mid;
                high = mid - 1; 
            } else {
                // If nums[mid] is less than target, the insertion point must be in the right half.
                low = mid + 1;
            }
        }

        return ans;
    }
};

// int main() {
//     Solution sol;
//     std::vector<int> nums;
//     int target;

//     // Test Case 1: Target found
//     nums = {1,3,5,6}; target = 5;
//     std::cout << "Nums: [1,3,5,6], Target: 5, Expected: 2, Got: " << sol.searchInsert(nums, target) << std::endl;

//     // Test Case 2: Target not found, insert in middle
//     nums = {1,3,5,6}; target = 2;
//     std::cout << "Nums: [1,3,5,6], Target: 2, Expected: 1, Got: " << sol.searchInsert(nums, target) << std::endl;

//     // Test Case 3: Target not found, insert at end
//     nums = {1,3,5,6}; target = 7;
//     std::cout << "Nums: [1,3,5,6], Target: 7, Expected: 4, Got: " << sol.searchInsert(nums, target) << std::endl;

//     // Test Case 4: Target not found, insert at beginning
//     nums = {1,3,5,6}; target = 0;
//     std::cout << "Nums: [1,3,5,6], Target: 0, Expected: 0, Got: " << sol.searchInsert(nums, target) << std::endl;

//     // Test Case 5: Single element, target smaller
//     nums = {1}; target = 0;
//     std::cout << "Nums: [1], Target: 0, Expected: 0, Got: " << sol.searchInsert(nums, target) << std::endl;

//     // Test Case 6: Single element, target larger
//     nums = {1}; target = 2;
//     std::cout << "Nums: [1], Target: 2, Expected: 1, Got: " << sol.searchInsert(nums, target) << std::endl;

//     // Test Case 7: Single element, target found
//     nums = {1}; target = 1;
//     std::cout << "Nums: [1], Target: 1, Expected: 0, Got: " << sol.searchInsert(nums, target) << std::endl;

//     // Test Case 8: Empty array
//     nums = {}; target = 5;
//     std::cout << "Nums: [], Target: 5, Expected: 0, Got: " << sol.searchInsert(nums, target) << std::endl;

//     // Test Case 9: Multiple occurrences, should find first valid insertion for non-existent target
//     nums = {1,3,3,3,5,6}; target = 4;
//     std::cout << "Nums: [1,3,3,3,5,6], Target: 4, Expected: 4, Got: " << sol.searchInsert(nums, target) << std::endl;

//     // Test Case 10: Target is one of multiple occurrences
//     nums = {1,3,3,3,5,6}; target = 3;
//     std::cout << "Nums: [1,3,3,3,5,6], Target: 3, Expected: 1, Got: " << sol.searchInsert(nums, target) << std::endl;

//     return 0;
// }