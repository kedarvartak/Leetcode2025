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
			// base case
			if (node == NULL)
			return;
			// N L R
			ans.push_back(node -> data);
			helper(node -> left, ans);
			helper(node -> right, ans);
		}


		vector<int> preorder(TreeNode* root){
			
			vector<int> ans;
			helper(root, ans);
			return ans;
		}
};