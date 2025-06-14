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
    void inorder(TreeNode* root, vector<int>&nums){
        if(root == NULL) return;

        inorder(root -> left, nums);
        nums.push_back(root -> val);
        inorder(root -> right, nums);
    }
    int kthSmallest(TreeNode* root, int k) {
        vector<int> nums;
        inorder(root, nums);
        return nums[k - 1];
    }
};

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
    int count = 0;
    int result = -1;

    void inorder(TreeNode* root, int k){
        if(root == NULL) return;

        inorder(root -> left, k);
        count++;
        if(count == k){
            result = root -> val;
            return;
        }
        inorder(root -> right, k);
    }


    int kthSmallest(TreeNode* root, int k) {
        if(root == NULL) return -1;
        inorder(root, k);
        return result;
    }
};

