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
    // Optimized Approach using Binary Search
    // Time Complexity: O(log²n) where n is number of nodes
    // Space Complexity: O(1) as we only use pointers
    int countNodes(TreeNode* root) {
        /*
        Simple Rules to Remember:
        1. In a complete binary tree:
           - All levels are filled except possibly the last
           - Last level is filled from left to right
        2. If left height equals right height:
           - Tree is perfect (2^h - 1 nodes)
        3. If heights differ:
           - Recursively count left and right subtrees
           - Add 1 for current node

        Visual Example:
        Complete Tree:
              1
             / \
            2   3
           / \  /
          4   5 6

        Height of left subtree = 2
        Height of right subtree = 1
        Total nodes = 6
        */

        if (!root) return 0;

        // Get left and right heights
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);

        // If heights are equal, tree is perfect
        if (leftHeight == rightHeight) {
            // For perfect tree: nodes = 2^h - 1
            // Add 1 for current node
            return (1 << leftHeight) - 1 + 1;
        }

        // If heights differ, recursively count
        return 1 + countNodes(root->left) + countNodes(root->right);
    }

private:
    // Get height of tree by going left
    // In complete tree, left path is always the longest
    int getHeight(TreeNode* root) {
        int height = 0;
        while (root) {
            height++;
            root = root->left;
        }
        return height;
    }
};

/*
Simple Memory Aid:

1. Complete Binary Tree Properties:
   - All levels filled except possibly last
   - Last level filled left to right
   - Left subtree always complete
   - Right subtree might be complete

2. Key Steps:
   a. Get left height
   b. Get right height
   c. If equal: use formula 2^h - 1 + 1
   d. If different: recurse on subtrees

3. Visual Process:
   For tree:
         1
        / \
       2   3
      / \  /
     4   5 6

   Step 1: Check heights
           leftHeight = 2
           rightHeight = 1
           Heights differ, so recurse

   Step 2: Count left subtree (perfect)
           2^2 - 1 + 1 = 4 nodes

   Step 3: Count right subtree
           1 + 1 = 2 nodes

   Step 4: Total = 1 + 4 + 2 = 7 nodes

4. Common Pitfalls:
   - Not handling NULL case
   - Incorrect height calculation
   - Wrong formula for perfect tree
   - Not adding current node

5. Time Complexity: O(log²n)
   - Height calculation: O(log n)
   - Recursive calls: O(log n)
   - Total: O(log n * log n)

6. Space Complexity: O(1)
   - Only uses pointers
   - No extra space needed
   - Recursion stack is O(log n)

7. Alternative Approaches:
   - Simple recursion: O(n) time
   - Binary search: O(log²n) time
   - But this approach is most efficient
*/ 