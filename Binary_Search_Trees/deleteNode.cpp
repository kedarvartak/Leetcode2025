class Solution {
public:
    TreeNode* findMin(TreeNode* node) {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == NULL) return NULL;

        if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } 
        else if (root->val < key) {
            root->right = deleteNode(root->right, key);
        } 
        else {
            if (root->left == NULL) return root->right;
            if (root->right == NULL) return root->left;

            TreeNode* minNode = findMin(root->right);
            root->val = minNode->val;
            root->right = deleteNode(root->right, minNode->val);
        }

        return root;
    }
};
