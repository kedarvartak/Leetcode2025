class Solution {
public:
    // Recursive DFS Approach
    // Time Complexity: O(n) where n is number of nodes
    // Space Complexity: O(n) for hash map and recursion stack
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        /*
        Simple Rules to Remember:
        1. Last element in postorder is always the root
        2. In inorder, everything before root is left subtree
        3. In inorder, everything after root is right subtree
        4. Number of elements in left subtree = root's index in inorder
        */

        // Create hash map for O(1) lookup of inorder indices
        unordered_map<int, int> mp;
        for (int i = 0; i < inorder.size(); i++) {
            mp[inorder[i]] = i;
        }

        return helper(inorder, postorder, mp, 0, inorder.size() - 1, 0, postorder.size() - 1);
    }

    TreeNode* helper(vector<int>& inorder, vector<int>& postorder, unordered_map<int, int>& mp, 
                     int inStart, int inEnd, int postStart, int postEnd) {
        // Base case: empty subtree
        if (inStart > inEnd || postStart > postEnd) {
            return NULL;
        }

        // Step 1: Get root from postorder (last element)
        int rootVal = postorder[postEnd];
        TreeNode* root = new TreeNode(rootVal);
        
        // Step 2: Find root's position in inorder
        int rootPos = mp[rootVal];
        
        // Step 3: Calculate number of nodes in left subtree
        int leftSize = rootPos - inStart;

        // Step 4: Build left subtree
        // - Start from beginning of postorder
        // - Take leftSize elements
        root->left = helper(inorder, postorder, mp, 
                          inStart,                // Start from beginning of inorder
                          rootPos - 1,            // End before root in inorder
                          postStart,              // Start from beginning of postorder
                          postStart + leftSize - 1); // Take leftSize elements
        
        // Step 5: Build right subtree
        // - Start after left subtree in postorder
        // - Take remaining elements (excluding root)
        root->right = helper(inorder, postorder, mp, 
                           rootPos + 1,           // Start after root in inorder
                           inEnd,                 // Take remaining elements
                           postStart + leftSize,  // Start after left subtree
                           postEnd - 1);          // Take remaining elements (excluding root)

        return root;
    }
};

/*
Simple Memory Aid:

1. For Left Subtree:
   - Inorder: [inStart, rootPos-1] (everything before root)
   - Postorder: [postStart, postStart+leftSize-1] (take leftSize elements)

2. For Right Subtree:
   - Inorder: [rootPos+1, inEnd] (everything after root)
   - Postorder: [postStart+leftSize, postEnd-1] (remaining elements, excluding root)

3. Key Formula:
   leftSize = rootPos - inStart
   (number of elements in left subtree)

4. Visual Example:
   inorder = [9,3,15,20,7]
   postorder = [9,15,7,20,3]
   
   For root = 3:
   - leftSize = 1 (3's position - start)
   - Left subtree: [9]
   - Right subtree: [15,20,7]
   - Final Tree:
        3
       / \
      9  20
         / \
        15  7

5. Key Differences from Preorder-Inorder:
   - Root is at end of postorder (not start)
   - Right subtree ends at postEnd-1 (excluding root)
   - Left subtree size calculation is same
   - Inorder traversal handling is same
*/
