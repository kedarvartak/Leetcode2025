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
    void recursion(TreeNode* root, int level, vector<int>& ans){
        if(root == NULL) return;

        if(ans.size() == level) ans.push_back(root -> data);
        recursion(root -> right, level+1, ans);       
        recursion(root -> left, level+1, ans);
        
    }

    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        recursion(root, 0, ans);
        return ans;  
    }
};