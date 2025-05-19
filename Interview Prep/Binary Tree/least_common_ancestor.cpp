/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    // Recursive DFS Approach
    // Time Complexity: O(n) where n is number of nodes
    // Space Complexity: O(h) where h is height of tree (recursion stack)
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        /*
        Simple Rules to Remember:
        1. If root is NULL, return NULL
        2. If root is p or q, return root
        3. Recursively search left and right subtrees
        4. If both subtrees return non-NULL, root is LCA
        5. If one subtree returns non-NULL, return that result
        6. If both subtrees return NULL, return NULL

        Visual Example:
        Tree:
              3
             / \
            5   1
           / \  / \
          6  2  0  8
            / \
           7   4

        Finding LCA of 5 and 1:
        - Start at root(3)
        - Left subtree returns 5
        - Right subtree returns 1
        - Both non-NULL, so 3 is LCA

        Finding LCA of 5 and 4:
        - Start at root(3)
        - Left subtree returns 5
        - Right subtree returns NULL
        - Return 5 (from left)
        */

        // Base case: empty tree
        if (root == NULL) return NULL;

        // Base case: root is one of the target nodes
        if (root == p) return p;
        if (root == q) return q;

        // Recursively search left and right subtrees
        TreeNode* leftAns = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightAns = lowestCommonAncestor(root->right, p, q);

        // Case 1: Both subtrees return NULL
        // Neither p nor q found in this subtree
        if (leftAns == NULL && rightAns == NULL) 
            return NULL;

        // Case 2: Only left subtree found a node
        // Return that node (it's the LCA)
        else if (leftAns != NULL && rightAns == NULL) 
            return leftAns;

        // Case 3: Only right subtree found a node
        // Return that node (it's the LCA)
        else if (rightAns != NULL && leftAns == NULL) 
            return rightAns;

        // Case 4: Both subtrees found nodes
        // Current root is the LCA
        else 
            return root;
    }
};

/*
Simple Memory Aid:

1. Base Cases:
   - NULL root: return NULL
   - Root is p: return p
   - Root is q: return q

2. Recursive Cases:
   a. Search left subtree
   b. Search right subtree
   c. Combine results:
      - Both NULL: return NULL
      - One non-NULL: return that
      - Both non-NULL: return root

3. Visual Process:
   For LCA of 5 and 1:
   Step 1: Check root(3)
           Not p or q, continue

   Step 2: Check left(5)
           Found p, return 5

   Step 3: Check right(1)
           Found q, return 1

   Step 4: Both non-NULL
           Return root(3)

4. Common Pitfalls:
   - Not handling NULL case
   - Not checking root == p or q
   - Incorrect return value logic
   - Not considering all cases

5. Time Complexity: O(n)
   - Each node visited once
   - Worst case: need to visit all nodes
   - Best case: O(1) if root is LCA

6. Space Complexity: O(h)
   - h is height of tree
   - Due to recursion stack
   - Worst case: O(n) for skewed tree
   - Best case: O(log n) for balanced tree

7. Key Properties:
   - LCA is the deepest node that has both p and q as descendants
   - A node can be a descendant of itself
   - If one node is ancestor of other, it's the LCA
   - If nodes are in different subtrees, root is LCA
*/