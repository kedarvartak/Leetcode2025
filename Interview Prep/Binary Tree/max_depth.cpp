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
    // Space Complexity: O(h) where h is height of tree (due to recursion stack)
    int maxDepth(TreeNode* root) {
        /*
        Example Walkthrough:
        Tree:
             3
            / \
           9  20
              / \
             15  7
        
        Step 1: Start at root (3)
        Step 2: Check left subtree (9)
          - 9 has no children -> depth = 1
        Step 3: Check right subtree (20)
          - 20 has two children (15,7)
          - Both 15 and 7 have no children -> depth = 2
        Step 4: Return max(1,2) + 1 = 3
        
        Another Example:
             1
              \
               2
                \
                 3
        
        Step 1: Start at root (1)
        Step 2: Left subtree is null -> depth = 0
        Step 3: Check right subtree (2)
          - 2 has right child (3)
          - 3 has no children -> depth = 1
        Step 4: Return max(0,1) + 1 = 2
        */

        // Base case: empty tree has depth 0
        if(root == NULL) return 0;

        // Recursively find depth of left and right subtrees
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);

        // Return maximum depth of subtrees plus 1 for current node
        return 1 + max(left, right);    
    }
};

/*
Recursive Approach Explanation:

1. Base Case:
   - Empty tree (NULL) has depth 0
   - This is our stopping condition for recursion

2. Recursive Case:
   - For each node:
     a. Find depth of left subtree
     b. Find depth of right subtree
     c. Take maximum of both depths
     d. Add 1 for current node

3. Time Complexity: O(n)
   - We visit each node exactly once
   - n is the number of nodes in the tree

4. Space Complexity: O(h)
   - h is the height of the tree
   - Space is used by the recursion stack
   - Worst case: O(n) for skewed tree
   - Best case: O(log n) for balanced tree

5. Key Points:
   - Depth of a node is the number of edges from root to that node
   - Maximum depth is the length of the longest path from root to any leaf
   - We need to check both left and right subtrees
   - Each level adds 1 to the depth

6. Common Pitfalls:
   - Forgetting to add 1 for current node
   - Not handling NULL case properly
   - Not considering both left and right subtrees
   - Confusing depth with height (they are the same in this case)

7. Alternative Names:
   - Maximum Depth
   - Tree Height
   - Longest Path from Root to Leaf
*/