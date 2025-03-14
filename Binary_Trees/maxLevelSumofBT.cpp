class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        if (!root) return -1;

        queue<TreeNode*> q;
        q.push(root);
        int maxSum = INT_MIN, level = 0, res = 0;

        while (!q.empty()) {
            int size = q.size(), sum = 0;
            level++;

            for (int i = 0; i < size; i++) {
                TreeNode* front = q.front();
                q.pop();

                sum += front->val;
                if (front->left) q.push(front->left);
                if (front->right) q.push(front->right);
            }

            if (sum > maxSum) {
                maxSum = sum;
                res = level;
            }
        }

        return res;
    }
};
