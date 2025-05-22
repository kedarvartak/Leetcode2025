class Solution {
public:
    // Greedy Approach - Working Backwards
    // Time Complexity: O(n), where n is the number of elements in nums
    // Space Complexity: O(1)
    bool canJump(vector<int>& nums) {
        /*
        Problem: Determine if you can reach the last index starting from the first index.
                 Each element nums[i] represents the maximum jump length from that position.

        Simple Rules to Remember:
        1. Start from the second to last element and move backwards.
        2. Maintain a 'goal' post, initially the last index.
        3. If the current position 'i' plus its jump length 'nums[i]' can reach or exceed the 'goal',
           then this current position 'i' becomes the new 'goal'.
        4. If the 'goal' eventually reaches index 0, it means the start can reach the end.

        Visual Example:
        nums = [2, 3, 1, 1, 4]
        n = 5
        goal = n - 1 = 4 (last index)

        Iteration 1: i = n - 2 = 3
            nums[3] = 1
            Can we reach 'goal' (4) from index 3?  (3 + nums[3] >= goal) => (3 + 1 >= 4) => (4 >= 4) -> True
            Update goal = i = 3

        Iteration 2: i = 2
            nums[2] = 1
            Can we reach 'goal' (3) from index 2?  (2 + nums[2] >= goal) => (2 + 1 >= 3) => (3 >= 3) -> True
            Update goal = i = 2

        Iteration 3: i = 1
            nums[1] = 3
            Can we reach 'goal' (2) from index 1?  (1 + nums[1] >= goal) => (1 + 3 >= 2) => (4 >= 2) -> True
            Update goal = i = 1

        Iteration 4: i = 0
            nums[0] = 2
            Can we reach 'goal' (1) from index 0?  (0 + nums[0] >= goal) => (0 + 2 >= 1) => (2 >= 1) -> True
            Update goal = i = 0

        Loop finishes.
        Is goal == 0? Yes.
        Return true.

        Another Example: nums = [3, 2, 1, 0, 4]
        n = 5
        goal = 4

        i = 3: nums[3] = 0. (3 + 0 >= 4) -> False. goal remains 4.
        i = 2: nums[2] = 1. (2 + 1 >= 4) -> False. goal remains 4.
        i = 1: nums[1] = 2. (1 + 2 >= 4) -> False. goal remains 4.
        i = 0: nums[0] = 3. (0 + 3 >= 4) -> False. goal remains 4.

        Loop finishes.
        Is goal == 0? No, goal is 4.
        Return false.
        */

        int n = nums.size();
        if (n == 0) return false; // Or true if an empty array means you're already there (problem dependent)
        if (n == 1) return true;  // If only one element, you are already at the last index

        int goal = n - 1; // The target index we want to reach (initially the last index)

        // Iterate backwards from the second to last element
        for (int i = n - 2; i >= 0; i--) {
            // If the current index 'i' plus its maximum jump length 'nums[i]'
            // can reach or surpass the current 'goal' position...
            if (i + nums[i] >= goal) {
                // ...then this current index 'i' becomes our new, closer 'goal'.
                // This means if we can reach 'i', we can definitely reach the original 'goal'.
                goal = i;
            }
        }

        // If after checking all positions, our 'goal' has become index 0,
        // it means we can jump from the start (index 0) to a position
        // from which the original last index is reachable.
        return goal == 0;
    }
};

/*
Key Steps:
1. Initialize 'goal' to the last index of the array.
2. Iterate from the second to last element (n-2) down to the first element (0).
3. In each iteration, check if the current index `i` plus the jump value `nums[i]` can reach or exceed the current `goal`.
4. If it can, update `goal` to `i` because this `i` is now a good stepping stone to the ultimate end.
5. After the loop, if `goal` is 0, it means the starting position can reach the end. Otherwise, it cannot.

Why this Greedy Approach Works:
- We are essentially asking: "From which position can I reach the current 'goal'?"
- By moving the 'goal' backward whenever a reachable position is found, we ensure that if the 'goal' becomes 0, there's a path.
- If `goal` is `j`, it means we have confirmed that index `j` can reach the actual last index.
- Now, if we find an index `i` that can reach `j`, then `i` becomes the new `goal`, signifying that `i` can also reach the actual last index (via `j`).

Common Pitfalls:
- Off-by-one errors in loop bounds or goal initialization.
- Misunderstanding the condition `i + nums[i] >= goal`.
- Iterating forwards can be more complex to implement greedily for this specific problem without keeping track of max reach.

Alternative Approaches:
1. Dynamic Programming:
   - dp[i] = true if index i can reach the end.
   - dp[n-1] = true.
   - Iterate i from n-2 down to 0. dp[i] is true if for any j from i+1 to i+nums[i], dp[j] is true.
   - Time: O(n*k) in worst case if jumps are small, or O(n^2). Can optimize to O(n).
   - Space: O(n) for dp array.

2. Forward Greedy (Max Reach):
   - Keep track of the maximum index reachable so far (`max_reach`).
   - Iterate from left to right. `max_reach = max(max_reach, i + nums[i])`.
   - If `i > max_reach` at any point, you're stuck.
   - If `max_reach >= n-1`, return true.
   - Time: O(n), Space: O(1).
   - (The provided solution is a backward greedy approach, which is often simpler to reason about for this problem).
*/