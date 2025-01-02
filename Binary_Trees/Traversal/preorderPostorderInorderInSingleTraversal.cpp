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

		vector<vector<int> > treeTraversal(TreeNode* root){
			vector<int> preorder , inorder, postorder;

			if (root == NULL) return {preorder, inorder, postorder};

			stack <pair<TreeNode* , int>> st;

			st.push({root, 1});

			while(!st.empty()){

			auto [node, state] = st.top();
			st.pop();

			if(state == 1){
				preorder.push_back(node -> data);
				st.push({ node, 2 });

				if(node -> left != NULL) st.push({node -> left, 1});
			}	
			else if(state == 2){
				inorder.push_back(node -> data);
				st.push({ node, 3});

				if(node -> right != NULL) st.push({node -> right, 1});

			}
			else if(state == 3){
				postorder.push_back(node -> data);
			}
			}
			return {inorder, preorder, postorder};

		}
};