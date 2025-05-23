#include <vector>
#include <unordered_set>
#include <algorithm> // For std::max
#include <iostream>  // For main example

/*
Problem: Longest Consecutive Sequence (LeetCode 128)
Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.
You must write an algorithm that runs in O(n) time.

Example: nums = [100, 4, 200, 1, 3, 2]
Output: 4 (The longest consecutive sequence is [1, 2, 3, 4])

Concept (Using Hash Set to Identify Sequence Starts):
The core idea is to efficiently check for the existence of numbers to build consecutive sequences
while ensuring O(n) overall time complexity. This is achieved by:
1. Storing all unique numbers from the input array into an `std::unordered_set`. This allows for
   O(1) average time complexity for checking the presence of a number (lookups).
2. Iterating through the unique numbers. For each number `x`:
   a. Crucially, check if `x-1` is present in the set.
   b. If `x-1` is NOT present, it means `x` is the true starting point of a new consecutive sequence.
      This check is vital to ensure that we only attempt to build a sequence from its actual beginning,
      preventing redundant work. For example, if we have {1, 2, 3}, we only start building from 1, not from 2 or 3.
   c. If `x` is a starting point, then count upwards (`x+1`, `x+2`, ...) by checking their presence
      in the set, and determine the length of this sequence.
3. The maximum length found among all such identified sequences is the answer.

How the New Code Works (Hash Set Approach):

1. Initialization and Population of Set:
   - `std::unordered_set<int> sett(nums.begin(), nums.end());`
     This line creates an `unordered_set` named `sett` and initializes it directly with all elements
     from the input `nums` vector. The `unordered_set` automatically handles duplicates, so `sett`
     will only contain the unique numbers from `nums`.
   - `int max_len = 0;` (or `maxi` as in the code)
     A variable is initialized to store the maximum length found so far.

2. Iterating Through Unique Numbers:
   - `for (int num : sett)`:
     The code iterates through each unique number `num` present in the `sett`.

3. Identifying the Start of a Sequence:
   - `if (sett.find(num - 1) == sett.end())`:
     For each `num`, this condition checks if the element `num - 1` exists in the `sett`.
     `sett.find(value)` returns an iterator to the element if found, or `sett.end()` if not found.
     So, `sett.find(num - 1) == sett.end()` is true if `num - 1` is NOT in the set.
     This means `num` is the starting element of a new consecutive sequence.

4. Counting the Length of the Current Sequence:
   - If `num` is a start:
     - `int current_len = 1;` (or `length = 1;`)
       The length of the current sequence is initialized to 1 (to account for `num` itself).
     - `while (sett.find(num + current_len) != sett.end())`:
       A `while` loop is used to find subsequent consecutive numbers.
       It checks if `num + current_len` (i.e., `num+1` in the first iteration of the while loop,
       then `num+2`, and so on) is present in the `sett`.
       As long as the next consecutive number is found in the set, `current_len` is incremented.

5. Updating Maximum Length:
   - `max_len = std::max(max_len, current_len);`
     After the `while` loop finishes (meaning the sequence starting at `num` has ended),
     the `max_len` is updated to be the maximum of its current value and `current_len`.

6. Return Result:
   - `return max_len;`
     After iterating through all unique numbers in `sett` and performing the checks and counts,
     `max_len` will hold the length of the longest consecutive sequence found.

Visual Example: nums = [100, 4, 200, 1, 3, 2]

1. Initialization:
   - `sett = {100, 4, 200, 1, 3, 2}` (order in set doesn't matter for logic)
   - `max_len = 0`

2. Iteration through `sett` (example order):
   - `num = 100`:
     - `sett.find(99) == sett.end()`? Yes (99 not in set). So, 100 is a start.
     - `current_len = 1`.
     - `while(sett.find(100 + 1) != sett.end())`? No (101 not in set). Loop doesn't run.
     - `max_len = std::max(0, 1) = 1`.
   - `num = 4`:
     - `sett.find(3) == sett.end()`? No (3 is in set). Skip building sequence from 4.
   - `num = 200`:
     - `sett.find(199) == sett.end()`? Yes. 200 is a start.
     - `current_len = 1`.
     - `while(sett.find(200 + 1) != sett.end())`? No.
     - `max_len = std::max(1, 1) = 1`.
   - `num = 1`:
     - `sett.find(0) == sett.end()`? Yes. 1 is a start.
     - `current_len = 1`.
     - `while(sett.find(1 + 1) != sett.end())`? (Check for 2) Yes. `current_len = 2`.
     - `while(sett.find(1 + 2) != sett.end())`? (Check for 3) Yes. `current_len = 3`.
     - `while(sett.find(1 + 3) != sett.end())`? (Check for 4) Yes. `current_len = 4`.
     - `while(sett.find(1 + 4) != sett.end())`? (Check for 5) No.
     - `max_len = std::max(1, 4) = 4`.
   - `num = 3`:
     - `sett.find(2) == sett.end()`? No (2 is in set). Skip.
   - `num = 2`:
     - `sett.find(1) == sett.end()`? No (1 is in set). Skip.

3. Return `max_len = 4`.

Algorithm Properties:

1. Time Complexity: O(N) on average
   - Populating the `std::unordered_set` takes O(N) time on average, where N is the number of elements in `nums`.
   - The outer `for` loop iterates up to N times (for unique elements).
   - The crucial part is the `if (sett.find(num - 1) == sett.end())` check. This ensures that the inner `while` loop
     (which counts the sequence length) is executed only for the starting numbers of consecutive sequences.
   - Although there's a `while` loop inside a `for` loop, each number is visited at most twice:
     once by the outer loop and once by the inner `while` loop (if it's part of a sequence being counted).
     For example, if we have 1, 2, 3, 4, 5: `num=1` starts the while loop which runs 4 times for 2,3,4,5.
     When `num` is 2, 3, 4, or 5, the `if` condition `sett.find(num - 1) == sett.end()` is false, so the while loop is skipped.
     Thus, the total number of operations is proportional to N.

2. Space Complexity: O(N)
   - The `std::unordered_set` `sett` stores up to N unique numbers from the input array in the worst case
     (if all numbers in `nums` are unique).

Edge Cases:
- Empty `nums` array (`[]`):
  - `sett` will be empty.
  - The `for` loop won't execute.
  - `max_len` remains 0. Returns 0 (correct).
- `nums` with one element (e.g., `[10]`):
  - `sett = {10}`.
  - Loop for `num = 10`: `sett.find(9)` is end. `current_len = 1`. `max_len = 1`. Returns 1 (correct).
- `nums` with duplicates (e.g., `[1,2,2,3]`):
  - `sett = {1, 2, 3}`. Duplicates are handled by the set.
  - Logic proceeds as with unique elements, resulting in length 3 for `[1,2,3]`.
- All numbers consecutive (e.g., `[1,2,3,4]`):
  - `sett = {1,2,3,4}`.
  - Only for `num = 1` will the `if` condition be true. The `while` loop counts up to 4. `max_len = 4`.
- No consecutive numbers (e.g., `[10,20,30]`):
  - For each number, `num-1` will not be in the set. Each sequence length will be 1. `max_len = 1`.

Why this Hash Set Approach is Efficient and Preferred:
- O(1) Average Lookups: `std::unordered_set` provides fast average-case time complexity for `find` operations.
- Avoids Redundant Work: The check `if (sett.find(num - 1) == sett.end())` is key. It ensures that we only start building and counting a sequence from its absolute smallest element. This prevents re-processing parts of sequences multiple times, which is essential for achieving the O(N) time complexity.
- Simplicity: The logic is relatively straightforward to understand and implement compared to approaches that might require more complex data structures or multiple explicit passes for marking elements.
*/

