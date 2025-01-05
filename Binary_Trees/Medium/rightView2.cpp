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

    vector<int> rightSideView(TreeNode* root) {
        vector <int> ans;
        if(root == NULL) return ans;

        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            int size = q.size();
            int rightValue;

            for(int i = 0; i < size; i++){
                TreeNode* node = q.front();
                q.pop();

                rightValue = node->data;

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            ans.push_back(rightValue);
        }    
        return ans; 
    }
};