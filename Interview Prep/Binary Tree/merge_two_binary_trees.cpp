class Solution {
public:
    // Recursive DFS Approach
    // Time Complexity: O(min(n1,n2)) where n1 and n2 are number of nodes in trees
    // Space Complexity: O(min(h1,h2)) where h1 and h2 are heights of trees
    TreeNode* helper(TreeNode* root1, TreeNode* root2) {
        /*
        Example Walkthrough:
        Tree 1:        Tree 2:        Result:
             1             2             3
            / \           / \           / \
           3   2         1   3         4   5
          /               \   \       /     \
         5                 4   7     5       7
        
        Step 1: Merge roots (1 + 2 = 3)
        Step 2: Merge left subtrees:
          - root1->left (3) + root2->left (1) = 4
          - root1->left->left (5) + root2->left->left (4) = 9
        Step 3: Merge right subtrees:
          - root1->right (2) + root2->right (3) = 5
          - root1->right->right (null) + root2->right->right (7) = 7
        */

        // Base case: if one tree is empty, return the other
        if (!root1) return root2;
        if (!root2) return root1;

        // Merge current nodes' values
        root1->val += root2->val;

        // Recursively merge left and right subtrees
        root1->left = helper(root1->left, root2->left);
        root1->right = helper(root1->right, root2->right);

        return root1;
    }

    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        // Start the merging process from roots
        return helper(root1, root2);
    }
};

/*
Recursive Approach Explanation:

1. Base Cases:
   - If root1 is NULL, return root2
   - If root2 is NULL, return root1
   - This handles cases where one tree is empty or we reach leaf nodes

2. Recursive Case:
   - For each pair of nodes:
     a. Add their values
     b. Recursively merge left subtrees
     c. Recursively merge right subtrees
     d. Return the merged node

3. Time Complexity: O(min(n1,n2))
   - We only process nodes that exist in both trees
   - n1 and n2 are number of nodes in respective trees
   - We stop when we reach the end of either tree

4. Space Complexity: O(min(h1,h2))
   - h1 and h2 are heights of the trees
   - Space is used by the recursion stack
   - Worst case: O(min(n1,n2)) for skewed trees
   - Best case: O(log min(n1,n2)) for balanced trees

5. Key Points:
   - We modify root1 in-place to create the merged tree
   - If a node exists in one tree but not the other, we keep the existing node
   - The merged tree structure follows the structure of the non-null tree
   - We don't need to create new nodes, just modify existing ones

6. Common Pitfalls:
   - Forgetting to handle NULL cases
   - Not considering different tree structures
   - Creating unnecessary new nodes
   - Not properly handling leaf nodes

7. Edge Cases:
   - Both trees are empty
   - One tree is empty
   - Trees have different structures
   - Trees have different depths
   - Trees have different number of nodes

8. Alternative Approaches:
   - Could create a new tree instead of modifying existing one
   - Could use iterative approach with stack/queue
   - But recursive approach is most elegant and efficient
*/
