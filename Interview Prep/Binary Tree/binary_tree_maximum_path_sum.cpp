/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // Recursive DFS Approach
    // Time Complexity: O(n) where n is number of nodes
    // Space Complexity: O(h) where h is height of tree (recursion stack)
    int helper(TreeNode* root, int& ans) {
        /*
        Simple Rules to Remember:
        1. For each node, we can:
           - Include it in a path going up to its parent
           - Use it as a root of a path going through it
        2. For path going up:
           - Can only choose one child (left or right)
           - Must be positive to be included
        3. For path through node:
           - Can include both children
           - Must be positive to be included
        4. Keep track of maximum path sum seen so far

        Visual Example:
        Tree:
              -10
             /   \
            9     20
                 /  \
                15   7

        Path through -10: 15 + 20 + (-10) = 25
        Path through 20: 15 + 20 + 7 = 42
        Maximum path sum = 42
        */

        // Base case: empty tree
        if (root == NULL) return 0;

        // Get maximum path sum from left and right subtrees
        // If negative, we don't include that path (use 0 instead)
        int leftSum = max(0, helper(root->left, ans));
        int rightSum = max(0, helper(root->right, ans));

        // Update maximum path sum if path through current node is better
        // Path through current node = left + right + current
        ans = max(ans, leftSum + rightSum + root->val);

        // Return maximum path sum going up to parent
        // Can only choose one child (left or right)
        return root->val + max(leftSum, rightSum);
    }

    int maxPathSum(TreeNode* root) {
        // Initialize answer with minimum possible value
        int ans = INT_MIN;
        helper(root, ans);
        return ans;
    }
};

/*
Simple Memory Aid:

1. For Each Node:
   a. Path going up to parent:
      - Can only choose one child
      - Must be positive
      - Return: node + max(left, right)
   
   b. Path through current node:
      - Can use both children
      - Must be positive
      - Update ans: left + right + node

2. Key Steps:
   a. Get left and right sums
   b. Take maximum with 0 (ignore negative paths)
   c. Update global maximum
   d. Return path going up

3. Visual Process:
   For tree:
          -10
         /   \
        9     20
             /  \
            15   7

   Step 1: Check node 15
           left = 0, right = 0
           ans = max(INT_MIN, 0 + 0 + 15) = 15
           return 15

   Step 2: Check node 7
           left = 0, right = 0
           ans = max(15, 0 + 0 + 7) = 15
           return 7

   Step 3: Check node 20
           left = 15, right = 7
           ans = max(15, 15 + 7 + 20) = 42
           return 20 + max(15, 7) = 35

   Step 4: Check node 9
           left = 0, right = 0
           ans = max(42, 0 + 0 + 9) = 42
           return 9

   Step 5: Check node -10
           left = 9, right = 35
           ans = max(42, 9 + 35 + (-10)) = 42
           return -10 + max(9, 35) = 25

4. Common Pitfalls:
   - Not handling negative values
   - Not considering paths through root
   - Not updating global maximum correctly
   - Not handling empty tree

5. Time Complexity: O(n)
   - Each node visited once
   - Constant work at each node
   - Linear time overall

6. Space Complexity: O(h)
   - h is height of tree
   - Due to recursion stack
   - Worst case: O(n) for skewed tree
   - Best case: O(log n) for balanced tree

7. Key Properties:
   - Path can start and end at any node
   - Path must be continuous
   - Can only go down to children
   - Can't go up to parent (except for return value)
   - Negative values are allowed
   - Must include at least one node
*/