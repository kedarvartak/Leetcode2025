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
    // Morris Traversal Approach
    // Time Complexity: O(n) where n is number of nodes
    // Space Complexity: O(1) as we only use pointers
    void flatten(TreeNode* root) {
        /*
        Simple Rules to Remember:
        1. For each node, if it has a left child:
           - Find the rightmost node in its left subtree
           - Make that node's right point to current node's right
           - Make current node's right point to its left
           - Set current node's left to NULL
        2. Move to the right child
        3. Repeat until we reach the end

        Visual Example:
        Initial Tree:
              1
             / \
            2   5
           / \   \
          3   4   6

        After processing node 1:
            1
             \
              2
             / \
            3   4
                 \
                  5
                   \
                    6

        After processing node 2:
            1
             \
              2
               \
                3
                 \
                  4
                   \
                    5
                     \
                      6
        */

        if (root == NULL) return;

        TreeNode* curr = root;

        while(curr != NULL) {
            // If current node has a left child
            if(curr->left != NULL) {
                // Step 1: Find the rightmost node in left subtree
                TreeNode* last = curr->left;
                while(last->right != NULL) {
                    last = last->right;
                }

                // Step 2: Make last node's right point to current's right
                last->right = curr->right;
                
                // Step 3: Make current's right point to its left
                curr->right = curr->left;
                
                // Step 4: Set current's left to NULL
                curr->left = NULL;
            }
            
            // Move to the right child
            curr = curr->right;
        }    
    }
};

/*
Simple Memory Aid:

1. For each node with left child:
   - Find rightmost in left subtree
   - Connect it to right subtree
   - Move left subtree to right
   - Clear left pointer

2. Key Steps:
   a. Find last node in left subtree
   b. Connect last->right to curr->right
   c. Move curr->left to curr->right
   d. Set curr->left to NULL
   e. Move to next node

3. Visual Process:
   Before:      After:
     1           1
    / \           \
   2   5           2
  / \   \           \
 3   4   6           3
                      \
                       4
                        \
                         5
                          \
                           6

4. Common Pitfalls:
   - Forgetting to find the rightmost node
   - Not handling NULL cases
   - Incorrect pointer connections
   - Not clearing left pointers

5. Time Complexity: O(n)
   - Each node is visited once
   - Finding rightmost node is O(h) but amortized to O(1)
   - Overall linear time

6. Space Complexity: O(1)
   - Only uses a few pointers
   - No extra space needed
   - In-place transformation
*/