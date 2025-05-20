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
    vector<int> rightSideView(TreeNode* root) {
        /*
        Simple Rules to Remember:
        1. Process nodes level by level
        2. Use a queue to maintain the order
        3. For each level:
           - Get the current level size
           - Process all nodes at that level
           - Take the rightmost node's value
           - Add children to queue for next level
        4. Store only the rightmost node's value for each level

        Visual Example:
        Tree:
                1
               / \
              2   3
               \   \
                5   4

        Step 1: Level 0 (Root)
               Queue: [1]
               Level size: 1
               Process: 1 (last node in level)
               Add children: 2, 3
               Add 1 to result
               Queue becomes: [2, 3]

        Step 2: Level 1
               Queue: [2, 3]
               Level size: 2
               Process: 2 (not last)
               Process: 3 (last node in level)
               Add children: 5, 4
               Add 3 to result
               Queue becomes: [5, 4]

        Step 3: Level 2
               Queue: [5, 4]
               Level size: 2
               Process: 5 (not last)
               Process: 4 (last node in level)
               No children to add
               Add 4 to result
               Queue becomes: []

        Final result: [1, 3, 4]
        */

        vector<int> result;
        if (root == NULL) return result;

        // Initialize queue with root node
        queue<TreeNode*> q;
        q.push(root);

        // Process each level
        while (!q.empty()) {
            // Get the number of nodes at current level
            int levelSize = q.size();

            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                // Get front node and remove it from queue
                TreeNode* front = q.front();
                q.pop();

                // If this is the last node in the level, add its value to result
                if (i == levelSize - 1) {
                    result.push_back(front->val);
                }

                // Add children to queue if they exist
                // Note: We add left child first to maintain level order
                if (front->left) q.push(front->left);
                if (front->right) q.push(front->right);
            }
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
      - Process all nodes at level
      - Take last node's value
      - Add children to queue
   c. Return right side view

3. Visual Process:
   For tree:
                1
               / \
              2   3
               \   \
                5   4

   Level 0: [1]     -> Take 1
   Level 1: [2, 3]  -> Take 3
   Level 2: [5, 4]  -> Take 4
   Result: [1, 3, 4]

4. Common Pitfalls:
   - Not handling empty tree
   - Not tracking level size
   - Taking wrong node in level
   - Not maintaining level order
   - Not considering all edge cases

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
   - Rightmost node at each level
   - Left to right within level
   - Children processed after parents
   - Queue maintains order

8. Alternative Approaches:
   - Recursive DFS with level tracking
   - Two queues for level separation
   - Level marker in queue
   - Level count tracking
   - Reverse level order traversal
*/