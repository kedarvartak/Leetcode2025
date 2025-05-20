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
    // Breadth-First Search (BFS) Approach
    // Time Complexity: O(n) where n is the number of nodes
    // Space Complexity: O(w) where w is the maximum width of the tree
    vector<vector<int>> levelOrder(TreeNode* root) {
        /*
        Simple Rules to Remember:
        1. Process nodes level by level
        2. Use a queue to maintain the order
        3. For each level:
           - Get the current level size
           - Process all nodes at that level
           - Add their children to the queue
        4. Store each level's values in a separate vector

        Visual Example:
        Tree:
                3
               / \
              9  20
                 / \
                15  7

        Step 1: Level 0 (Root)
               Queue: [3]
               Level size: 1
               Process: 3
               Add children: 9, 20
               Current level: [3]
               Queue becomes: [9, 20]

        Step 2: Level 1
               Queue: [9, 20]
               Level size: 2
               Process: 9 (no children)
               Process: 20 (add children: 15, 7)
               Current level: [9, 20]
               Queue becomes: [15, 7]

        Step 3: Level 2
               Queue: [15, 7]
               Level size: 2
               Process: 15 (no children)
               Process: 7 (no children)
               Current level: [15, 7]
               Queue becomes: []

        Final result: [[3], [9, 20], [15, 7]]
        */

        vector<vector<int>> ans;
        if(root == NULL) return ans;

        // Initialize queue with root node
        queue<TreeNode*> q;
        q.push(root);

        // Process each level
        while(!q.empty()) {
            // Get the number of nodes at current level
            int levelSize = q.size();
            vector<int> currentLevel;

            // Process all nodes at current level
            for(int i = 0; i < levelSize; i++) {
                // Get front node and remove it from queue
                TreeNode* node = q.front();
                q.pop();

                // Add children to queue if they exist
                if(node->left != NULL) q.push(node->left);
                if(node->right != NULL) q.push(node->right);

                // Add current node's value to level vector
                currentLevel.push_back(node->val);
            }

            // Add current level to result
            ans.push_back(currentLevel);
        }

        return ans;
    }
};

/*
Simple Memory Aid:

1. Queue Properties:
   - First In First Out (FIFO)
   - Maintains level order
   - Stores nodes to be processed
   - Size varies with tree width

2. Key Steps:
   a. Initialize queue with root
   b. While queue not empty:
      - Get current level size
      - Process all nodes at level
      - Add children to queue
      - Store level values
   c. Return level order traversal

3. Visual Process:
   For tree:
                3
               / \
              9  20
                 / \
                15  7

   Level 0: [3]
   Level 1: [9, 20]
   Level 2: [15, 7]

4. Common Pitfalls:
   - Not handling empty tree
   - Not tracking level size
   - Processing nodes in wrong order
   - Not adding children correctly
   - Not maintaining level separation

5. Time Complexity: O(n)
   - n: number of nodes
   - Each node processed once
   - Each edge traversed once
   - Queue operations are O(1)

6. Space Complexity: O(w)
   - w: maximum width of tree
   - Queue stores at most one level
   - Worst case: complete binary tree
   - Last level can have n/2 nodes

7. Key Properties:
   - Level by level processing
   - Left to right within level
   - Children processed after parents
   - Queue maintains order
   - Each level in separate vector

8. Alternative Approaches:
   - Recursive DFS with level tracking
   - Two queues for level separation
   - Level marker in queue
   - Level count tracking
*/