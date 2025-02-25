/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return NULL;
        unordered_map<Node*, Node*> clones;
        queue<Node*> q;

        clones[node] = new Node(node -> val);
        q.push(node);

        while(!q.empty()){
            Node* curr = q.front();
            q.pop();

            for (Node* neighbor : curr->neighbors) {
                
                if (clones.find(neighbor) == clones.end()) {
                    clones[neighbor] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                
                clones[curr]->neighbors.push_back(clones[neighbor]);
            }
        }
        return clones[node];
    }
};