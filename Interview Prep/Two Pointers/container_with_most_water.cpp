class Solution {
public:
    // Speed optimization for I/O
    int speed = [] () {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        return 0;
    } ();

    // Two Pointers Approach
    // Time Complexity: O(n) where n is the length of height array
    // Space Complexity: O(1) as we only use two pointers
    int maxArea(vector<int>& height) {
        /*
        Simple Rules to Remember:
        1. Use two pointers: left and right
        2. Area = min(height[left], height[right]) * (right - left)
        3. Move pointer with smaller height
        4. Keep track of maximum area
        5. Stop when pointers meet
        6. Width decreases as pointers move

        Visual Example:
        height = [1, 8, 6, 2, 5, 4, 8, 3, 7]

        Step 1: left = 0, right = 8
               height[left] = 1, height[right] = 7
               currArea = min(1, 7) * (8 - 0) = 1 * 8 = 8
               maxArea = 8
               Move left (1 < 7)

        Step 2: left = 1, right = 8
               height[left] = 8, height[right] = 7
               currArea = min(8, 7) * (8 - 1) = 7 * 7 = 49
               maxArea = 49
               Move right (8 > 7)

        Step 3: left = 1, right = 7
               height[left] = 8, height[right] = 3
               currArea = min(8, 3) * (7 - 1) = 3 * 6 = 18
               maxArea = 49
               Move right (8 > 3)

        Step 4: left = 1, right = 6
               height[left] = 8, height[right] = 8
               currArea = min(8, 8) * (6 - 1) = 8 * 5 = 40
               maxArea = 49
               Move left (8 == 8)

        Step 5: left = 2, right = 6
               height[left] = 6, height[right] = 8
               currArea = min(6, 8) * (6 - 2) = 6 * 4 = 24
               maxArea = 49
               Move left (6 < 8)

        Final result: 49 (left = 1, right = 8)
        */

        // Initialize pointers and maxArea
        int left = 0;
        int right = height.size() - 1;
        int maxArea = 0;

        // Move pointers until they meet
        while (left < right) {
            // Calculate current area
            int currArea = min(height[left], height[right]) * (right - left);
            maxArea = max(maxArea, currArea);

            // Move pointer with smaller height
            if (height[left] < height[right]) {
                left++;
            }
            else {
                right--;
            }
        }

        return maxArea;
    }
};

/*
Simple Memory Aid:

1. Key Variables:
   - left: Left pointer
   - right: Right pointer
   - maxArea: Maximum area found
   - currArea: Current area being calculated

2. Key Steps:
   a. Initialize pointers at both ends
   b. While left < right:
      - Calculate current area
      - Update maxArea if needed
      - Move pointer with smaller height
   c. Return maxArea

3. Visual Process:
   For height = [1, 8, 6, 2, 5, 4, 8, 3, 7]:

   Step 1: [1, 8, 6, 2, 5, 4, 8, 3, 7]
           L                         R
           Area = 8

   Step 2: [1, 8, 6, 2, 5, 4, 8, 3, 7]
              L                     R
           Area = 49

   Step 3: [1, 8, 6, 2, 5, 4, 8, 3, 7]
              L                  R
           Area = 49

   Step 4: [1, 8, 6, 2, 5, 4, 8, 3, 7]
              L               R
           Area = 49

   Step 5: [1, 8, 6, 2, 5, 4, 8, 3, 7]
                 L            R
           Area = 49

4. Common Pitfalls:
   - Not handling empty array
   - Wrong pointer movement logic
   - Not considering equal heights
   - Not updating maxArea correctly
   - Not understanding area calculation
   - Not considering width decrease

5. Time Complexity: O(n)
   - n: length of height array
   - Each pointer moves at most n times
   - Constant time operations
   - No nested loops

6. Space Complexity: O(1)
   - Only two pointers used
   - No extra data structures
   - Constant space regardless of input size

7. Key Properties:
   - Two pointer technique
   - Area = min(height) * width
   - Width decreases as pointers move
   - Move smaller height pointer
   - Greedy approach works
   - No need to check all pairs

8. Why Two Pointers Work:
   - Moving smaller height pointer is optimal
   - Width decreases as pointers move
   - No need to check all possible pairs
   - Greedy approach is correct
   - Single pass solution
   - Efficient space usage

9. Alternative Approaches:
   - Brute force (O(n²))
   - Dynamic programming
   - Using stack
   - Using monotonic stack
   - Using binary search
*/