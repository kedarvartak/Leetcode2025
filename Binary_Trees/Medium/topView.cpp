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
    vector<int> topView(TreeNode *root){
        vector <int> ans;
        if(root == NULL) return ans;

        map<int, int> mp;
        queue<pair<TreeNode*, int>> q;

        q.push({root, 0});

        while(!q.empty()){
            auto it = q.front();
            q.pop();

            TreeNode* node = it.first;
            int line = it.second;

            if(mp.find(line) == mp.end()){
                mp[line] = node -> data;
            }

            if(node -> left != NULL) q.push({node -> left, line - 1});
            if(node -> right != NULL) q.push({node -> right, line + 1});

        }

        for(auto it : mp) ans.push_back(it.second);
        return ans;
    }
};