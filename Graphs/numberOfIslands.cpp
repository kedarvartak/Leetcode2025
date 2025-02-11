
class Solution {
public:
    void bfs(int i, int j, vector<vector<bool>>& visited, vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        queue<pair<int, int>> q;
        q.push({i, j});
        visited[i][j] = true;

        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();

            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;

                if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m &&
                    grid[newRow][newCol] == '1' && !visited[newRow][newCol]) {
                    
                    visited[newRow][newCol] = true;
                    q.push({newRow, newCol});
                }
            }
        }
    }

    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int islandCount = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    islandCount++;
                    bfs(i, j, visited, grid);
                }
            }
        }
        return islandCount;
    }
};
