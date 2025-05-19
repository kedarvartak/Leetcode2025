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
    TreeNode* invertTree(TreeNode* root) {
        /*
        Example Walkthrough:
        Original Tree:    Inverted Tree:
             4               4
            / \             / \
           2   7           7   2
          / \ / \         / \ / \
         1  3 6  9       9  6 3  1
        
        Step 1: Start at root (4)
          - Swap left (2) and right (7)
        
        Step 2: Process left subtree (7)
          - Swap left (6) and right (9)
        
        Step 3: Process right subtree (2)
          - Swap left (1) and right (3)
        
        Final Result: Tree is mirrored horizontally
        */

        // Base case: empty tree
        if (root == NULL) return root;

        // Swap left and right children of current node
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;

        // Recursively invert left and right subtrees
        invertTree(root->left);
        invertTree(root->right);

        return root;
    }
};

/*
Recursive Approach Explanation:

1. Base Case:
   - Empty tree (NULL) remains empty
   - This is our stopping condition for recursion

2. Recursive Case:
   - For each node:
     a. Swap its left and right children
     b. Recursively invert left subtree
     c. Recursively invert right subtree
     d. Return the inverted node

3. Time Complexity: O(n)
   - We visit each node exactly once
   - n is the number of nodes in the tree
   - Each node requires constant time for swapping

4. Space Complexity: O(h)
   - h is the height of the tree
   - Space is used by the recursion stack
   - Worst case: O(n) for skewed tree
   - Best case: O(log n) for balanced tree

5. Key Points:
   - Inverting a tree means mirroring it horizontally
   - All left children become right children and vice versa
   - The root node remains the same
   - The operation is performed in-place

6. Common Pitfalls:
   - Forgetting to handle NULL case
   - Not swapping children before recursion
   - Not returning the root node
   - Creating unnecessary new nodes

7. Edge Cases:
   - Empty tree
   - Single node tree
   - Skewed tree (all nodes on one side)
   - Balanced tree
   - Tree with only left children
   - Tree with only right children

8. Visual Understanding:
   - Imagine a mirror placed vertically at the root
   - All nodes on the left appear on the right
   - All nodes on the right appear on the left
   - The structure is mirrored but values remain same

9. Alternative Names:
   - Mirror Tree
   - Flip Tree
   - Horizontal Mirror
*/