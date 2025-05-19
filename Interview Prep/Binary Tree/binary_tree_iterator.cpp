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
class BSTIterator {
public:
    // Constructor: Initialize iterator with root
    // Time Complexity: O(n) for initial traversal
    // Space Complexity: O(n) for storing nodes
    BSTIterator(TreeNode* root) {
        /*
        Simple Rules to Remember:
        1. Store nodes in inorder traversal order
        2. Use deque for efficient front operations
        3. Initialize during construction
        4. Return elements one by one

        Visual Example:
        Tree:
              7
             / \
            3   15
               /  \
              9    20

        Inorder traversal: [3,7,9,15,20]
        Stored in deque for sequential access
        */
        inorderTraversal(root);
    }
    
    // Return next smallest number
    // Time Complexity: O(1)
    // Space Complexity: O(1)
    int next() {
        // Get front element and remove it
        int val = nodes.front();
        nodes.pop_front();
        return val;
    }
    
    // Check if there are more numbers
    // Time Complexity: O(1)
    // Space Complexity: O(1)
    bool hasNext() {
        return !nodes.empty();
    }

private:
    // Store nodes in inorder traversal order
    deque<int> nodes;
    
    // Perform inorder traversal and store nodes
    // Time Complexity: O(n)
    // Space Complexity: O(n) for recursion stack
    void inorderTraversal(TreeNode* node) {
        if (!node) return;
        
        // Visit left subtree
        inorderTraversal(node->left);
        
        // Store current node
        nodes.push_back(node->val);
        
        // Visit right subtree
        inorderTraversal(node->right);
    }
};

/*
Simple Memory Aid:

1. Iterator Design:
   - Store nodes in sorted order (inorder)
   - Use deque for efficient front operations
   - Return elements one by one
   - Check if more elements exist

2. Key Operations:
   a. Constructor: Initialize with inorder traversal
   b. next(): Return and remove front element
   c. hasNext(): Check if deque is empty
   d. inorderTraversal: Store nodes in order

3. Visual Process:
   For tree:
         7
        / \
       3   15
          /  \
         9    20

   Step 1: Inorder traversal
           [3,7,9,15,20]

   Step 2: Store in deque
           front -> [3,7,9,15,20] <- back

   Step 3: next() calls
           next() -> 3
           next() -> 7
           next() -> 9
           next() -> 15
           next() -> 20

4. Common Pitfalls:
   - Not handling empty tree
   - Incorrect traversal order
   - Inefficient data structure
   - Memory leaks

5. Time Complexity:
   - Constructor: O(n)
   - next(): O(1)
   - hasNext(): O(1)
   - Overall: O(n) for n operations

6. Space Complexity:
   - O(n) for storing nodes
   - O(h) for recursion stack
   - Where h is height of tree

7. Alternative Approaches:
   - Stack-based iterative traversal
   - Morris traversal
   - But this approach is most intuitive
*/

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */