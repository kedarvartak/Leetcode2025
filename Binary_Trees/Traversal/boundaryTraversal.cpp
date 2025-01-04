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
    bool isLeaf(TreeNode* root){
        return !root -> left && !root -> right;
    }

    void addLeftBoundary(TreeNode* root, vector <int>& res){
        TreeNode* curr = root -> left;
        while(curr){
            if(!isLeaf(curr)) res.push_back(curr-> data);

            if(curr -> left) curr = curr -> left;

            else curr = curr -> right;
        }
    }

    void addRightBoundary(TreeNode* root, vector <int>& res){
        TreeNode* curr = root -> right;
        vector<int> temp;
        while(curr){
            if(!isLeaf(curr)) temp.push_back(curr -> data);
            
            if(curr -> right) curr = curr -> right;
            else curr = curr -> left;

        }
        reverse(temp.begin(), temp.end());
        res.insert(res.end(), temp.begin(), temp.end());
    }

    void addLeaves(TreeNode* root, vector <int>& res){
        if(isLeaf(root)){
            res.push_back(root -> data);
            return;
        }
        if (root -> left) addLeaves(root -> left, res);
        if (root -> right) addLeaves(root -> right, res);
    }

    vector <int> boundary(TreeNode* root){
    	vector <int> res;
        if(!root) return res;
        if(!isLeaf(root)) res.push_back(root -> data);

        addLeftBoundary(root, res);
        addLeaves(root, res);
        addRightBoundary(root, res);
    }
};