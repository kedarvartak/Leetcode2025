class Solution {
public:
    // Recursive DFS Approach
    // Time Complexity: O(n) where n is number of nodes
    // Space Complexity: O(n) for hash map and recursion stack
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        /*
        Example Walkthrough:
        preorder = [3,9,20,15,7]
        inorder = [9,3,15,20,7]
        
        Step 1: Create hash map for inorder indices
        {9:0, 3:1, 15:2, 20:3, 7:4}
        
        Step 2: Start with root (3)
        - Find 3's position in inorder: index = 1
        - Left subtree: inorder[0:0] = [9]
        - Right subtree: inorder[2:4] = [15,20,7]
        
        Step 3: Build left subtree
        - Root: 9 (from preorder[1])
        - No left or right children
        
        Step 4: Build right subtree
        - Root: 20 (from preorder[2])
        - Left: 15
        - Right: 7
        
        Final Tree:
             3
            / \
           9  20
              / \
             15  7
        */

        // Create hash map for O(1) lookup of inorder indices
        unordered_map<int, int> mp;
        for (int i = 0; i < inorder.size(); i++) {
            mp[inorder[i]] = i;
        }

        // Start recursive construction
        return helper(preorder, inorder, mp, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }

    TreeNode* helper(vector<int>& preorder, vector<int>& inorder, unordered_map<int, int>& mp, 
                     int preStart, int preEnd, int inStart, int inEnd) {
        // Base case: empty subtree
        if (preStart > preEnd || inStart > inEnd)
            return NULL;

        // Current root is first element in preorder
        int val = preorder[preStart];
        TreeNode* root = new TreeNode(val);
        
        // Find root's position in inorder
        int index = mp[val];
        
        // Calculate size of left subtree
        int left = index - inStart;

        // Recursively build left and right subtrees
        // Left subtree: 
        // - preorder: [preStart+1, preStart+left]
        // - inorder: [inStart, index-1]
        root->left = helper(preorder, inorder, mp, 
                          preStart + 1, preStart + left, 
                          inStart, index - 1);
        
        // Right subtree:
        // - preorder: [preStart+left+1, preEnd]
        // - inorder: [index+1, inEnd]
        root->right = helper(preorder, inorder, mp, 
                           preStart + left + 1, preEnd, 
                           index + 1, inEnd);

        return root;
    }
};

/*
Recursive Approach Explanation:

1. Key Concepts:
   - Preorder: Root -> Left -> Right
   - Inorder: Left -> Root -> Right
   - First element in preorder is always the root
   - In inorder, elements before root are in left subtree
   - Elements after root are in right subtree

2. Algorithm Steps:
   a. Create hash map for O(1) lookup of inorder indices
   b. For each subtree:
      - Get root from preorder
      - Find root's position in inorder
      - Split inorder into left and right subtrees
      - Recursively build subtrees

3. Time Complexity: O(n)
   - Building hash map: O(n)
   - Tree construction: O(n)
   - Each node is processed exactly once

4. Space Complexity: O(n)
   - Hash map: O(n)
   - Recursion stack: O(h) where h is height
   - Worst case: O(n) for skewed tree

5. Key Points:
   - Preorder gives us the root
   - Inorder helps us split into subtrees
   - Hash map provides O(1) lookup
   - We need both traversals to uniquely construct the tree

6. Common Pitfalls:
   - Incorrect index calculations
   - Not handling empty subtrees
   - Memory leaks from not deleting nodes
   - Array index out of bounds

7. Edge Cases:
   - Empty arrays
   - Single node
   - Skewed tree
   - Balanced tree
   - Duplicate values (if allowed)

8. Alternative Approaches:
   - Iterative solution using stack
   - Without hash map (but slower)
   - But recursive approach is most elegant

9. Important Properties:
   - Unique tree construction possible only with both traversals
   - Preorder + Inorder = Unique tree
   - Postorder + Inorder = Unique tree
   - Preorder + Postorder = Not unique
*/
