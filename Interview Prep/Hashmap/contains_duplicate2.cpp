#include <vector>
#include <unordered_map>
#include <iostream> // For main example

/*
Problem: Contains Duplicate II (LeetCode 219)
Given an integer array `nums` and an integer `k`, return `true` if there are two distinct indices
`i` and `j` in the array such that `nums[i] == nums[j]` and `abs(i - j) <= k`.
Otherwise, return `false`.

Concept (Using Hash Map):
The core idea is to efficiently track the most recent index at which each number has been seen.
As we iterate through the array, if we encounter a number that we have seen before, we can
quickly check if the difference between the current index and its last seen index is within `k`.
An `unordered_map` (hash map) is ideal for this, mapping numbers to their last seen indices.

How it Works:
1. Initialize an empty `unordered_map<int, int> mp` to store `number -> last_seen_index`.
2. Iterate through the input array `nums` with index `i` from `0` to `nums.size() - 1`.
3. For each element `current_num = nums[i]`:
   a. Check if `current_num` already exists as a key in `mp`.
      - If it exists: This means we've seen this number before. Let `last_seen_index = mp[current_num]`.
        Calculate the difference `diff = i - last_seen_index`.
        If `diff <= k`, we have found two identical numbers within the distance `k`. Return `true`.
   b. Regardless of whether a duplicate satisfying the condition was found, update the map:
      Set `mp[current_num] = i`. This ensures that `mp` always stores the most recent index for `current_num`.
      This is important because if we find the same number again later, we need to compare with its closest prior occurrence.
4. If the loop completes without returning `true`, it means no such pair of duplicates was found. Return `false`.

Visual Example:
nums = [1, 2, 3, 1], k = 3
mp = {}

Iteration 1 (i=0, nums[0]=1):
  - `1` not in `mp`.
  - `mp[1] = 0`.  mp = { (1:0) }

Iteration 2 (i=1, nums[1]=2):
  - `2` not in `mp`.
  - `mp[2] = 1`.  mp = { (1:0), (2:1) }

Iteration 3 (i=2, nums[2]=3):
  - `3` not in `mp`.
  - `mp[3] = 2`.  mp = { (1:0), (2:1), (3:2) }

Iteration 4 (i=3, nums[3]=1):
  - `1` is in `mp`. `last_seen_index = mp[1] = 0`.
  - `diff = i - last_seen_index = 3 - 0 = 3`.
  - Is `diff <= k`?  (3 <= 3) -> True.
  - Return `true`.

Example 2: nums = [1, 0, 1, 1], k = 1
mp = {}

i=0, nums[0]=1: mp[1]=0. mp={(1:0)}
i=1, nums[1]=0: mp[0]=1. mp={(1:0), (0:1)}
i=2, nums[2]=1:
  - 1 in mp. last_seen_index = mp[1] = 0.
  - diff = 2 - 0 = 2.
  - (2 <= k=1) -> False.
  - Update mp[1]=2. mp={(1:2), (0:1)}
i=3, nums[3]=1:
  - 1 in mp. last_seen_index = mp[1] = 2.
  - diff = 3 - 2 = 1.
  - (1 <= k=1) -> True.
  - Return `true`.

Algorithm Properties:

1. Time Complexity: O(n)
   - Where `n` is the number of elements in `nums`.
   - We iterate through the array once.
   - `unordered_map` operations (find, insert, access) take O(1) on average.
   - In the worst case (many hash collisions), these operations could degrade to O(n),
     making the overall worst-case O(n^2), but this is rare with good hash functions.

2. Space Complexity: O(min(n, m)) or O(min(n, k+1))
   - Where `n` is the number of elements and `m` is the number of unique elements in `nums`.
   - In the worst case, if all elements are unique, the map could store up to `n` entries.
   - If the number of unique elements `m` is less than `n`, it stores `m` entries.
   - Another perspective: If using a sliding window approach with a set (see alternatives),
     the space is O(k) or O(min(n, k+1)) for the window. This hash map approach might store
     more if `k` is small but there are many unique numbers outside `k` distance that are processed
     before a relevant duplicate is found. However, for the purpose of *finding* a duplicate within
     distance `k`, a window of size `k+1` is key. The provided hash map solution stores all unique
     values encountered and their last index, so O(min(n,m)) is a direct measure of its map size.

Edge Cases:
- Empty array `nums`: Loop won't run, returns `false` (correct).
- `k = 0`: `abs(i - j) <= 0` means `i == j`. Since indices must be distinct, this should always be `false`
  unless problem interpretation differs. The code handles this correctly: `i - mp[val]` would be 0 only if it's the
  same element just processed which is not possible as mp[val] is the *previous* index. If `nums=[1,1], k=0`,
  i=0: mp[1]=0. i=1: mp.find(1) true, i - mp[1] = 1 - 0 = 1. 1 <= 0 is false. mp[1]=1. Returns false. Correct.
- Array with all unique elements: Returns `false` (correct).
- Array with all same elements (e.g., `[1,1,1,1], k=1`): Returns `true` on the second element (correct).

Why Hash Map is Efficient:
- Fast Lookups: Checking if an element has been seen before (`mp.find()`) is O(1) on average.
- Fast Updates/Insertions: Storing/updating the last seen index (`mp[val] = i`) is O(1) on average.
This avoids the need for nested loops or rescanning parts of the array repeatedly.

Alternative Approaches:

1. Brute Force:
   - Use two nested loops. The outer loop for `i`, the inner loop for `j` from `i+1`.
   - Check if `nums[i] == nums[j]` and `abs(i - j) <= k`.
   - Time Complexity: O(n*min(n,k)) or O(n^2) in the worst case if k is large.
   - Space Complexity: O(1).
   - Too slow for large inputs.

2. Sliding Window with a Set:
   - Maintain a sliding window of size `k` (or `k+1` elements).
   - Use a hash set to store elements within the current window.
   - Iterate through `nums`:
     - If `i > k`, remove `nums[i - k - 1]` from the set (element that slides out of the window).
     - Try to insert `nums[i]` into the set.
       - If insertion fails (element already in set), it means `nums[i]` is a duplicate within
         the window of size `k`. Return `true`.
       - Otherwise, add `nums[i]` to the set.
   - Time Complexity: O(n) (each element added/removed from set at most once, O(1) avg set ops).
   - Space Complexity: O(min(n, k+1)) or O(k) (to store elements in the window set).
   - This is often a very clean and efficient alternative and bounds space by `k`.
*/

