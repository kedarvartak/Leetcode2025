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
		void helper(TreeNode* node, vector<int>& ans){
        //BC
        if(node == NULL) return;
        helper(node -> left, ans);
        ans.push_back(node -> data);
        helper(node -> right, ans);
    	}

		vector<int> inorder(TreeNode* root){
	    vector<int> ans;
        helper(root, ans);
        return ans;
		}
};