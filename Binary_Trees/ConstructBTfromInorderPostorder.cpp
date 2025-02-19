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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
            unordered_map<int, int> mp;
            for(int i = 0; i < inorder.size(); i++){
                mp[inorder[i]] = i;
            }
            int postIndex = postorder.size() - 1;
            return helper(inorder, postorder, mp, postIndex, 0, inorder.size() - 1);
    }

    TreeNode* helper(vector<int>& inorder, vector<int>& postorder, unordered_map<int, int>& mp, int& postIndex, int inStart, int inEnd){
        if (inStart > inEnd) return NULL;
        int rootVal = postorder[postIndex--];
        TreeNode* root = new TreeNode(rootVal);
        int inIndex = mp[rootVal];

        root->right = helper(inorder, postorder, mp, postIndex, inIndex + 1, inEnd);
        root->left = helper(inorder, postorder, mp, postIndex, inStart, inIndex - 1);

        return root;
        
    }
};