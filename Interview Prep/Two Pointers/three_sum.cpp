class Solution {
public:
    // Two Pointers Approach with Sorting
    // Time Complexity: O(n²) where n is the length of arr
    // Space Complexity: O(1) excluding the result array
    vector<vector<int>> threeSum(vector<int>& arr) {
        /*
        Simple Rules to Remember:
        1. Sort array first
        2. Use three pointers: i, j, k
        3. i is fixed for each iteration
        4. j and k move towards each other
        5. Skip duplicates to avoid same triplets
        6. Sum should be zero

        Visual Example:
        arr = [-1, 0, 1, 2, -1, -4]

        After sorting: [-4, -1, -1, 0, 1, 2]

        Step 1: i = 0 (arr[i] = -4)
               j = 1, k = 5
               sum = -4 + (-1) + 2 = -3 < 0
               j++

               j = 2, k = 5
               sum = -4 + (-1) + 2 = -3 < 0
               j++

               j = 3, k = 5
               sum = -4 + 0 + 2 = -2 < 0
               j++

               j = 4, k = 5
               sum = -4 + 1 + 2 = -1 < 0
               j++

        Step 2: i = 1 (arr[i] = -1)
               j = 2, k = 5
               sum = -1 + (-1) + 2 = 0
               Found triplet: [-1, -1, 2]
               j++, k--

               j = 3, k = 4
               sum = -1 + 0 + 1 = 0
               Found triplet: [-1, 0, 1]
               j++, k--

        Step 3: i = 2 (arr[i] = -1)
               Skip as it's same as previous i

        Step 4: i = 3 (arr[i] = 0)
               j = 4, k = 5
               sum = 0 + 1 + 2 = 3 > 0
               k--

        Final result: [[-1, -1, 2], [-1, 0, 1]]
        */

        vector<vector<int>> ans;
        int n = arr.size();

        // Sort array to use two pointers approach
        sort(arr.begin(), arr.end());

        // Fix first element and find other two
        for (int i = 0; i < n; i++) {
            // Skip duplicates for i
            if (i != 0 && arr[i] == arr[i - 1]) continue;

            // Initialize two pointers
            int j = i + 1;  // Left pointer
            int k = n - 1;  // Right pointer

            // Find pairs that sum to -arr[i]
            while (j < k) {
                int sum = arr[i] + arr[j] + arr[k];

                if (sum < 0) {
                    // Sum is too small, move left pointer
                    j++;
                }
                else if (sum > 0) {
                    // Sum is too large, move right pointer
                    k--;
                }
                else {
                    // Found a valid triplet
                    vector<int> temp = {arr[i], arr[j], arr[k]};
                    ans.push_back(temp);

                    // Move both pointers
                    j++;
                    k--;

                    // Skip duplicates for j
                    while (j < k && arr[j] == arr[j - 1]) j++;
                    // Skip duplicates for k
                    while (j < k && arr[k] == arr[k + 1]) k--;
                }
            }
        }

        return ans;
    }

    // Alternative Solution: Hash Set Approach
    // Time Complexity: O(n²) where n is the length of arr
    // Space Complexity: O(n) for the hash set
    vector<vector<int>> threeSumHashSet(vector<int>& arr) {
        /*
        Simple Rules to Remember:
        1. Sort array first
        2. Use hash set to store seen numbers
        3. For each pair (i,j), look for -(arr[i] + arr[j]) in set
        4. Skip duplicates to avoid same triplets
        5. Sum should be zero

        Visual Example:
        arr = [-1, 0, 1, 2, -1, -4]

        After sorting: [-4, -1, -1, 0, 1, 2]

        Step 1: i = 0 (arr[i] = -4)
               j = 1, target = 5
               Set: {}
               Not found, add -1 to set

               j = 2, target = 5
               Set: {-1}
               Not found, add -1 to set

               j = 3, target = 4
               Set: {-1}
               Not found, add 0 to set

        Step 2: i = 1 (arr[i] = -1)
               j = 2, target = 2
               Set: {-1, 0}
               Not found, add -1 to set

               j = 3, target = 1
               Set: {-1, 0}
               Not found, add 0 to set

               j = 4, target = 0
               Set: {-1, 0}
               Found! Add [-1, 0, 1] to result

        Final result: [[-1, 0, 1], [-1, -1, 2]]
        */

        vector<vector<int>> ans;
        int n = arr.size();
        
        // Sort array to handle duplicates
        sort(arr.begin(), arr.end());

        for (int i = 0; i < n; i++) {
            // Skip duplicates for i
            if (i != 0 && arr[i] == arr[i - 1]) continue;

            // Hash set to store seen numbers
            unordered_set<int> seen;

            for (int j = i + 1; j < n; j++) {
                // Skip duplicates for j
                if (j > i + 1 && arr[j] == arr[j - 1]) continue;

                int target = -(arr[i] + arr[j]);

                // If target found in set, we have a valid triplet
                if (seen.count(target)) {
                    ans.push_back({arr[i], target, arr[j]});
                }

                // Add current number to set
                seen.insert(arr[j]);
            }
        }

        return ans;
    }
};

/*
Simple Memory Aid:

1. Key Variables:
   - i: First pointer (fixed for each iteration)
   - j: Left pointer (moves right)
   - k: Right pointer (moves left)
   - sum: Current sum of three numbers

2. Key Steps:
   a. Sort array
   b. For each i:
      - Skip if duplicate
      - Initialize j and k
      - While j < k:
        * Calculate sum
        * Move pointers based on sum
        * Handle duplicates
   c. Return result

3. Visual Process:
   For arr = [-1, 0, 1, 2, -1, -4]:

   Sorted: [-4, -1, -1, 0, 1, 2]
   i=0:    [-4, -1, -1, 0, 1, 2]
           i   j            k
   i=1:    [-4, -1, -1, 0, 1, 2]
              i  j         k
   i=2:    [-4, -1, -1, 0, 1, 2]
                 i  j      k

4. Common Pitfalls:
   - Not handling duplicates
   - Wrong pointer movement
   - Not sorting array
   - Not considering all cases
   - Wrong sum comparison
   - Not handling edge cases

5. Time Complexity: O(n²)
   - n: length of array
   - Sorting: O(n log n)
   - Two pointers: O(n)
   - Total: O(n log n + n²) = O(n²)

6. Space Complexity: O(1)
   - In-place sorting
   - Only pointers used
   - Excluding result array
   - Constant extra space

7. Key Properties:
   - Array must be sorted
   - Three pointers needed
   - Skip duplicates
   - Sum should be zero
   - j and k move towards each other
   - i is fixed for each iteration

8. Why Two Pointers Work:
   - Array is sorted
   - Can move pointers based on sum
   - Efficient search for pairs
   - No need to check all combinations
   - Handles duplicates correctly
   - Optimal time complexity

9. Alternative Approaches:
   - Using hash set
   - Using hash map
   - Brute force (O(n³))
   - Using binary search
   - Using two sum approach
*/