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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        /*
        Simple Rules to Remember:
        1. Process nodes level by level
        2. Use a queue to maintain the order
        3. For each level:
           - Get the current level size
           - Process all nodes at that level
           - Add values to level vector
           - Reverse level vector if needed (zigzag)
           - Add children to queue for next level
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
               Level 0 is left to right: [3]
               Queue becomes: [9, 20]

        Step 2: Level 1
               Queue: [9, 20]
               Level size: 2
               Process: 9, 20
               Add children: 15, 7
               Level 1 is right to left: [20, 9]
               Queue becomes: [15, 7]

        Step 3: Level 2
               Queue: [15, 7]
               Level size: 2
               Process: 15, 7
               No children to add
               Level 2 is left to right: [15, 7]
               Queue becomes: []

        Final result: [[3], [20, 9], [15, 7]]
        */

        vector<vector<int>> result;
        if (root == NULL) return result;

        // Initialize queue with root node
        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;  // Direction flag

        // Process each level
        while (!q.empty()) {
            // Get the number of nodes at current level
            int levelSize = q.size();
            vector<int> currentLevel(levelSize);

            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                // Get front node and remove it from queue
                TreeNode* node = q.front();
                q.pop();

                // Add node value to level vector
                // If left to right, use i as index
                // If right to left, use (levelSize - 1 - i) as index
                int index = leftToRight ? i : (levelSize - 1 - i);
                currentLevel[index] = node->val;

                // Add children to queue if they exist
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            // Add current level to result
            result.push_back(currentLevel);
            
            // Toggle direction for next level
            leftToRight = !leftToRight;
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
      - Create level vector
      - Process all nodes at level
      - Add values in zigzag order
      - Add children to queue
      - Toggle direction
   c. Return zigzag traversal

3. Visual Process:
   For tree:
                3
               / \
              9  20
                 / \
                15  7

   Level 0: [3]     -> Left to right: [3]
   Level 1: [9, 20] -> Right to left: [20, 9]
   Level 2: [15, 7] -> Left to right: [15, 7]
   Result: [[3], [20, 9], [15, 7]]

4. Common Pitfalls:
   - Not handling empty tree
   - Not tracking level size
   - Incorrect zigzag ordering
   - Not maintaining level order
   - Not considering all edge cases
   - Wrong index calculation

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
   - Alternating direction
   - Left to right then right to left
   - Children processed after parents
   - Queue maintains order
   - Level vectors in result

8. Alternative Approaches:
   - Using two stacks
   - Using deque for level storage
   - Recursive DFS with level tracking
   - Two queues for level separation
   - Level marker in queue
*/
