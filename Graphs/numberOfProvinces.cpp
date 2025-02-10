class Solution {
public:
    void bfs(int node, vector<vector<int>>& adjLs, vector<int>& vis) {
        queue<int> q;
        q.push(node);
        vis[node] = 1;

        while (!q.empty()) {
            int i = q.front();
            q.pop();

            for (int adjNode : adjLs[i]) {
                if (!vis[adjNode]) {
                    vis[adjNode] = 1;
                    q.push(adjNode);
                }
            }
        }
    }

    int findCircleNum(vector<vector<int>>& adj) {
        int V = adj.size();
        vector<vector<int>> adjLs(V);
        vector<int> vis(V, 0);
        int cnt = 0;

        
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) { 
                if (adj[i][j] == 1) {
                    adjLs[i].push_back(j);
                    adjLs[j].push_back(i);
                }
            }
        }

        // BFS Traversal
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                cnt++;
                bfs(i, adjLs, vis);
            }
        }

        return cnt;
    }
};
