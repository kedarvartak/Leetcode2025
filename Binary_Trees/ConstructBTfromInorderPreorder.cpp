class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> mp;
        
        for (int i = 0; i < inorder.size(); i++) {
            mp[inorder[i]] = i;
        }

        return helper(preorder, inorder, mp, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }

    TreeNode* helper(vector<int>& preorder, vector<int>& inorder, unordered_map<int, int>& mp, 
                     int preStart, int preEnd, int inStart, int inEnd) {
        if (preStart > preEnd || inStart > inEnd)
            return NULL;

        int val = preorder[preStart];
        TreeNode* root = new TreeNode(val);
        int index = mp[val];
        int left = index - inStart;

        root->left = helper(preorder, inorder, mp, preStart + 1, preStart + left, inStart, index - 1);
        root->right = helper(preorder, inorder, mp, preStart + left + 1, preEnd, index + 1, inEnd);

        return root;
    }
};
