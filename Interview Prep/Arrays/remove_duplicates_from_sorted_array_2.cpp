class Solution {
public:
    // Two Pointers Approach
    // Time Complexity: O(n) where n is the length of nums array
    // Space Complexity: O(1) as we modify array in-place
    int removeDuplicates(vector<int>& nums) {
        /*
        Simple Rules to Remember:
        1. Array is sorted in non-decreasing order
        2. Allow at most 2 occurrences of each element
        3. Modify array in-place
        4. Return new length of array
        5. Elements beyond new length don't matter
        6. Use two pointers: one for writing, one for reading

        Visual Example:
        nums = [1, 1, 1, 2, 2, 3]

        Step 1: Initialize
               write = 2 (start after first two elements)
               read = 2 (start from third element)
               nums = [1, 1, 1, 2, 2, 3]

        Step 2: read = 2
               nums[read] = 1
               nums[read] == nums[write-2] (1 == 1)
               Skip this element
               nums = [1, 1, 1, 2, 2, 3]

        Step 3: read = 3
               nums[read] = 2
               nums[read] != nums[write-2] (2 != 1)
               Copy 2 to write position
               write++
               nums = [1, 1, 2, 2, 2, 3]

        Step 4: read = 4
               nums[read] = 2
               nums[read] != nums[write-2] (2 != 1)
               Copy 2 to write position
               write++
               nums = [1, 1, 2, 2, 2, 3]

        Step 5: read = 5
               nums[read] = 3
               nums[read] != nums[write-2] (3 != 2)
               Copy 3 to write position
               write++
               nums = [1, 1, 2, 2, 3, 3]

        Final result: 5 (nums = [1, 1, 2, 2, 3, _])
        */

        // Handle edge cases
        if (nums.size() <= 2) return nums.size();

        // Initialize write pointer after first two elements
        int write = 2;

        // Iterate through array starting from third element
        for (int read = 2; read < nums.size(); read++) {
            // If current element is different from element two positions back
            // (allowing at most 2 occurrences)
            if (nums[read] != nums[write - 2]) {
                // Copy current element to write position
                nums[write] = nums[read];
                write++;
            }
        }

        return write;
    }
};

/*
Simple Memory Aid:

1. Key Variables:
   - write: Position to write next valid element
   - read: Position to read next element
   - nums[write-2]: Element two positions back from write

2. Key Steps:
   a. Start write pointer after first two elements
   b. For each element (starting from third):
      - If element != nums[write-2]:
        * Copy element to write position
        * Increment write
      - If element == nums[write-2]:
        * Skip element (more than 2 occurrences)
   c. Return write (new length)

3. Visual Process:
   For nums = [1, 1, 1, 2, 2, 3]:

   Initial:  [1, 1, 1, 2, 2, 3]
   Step 1:   [1, 1, 1, 2, 2, 3]  (write=2, read=2)
   Step 2:   [1, 1, 1, 2, 2, 3]  (write=2, read=3)
   Step 3:   [1, 1, 2, 2, 2, 3]  (write=3, read=4)
   Step 4:   [1, 1, 2, 2, 2, 3]  (write=4, read=5)
   Final:    [1, 1, 2, 2, 3, 3]  (write=5)

4. Common Pitfalls:
   - Not handling edge cases
   - Wrong pointer initialization
   - Incorrect comparison logic
   - Not understanding in-place modification
   - Not considering array bounds
   - Wrong return value

5. Time Complexity: O(n)
   - n: length of nums array
   - Single pass through array
   - Constant time operations
   - No nested loops

6. Space Complexity: O(1)
   - In-place modification
   - Only two variables used
   - No extra data structures
   - Constant space regardless of input size

7. Key Properties:
   - Array is sorted
   - At most 2 occurrences allowed
   - In-place modification
   - Two pointer technique
   - Write pointer tracks valid elements
   - Read pointer scans array

8. Alternative Approaches:
   - Using extra array
   - Counting occurrences
   - Using hash map
   - Using set
   - Using vector erase

9. Why Two Pointers Work:
   - Array is sorted
   - We only need to look back 2 positions
   - No need to track all occurrences
   - Can modify array in-place
   - Efficient space usage
   - Single pass solution
*/
