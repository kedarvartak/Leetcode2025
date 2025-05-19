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
    bool hasPathSum(TreeNode* root, int targetSum) {
        /*
        Simple Rules to Remember:
        1. If node is NULL, return false (no path exists)
        2. If node is leaf (no children):
           - Check if remaining sum equals node's value
        3. For non-leaf nodes:
           - Subtract current node's value from target
           - Check left and right subtrees
           - Return true if either path works

        Visual Example:
        Tree:
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
        targetSum = 22

        Path 1: 5 -> 4 -> 11 -> 2 = 22
        Path 2: 5 -> 8 -> 4 -> 1 = 18
        Returns true because Path 1 exists
        */

        // Base case: empty tree
        if(root == NULL) return false;

        // Base case: leaf node
        if(root->left == NULL && root->right == NULL) {
            // Check if remaining sum equals leaf's value
            return targetSum - root->val == 0;
        }

        // Recursive case: subtract current value and check children
        targetSum -= root->val;

        // Check if either left or right path works
        return hasPathSum(root->left, targetSum) || 
               hasPathSum(root->right, targetSum);
    }
};

/*
Simple Memory Aid:

1. Base Cases:
   - NULL node: return false
   - Leaf node: check if remaining sum equals node's value

2. Recursive Case:
   - Subtract current value from target
   - Check left subtree
   - Check right subtree
   - Return true if either works

3. Visual Process:
   For targetSum = 22:
   Step 1: root = 5
           targetSum = 22 - 5 = 17
           Check left(4) and right(8)

   Step 2: root = 4
           targetSum = 17 - 4 = 13
           Check left(11) and right(NULL)

   Step 3: root = 11
           targetSum = 13 - 11 = 2
           Check left(7) and right(2)

   Step 4: root = 2 (leaf)
           targetSum = 2 - 2 = 0
           Return true

4. Common Pitfalls:
   - Not handling NULL nodes
   - Not checking leaf nodes correctly
   - Forgetting to subtract current value
   - Not considering negative values

5. Time Complexity: O(n)
   - Each node is visited once
   - In worst case, need to check all paths

6. Space Complexity: O(h)
   - h is height of tree
   - Due to recursion stack
   - Worst case: O(n) for skewed tree
   - Best case: O(log n) for balanced tree

7. Alternative Approaches:
   - Iterative DFS with stack
   - BFS with queue
   - But recursive is most elegant
*/