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
    int prev = INT_MIN;
    bool isValid = true;
    void inorder(TreeNode* root){
        if(root == NULL || !isValid) return;

        inorder(root -> left);
        if(prev >= root -> val){
            isValid = false;
        }
        prev = root -> val;
        inorder(root -> right);
    }

    bool isValidBST(TreeNode* root) {
        inorder(root);
        return isValid;
    }
};