/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == NULL) return 0;

        int left = maxDepth(root -> left);
        int right = maxDepth(root -> right);

        return 1 + max(left, right);
    }
};