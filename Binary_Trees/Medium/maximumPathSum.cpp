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
    int findSum(TreeNode* root, int& maxi){
        if(root == NULL) return 0;

        int left = max(0, findSum(root -> left, maxi));
        int right = max(0, findSum(root -> right, maxi));

        maxi = max(maxi, left + right + root -> data);

        return max(left, right) + root -> data;
    }


    int maxPathSum(TreeNode* root) {
        int maxi = INT_MIN;
        findSum(root, maxi);
        return maxi;
    }
};	