class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> result;
        if (!root) return result;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();
            int maxVal = INT_MIN;

            for (int i = 0; i < size; i++) {
                TreeNode* front = q.front();
                q.pop();

                maxVal = max(maxVal, front->val);

                if (front->left) q.push(front->left);
                if (front->right) q.push(front->right);
            }
            result.push_back(maxVal);
        }
        return result;
    }
};