class Solution {
public:
    int longestConsecutive(std::vector<int>& nums) {
        // Create an unordered_set from the input vector to store unique elements
        // and allow for O(1) average time lookups.
        std::unordered_set<int> sett(nums.begin(), nums.end());
        int max_len = 0; // Variable to store the maximum length found

        // Iterate over each unique number in the set
        for (int num : sett) {
            // Check if the current number `num` is the start of a sequence.
            // A number is a start if `num - 1` is NOT present in the set.
            if (sett.find(num - 1) == sett.end()) {
                int current_len = 1;

                // If it's a start, count the length of the consecutive sequence
                while (sett.find(num + current_len) != sett.end()) {
                    current_len++;
                }
                // Update the maximum length found so far
                max_len = std::max(max_len, current_len);
            }
        }
        return max_len;
    }
};

// int main() {
//     Solution sol;
//     std::vector<int> nums1 = {100, 4, 200, 1, 3, 2};
//     std::cout << "Nums: [100, 4, 200, 1, 3, 2], Longest: " << sol.longestConsecutive(nums1) << std::endl; // Expected: 4

//     std::vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
//     std::cout << "Nums: [0, 3, 7, 2, 5, 8, 4, 6, 0, 1], Longest: " << sol.longestConsecutive(nums2) << std::endl; // Expected: 9

//     std::vector<int> nums3 = {};
//     std::cout << "Nums: [], Longest: " << sol.longestConsecutive(nums3) << std::endl; // Expected: 0

//     std::vector<int> nums4 = {5};
//     std::cout << "Nums: [5], Longest: " << sol.longestConsecutive(nums4) << std::endl; // Expected: 1

//     std::vector<int> nums5 = {1, 2, 0, 1};
//     std::cout << "Nums: [1,2,0,1], Longest: " << sol.longestConsecutive(nums5) << std::endl; // Expected: 3 ([0,1,2])
    
//     std::vector<int> nums6 = {9,1,4,7,3,-1,0,5,8,-1,6};
//     std::cout << "Nums: [9,1,4,7,3,-1,0,5,8,-1,6], Longest: " << sol.longestConsecutive(nums6) << std::endl; // Expected: 7 (sequence is 3,4,5,6,7,8,9)

//     std::vector<int> nums7 = {1,1,1,1};
//     std::cout << "Nums: [1,1,1,1], Longest: " << sol.longestConsecutive(nums7) << std::endl; // Expected: 1

//     return 0;
// }