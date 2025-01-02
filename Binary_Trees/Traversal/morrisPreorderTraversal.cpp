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
		vector<int> preorder(TreeNode* root){
	       vector <int> preorder;
		   TreeNode* curr = root;

		   while(curr != NULL){
			//case 1 - no left subtree
			if(curr -> left == NULL){
				preorder.push_back(curr -> data);
				curr = curr -> right;
			}
			//case 2 - has a left subtree
			else{ // thread banavla
				TreeNode* prev = curr -> left;
				while(prev -> right && prev -> right != curr){
					prev = prev -> right;
				}
				// thread udavla
				if(prev -> right == NULL){
					prev -> right = curr;
					preorder.push_back(curr -> data); // as preorder is NLR
					curr = curr -> left;
				}

				else{ // im going to right 
					prev -> right = NULL;
					curr = curr -> right;
				}
			}
		   }
		   return preorder;
		}
};