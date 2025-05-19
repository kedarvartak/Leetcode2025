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
    // Approach 1: Recursive DFS
    // Time Complexity: O(min(n,m)) where n and m are number of nodes in trees
    // Space Complexity: O(min(h1,h2)) where h1 and h2 are heights of trees
    bool isSameTree(TreeNode* p, TreeNode* q) {
        /*
        Example Walkthrough:
        Tree 1:        Tree 2:
             1             1
            / \           / \
           2   3         2   3
          
        Step 1: Compare root nodes (1 == 1) -> true
        Step 2: Compare left subtrees (2 == 2) -> true
        Step 3: Compare right subtrees (3 == 3) -> true
        Final result: true
        
        Another Example:
        Tree 1:        Tree 2:
             1             1
            / \           / \
           2   3         2   4
          
        Step 1: Compare root nodes (1 == 1) -> true
        Step 2: Compare left subtrees (2 == 2) -> true
        Step 3: Compare right subtrees (3 != 4) -> false
        Final result: false
        */

        // Base case: both trees are empty
        if(p == NULL && q == NULL) return true; 
        
        // Base case: one tree is empty, other is not
        if(p == NULL || q == NULL) return false;
        
        // Compare current nodes' values
        if(p->val != q->val) return false;
        
        // Recursively compare left and right subtrees
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }

    // Approach 2: Iterative BFS using Queue
    // Time Complexity: O(min(n,m)) where n and m are number of nodes
    // Space Complexity: O(min(n,m)) for queue
    bool isSameTree_BFS(TreeNode* p, TreeNode* q) {
        /*
        Example Walkthrough:
        Tree 1:        Tree 2:
             1             1
            / \           / \
           2   3         2   3
          
        Queue state:
        1. [(1,1)] -> pop and compare -> true
        2. [(2,2), (3,3)] -> pop (2,2) and compare -> true
        3. [(3,3)] -> pop and compare -> true
        4. [] -> empty queue, return true
        */
        
          
        queue<pair<TreeNode*, TreeNode*>> queue;
        queue.push({p, q});
        
        while (!queue.empty()) {
            auto [node1, node2] = queue.front();
            queue.pop();
            
            if (!node1 && !node2) continue;
            if (!node1 || !node2) return false;
            if (node1->val != node2->val) return false;
            
            queue.push({node1->left, node2->left});
            queue.push({node1->right, node2->right});
        }
        
        return true;
    }

    // Approach 3: Iterative DFS using Stack
    // Time Complexity: O(min(n,m)) where n and m are number of nodes
    // Space Complexity: O(min(h1,h2)) where h1 and h2 are heights
    bool isSameTree_DFS(TreeNode* p, TreeNode* q) {
        /*
        Example Walkthrough:
        Tree 1:        Tree 2:
             1             1
            / \           / \
           2   3         2   3
          
        Stack state:
        1. [(1,1)] -> pop and compare -> true
        2. [(2,2), (3,3)] -> pop (2,2) and compare -> true
        3. [(3,3)] -> pop and compare -> true
        4. [] -> empty stack, return true
        */
        
        stack<pair<TreeNode*, TreeNode*>> st;
        st.push({p, q});
        
        while (!st.empty()) {
            auto [node1, node2] = st.top();
            st.pop();
            
            if (!node1 && !node2) continue;
            if (!node1 || !node2) return false;
            if (node1->val != node2->val) return false;
            
            st.push({node1->right, node2->right});
            st.push({node1->left, node2->left});
        }
        
        return true;
    }
};

/*
Comparison of Approaches:

1. Recursive DFS (Original):
   - Pros: Simple, elegant, easy to understand
   - Cons: Stack overflow for very deep trees
   - Best when: Tree depth is reasonable

2. Iterative BFS:
   - Pros: No stack overflow, level-by-level comparison
   - Cons: More complex, uses more memory
   - Best when: Trees are wide rather than deep

3. Iterative DFS:
   - Pros: No stack overflow, depth-first comparison
   - Cons: More complex than recursive version
   - Best when: Trees are deep rather than wide

Time Complexity:
- All approaches: O(min(n,m)) where n and m are number of nodes
- We stop as soon as we find a mismatch

Space Complexity:
- Recursive DFS: O(min(h1,h2)) where h1 and h2 are heights
- Iterative BFS: O(min(n,m)) for queue
- Iterative DFS: O(min(h1,h2)) for stack

Note: For most cases, the recursive approach is preferred due to its simplicity.
Use iterative approaches when dealing with very deep trees or when stack space is limited.
*/