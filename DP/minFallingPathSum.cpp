#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    // Approach 1: Recursion (Brute Force)
    int recursion(int i, int j, vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        if (j < 0 || j >= m) return INT_MAX;
        if (i == 0) return matrix[0][j];

        int up = recursion(i - 1, j, matrix);
        int left = recursion(i - 1, j - 1, matrix);
        int right = recursion(i - 1, j + 1, matrix);

        return matrix[i][j] + min({up, left, right});
    }

    int minFallingPathSumRecursion(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        int mini = INT_MAX;
        for (int j = 0; j < m; j++) {
            mini = min(mini, recursion(n - 1, j, matrix));
        }
        return mini;
    }

    // Approach 2: Memoization (Top-Down DP)
    int memoization(int i, int j, vector<vector<int>>& matrix, vector<vector<int>>& dp) {
        int n = matrix.size(), m = matrix[0].size();
        if (j < 0 || j >= m) return INT_MAX;
        if (i == 0) return matrix[0][j];
        if (dp[i][j] != -1) return dp[i][j];

        int up = memoization(i - 1, j, matrix, dp);
        int left = (j > 0) ? memoization(i - 1, j - 1, matrix, dp) : INT_MAX;
        int right = (j < m - 1) ? memoization(i - 1, j + 1, matrix, dp) : INT_MAX;

        return dp[i][j] = matrix[i][j] + min({up, left, right});
    }

    int minFallingPathSumMemoization(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        int mini = INT_MAX;
        for (int j = 0; j < m; j++) {
            mini = min(mini, memoization(n - 1, j, matrix, dp));
        }
        return mini;
    }

    // Approach 3: Tabulation (Bottom-Up DP)
    int minFallingPathSumTabulation(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));

        for (int j = 0; j < m; j++) dp[0][j] = matrix[0][j];

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int up = dp[i - 1][j];
                int left = (j > 0) ? dp[i - 1][j - 1] : INT_MAX;
                int right = (j < m - 1) ? dp[i - 1][j + 1] : INT_MAX;

                dp[i][j] = matrix[i][j] + min({up, left, right});
            }
        }
        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }

    // Approach 4: Space Optimized DP
    int minFallingPathSumSpaceOptimized(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<int> prev(m, 0), curr(m, 0);

        for (int j = 0; j < m; j++) prev[j] = matrix[0][j];

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int up = prev[j];
                int left = (j > 0) ? prev[j - 1] : INT_MAX;
                int right = (j < m - 1) ? prev[j + 1] : INT_MAX;

                curr[j] = matrix[i][j] + min({up, left, right});
            }
            prev = curr;
        }

        return *min_element(prev.begin(), prev.end());
    }

    // Approach 5: In-Place Modification (Best Space Optimization)
    int minFallingPathSumInPlace(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int up = matrix[i - 1][j];
                int left = (j > 0) ? matrix[i - 1][j - 1] : INT_MAX;
                int right = (j < m - 1) ? matrix[i - 1][j + 1] : INT_MAX;

                matrix[i][j] += min({up, left, right});
            }
        }

        return *min_element(matrix[n - 1].begin(), matrix[n - 1].end());
    }
};

// Driver Code
int main() {
    vector<vector<int>> matrix = {
        {2, 1, 3},
        {6, 5, 4},
        {7, 8, 9}
    };

    Solution sol;

    // Uncomment any of the following lines to test different approaches:
    
    // cout << "Recursion (Brute Force): " << sol.minFallingPathSumRecursion(matrix) << endl;
    
    // cout << "Memoization (Top-Down DP): " << sol.minFallingPathSumMemoization(matrix) << endl;
    
    // cout << "Tabulation (Bottom-Up DP): " << sol.minFallingPathSumTabulation(matrix) << endl;
    
    // cout << "Space Optimized DP: " << sol.minFallingPathSumSpaceOptimized(matrix) << endl;
    
    cout << "In-Place DP (Best Space Optimization): " << sol.minFallingPathSumInPlace(matrix) << endl;

    return 0;
}
