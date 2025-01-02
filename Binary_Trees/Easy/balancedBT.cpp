/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution{
public:
    int getHeight(TreeNode* root){
        if(root == NULL) return 0;

        int left = getHeight(root -> left);
        int right = getHeight(root -> right);

        return 1 + max(left, right);
    }


    bool isBalanced(TreeNode *root){
    	if(root == NULL) return true;

        int left = getHeight(root -> left);
        int right = getHeight(root -> right);

        if(abs(left - right) <= 1 && isBalanced(root -> left) && isBalanced(root -> right))
        return true;

        return false;
    }
};