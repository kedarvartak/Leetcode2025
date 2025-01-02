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
    vector<int> getInorder(TreeNode* root) {
    	
        vector <int> inorder;

        TreeNode* curr = root;

        while (curr != NULL){
            //case 1 - no left subtree present , right traverse kara
            if(curr -> left == NULL){
                inorder.push_back(curr -> data);
                curr = curr -> right;
            }
            // left subtree exists, traverse it pls
            else{

                TreeNode* prev = curr -> left; // find the left child
                while(prev -> right && prev -> right != curr){
                    prev = prev -> right; // find rightmost child
                }
                // thread lavla from left subtree's rightmost child to root
                if(prev -> right == NULL){
                    prev -> right = curr;
                    curr = curr -> left;
                }
                else{
                    prev -> right = NULL;
                    inorder.push_back(curr -> data);
                    curr = curr -> right;
                }

            }
        }
        return inorder;
    }
};