class Solution {
public:
    bool containsNearbyDuplicate(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> mp; // Stores <number, last_seen_index>

        for (int i = 0; i < nums.size(); ++i) {
            int current_num = nums[i];

            // Check if the current number has been seen before
            if (mp.count(current_num)) { // .count() is preferred over .find() != .end() for just checking existence
                // If seen, check if the distance to the last occurrence is within k
                if (i - mp[current_num] <= k) {
                    return true; // Found a duplicate within the distance k
                }
            }
            
            // Update the last seen index of the current number
            // This is done regardless of whether a duplicate was found earlier,
            // to ensure we always have the most recent index for future comparisons.
            mp[current_num] = i;
        }

        // If the loop completes, no such duplicate pair was found
        return false;
    }
};

// int main() {
//     Solution sol;
//     std::vector<int> nums1 = {1, 2, 3, 1};
//     int k1 = 3;
//     std::cout << "Nums: [1,2,3,1], k=3. Has nearby duplicate: " << (sol.containsNearbyDuplicate(nums1, k1) ? "true" : "false") << std::endl; // Expected: true

//     std::vector<int> nums2 = {1, 0, 1, 1};
//     int k2 = 1;
//     std::cout << "Nums: [1,0,1,1], k=1. Has nearby duplicate: " << (sol.containsNearbyDuplicate(nums2, k2) ? "true" : "false") << std::endl; // Expected: true

//     std::vector<int> nums3 = {1, 2, 3, 1, 2, 3};
//     int k3 = 2;
//     std::cout << "Nums: [1,2,3,1,2,3], k=2. Has nearby duplicate: " << (sol.containsNearbyDuplicate(nums3, k3) ? "true" : "false") << std::endl; // Expected: false

//     std::vector<int> nums4 = {};
//     int k4 = 1;
//     std::cout << "Nums: [], k=1. Has nearby duplicate: " << (sol.containsNearbyDuplicate(nums4, k4) ? "true" : "false") << std::endl; // Expected: false

//     std::vector<int> nums5 = {1,1};
//     int k5 = 0;
//     std::cout << "Nums: [1,1], k=0. Has nearby duplicate: " << (sol.containsNearbyDuplicate(nums5, k5) ? "true" : "false") << std::endl; // Expected: false (distinct indices i,j -> abs(i-j) > 0)
    
//     std::vector<int> nums6 = {99,99};
//     int k6 = 2;
//     std::cout << "Nums: [99,99], k=2. Has nearby duplicate: " << (sol.containsNearbyDuplicate(nums6, k6) ? "true" : "false") << std::endl; // Expected: true

//     return 0;
// }