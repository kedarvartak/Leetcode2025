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
    vector<double> averageOfLevels(TreeNode* root) {
        /*
        Simple Rules to Remember:
        1. Process nodes level by level
        2. Use a queue to maintain the order
        3. For each level:
           - Get the current level size
           - Sum all node values at that level
           - Calculate average (sum / count)
           - Add children to queue for next level
        4. Store average for each level

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
               Sum: 3
               Count: 1
               Average: 3.0
               Add children: 9, 20
               Queue becomes: [9, 20]

        Step 2: Level 1
               Queue: [9, 20]
               Level size: 2
               Sum: 9 + 20 = 29
               Count: 2
               Average: 14.5
               Add children: 15, 7
               Queue becomes: [15, 7]

        Step 3: Level 2
               Queue: [15, 7]
               Level size: 2
               Sum: 15 + 7 = 22
               Count: 2
               Average: 11.0
               No children to add
               Queue becomes: []

        Final result: [3.0, 14.5, 11.0]
        */

        vector<double> result;
        if (root == NULL) return result;

        // Initialize queue with root node
        queue<TreeNode*> q;
        q.push(root);

        // Process each level
        while (!q.empty()) {
            // Get the number of nodes at current level
            int levelSize = q.size();
            double levelSum = 0;

            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                // Get front node and remove it from queue
                TreeNode* node = q.front();
                q.pop();

                // Add node value to level sum
                levelSum += node->val;

                // Add children to queue if they exist
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            // Calculate and store average for current level
            result.push_back(levelSum / levelSize);
        }

        return result;
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
      - Initialize level sum
      - Process all nodes at level
      - Add node values to sum
      - Add children to queue
      - Calculate and store average
   c. Return level averages

3. Visual Process:
   For tree:
                3
               / \
              9  20
                 / \
                15  7

   Level 0: [3]     -> Average: 3.0
   Level 1: [9, 20] -> Average: 14.5
   Level 2: [15, 7] -> Average: 11.0
   Result: [3.0, 14.5, 11.0]

4. Common Pitfalls:
   - Not handling empty tree
   - Not tracking level size
   - Integer division instead of double
   - Not maintaining level order
   - Not considering all edge cases
   - Not handling large numbers (overflow)

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
   - Sum and count for each level
   - Left to right within level
   - Children processed after parents
   - Queue maintains order
   - Double precision for averages

8. Alternative Approaches:
   - Recursive DFS with level tracking
   - Two queues for level separation
   - Level marker in queue
   - Level count tracking
   - Using long long for sum to prevent overflow
*/
