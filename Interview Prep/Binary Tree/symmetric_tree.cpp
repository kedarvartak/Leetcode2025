class Solution {
public:
    // Recursive DFS Approach
    // Time Complexity: O(n) where n is number of nodes
    // Space Complexity: O(h) where h is height of tree (due to recursion stack)
    bool isMirror(TreeNode* left, TreeNode* right) {
        /*
        Example Walkthrough:
        Tree:
             1
            / \
           2   2
          / \ / \
         3  4 4  3
        
        Step 1: Compare root's children (2,2) -> true
        Step 2: Compare (3,3) and (4,4) -> true
        Step 3: All comparisons match -> tree is symmetric
        
        Another Example:
             1
            / \
           2   2
          /     \
         3       3
        
        Step 1: Compare root's children (2,2) -> true
        Step 2: Compare (3,null) and (null,3) -> false
        Step 3: Tree is not symmetric
        */

        // Base case: both nodes are null
        if (left == NULL && right == NULL) return true;
        
        // Base case: only one node is null
        if (left == NULL || right == NULL) return false;
        
        // Compare current nodes' values
        if (left->val != right->val) return false;
        
        // Recursively check mirror property:
        // left's left should mirror right's right
        // left's right should mirror right's left
        return isMirror(left->left, right->right) && 
               isMirror(left->right, right->left);
    }

    bool isSymmetric(TreeNode* root) {
        // Empty tree is symmetric
        if (root == NULL) return true;
        
        // Check if left and right subtrees are mirror images
        return isMirror(root->left, root->right);
    }

    // Approach 2: Iterative BFS using Queue
    // Time Complexity: O(n) where n is number of nodes
    // Space Complexity: O(n) for queue
    bool isSymmetric_BFS(TreeNode* root) {
        /*
        Example Walkthrough:
        Tree:
             1
            / \
           2   2
          / \ / \
         3  4 4  3
        
        Queue state:
        1. [(2,2)] -> pop and compare -> true
        2. [(3,3), (4,4)] -> pop (3,3) and compare -> true
        3. [(4,4)] -> pop and compare -> true
        4. [] -> empty queue, return true
        */
        
        if (!root) return true;
        
        queue<pair<TreeNode*, TreeNode*>> queue;
        queue.push({root->left, root->right});
        
        while (!queue.empty()) {
            auto [left, right] = queue.front();
            queue.pop();
            
            if (!left && !right) continue;
            if (!left || !right) return false;
            if (left->val != right->val) return false;
            
            // Push mirror pairs
            queue.push({left->left, right->right});
            queue.push({left->right, right->left});
        }
        
        return true;
    }

    // Approach 3: Iterative DFS using Stack
    // Time Complexity: O(n) where n is number of nodes
    // Space Complexity: O(h) where h is height of tree
    bool isSymmetric_DFS(TreeNode* root) {
        /*
        Example Walkthrough:
        Tree:
             1
            / \
           2   2
          / \ / \
         3  4 4  3
        
        Stack state:
        1. [(2,2)] -> pop and compare -> true
        2. [(3,3), (4,4)] -> pop (3,3) and compare -> true
        3. [(4,4)] -> pop and compare -> true
        4. [] -> empty stack, return true
        */
        
        if (!root) return true;
        
        stack<pair<TreeNode*, TreeNode*>> stack;
        stack.push({root->left, root->right});
        
        while (!stack.empty()) {
            auto [left, right] = stack.top();
            stack.pop();
            
            if (!left && !right) continue;
            if (!left || !right) return false;
            if (left->val != right->val) return false;
            
            // Push mirror pairs
            stack.push({left->right, right->left});
            stack.push({left->left, right->right});
        }
        
        return true;
    }
};

/*
Recursive Approach Explanation:

1. Base Cases:
   - Empty tree is symmetric
   - Single node is symmetric
   - Mismatched null nodes are not symmetric
   - Different values are not symmetric

2. Recursive Case:
   - For each pair of nodes, check:
     a. Their values are equal
     b. Left's left subtree mirrors right's right subtree
     c. Left's right subtree mirrors right's left subtree

3. Time Complexity: O(n)
   - We visit each node exactly once
   - n is the number of nodes in the tree

4. Space Complexity: O(h)
   - h is the height of the tree
   - Space is used by the recursion stack
   - Worst case: O(n) for skewed tree
   - Best case: O(log n) for balanced tree

5. Key Points:
   - A tree is symmetric if it's a mirror image of itself
   - Mirror property means:
     * Left subtree of left node = Right subtree of right node
     * Right subtree of left node = Left subtree of right node
   - We only need to compare corresponding nodes

6. Common Pitfalls:
   - Forgetting to check for null nodes
   - Not checking both left-right and right-left pairs
   - Not handling empty tree case
*/
