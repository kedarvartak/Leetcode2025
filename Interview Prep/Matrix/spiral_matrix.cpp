#include <vector>
#include <iostream>  // For main example
// #include <algorithm> // Not strictly needed by this specific solution

/*
Problem: Spiral Matrix (LeetCode 54)
Given an m x n matrix, return all elements of the matrix in spiral order.

Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:
Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

Concept (Layer-by-Layer Simulation):
The approach is to simulate the spiral traversal by maintaining boundaries for the current
"layer" of the matrix being processed. These boundaries are top, bottom, left, and right.
In each iteration of a main loop, we traverse the four sides of the current outer layer:

1. Traverse Right: Move from `left` to `right` along the `top` row.
   After traversal, this top row is considered processed, so `top` is incremented.

2. Traverse Down: Move from the new `top` to `bottom` along the `right` column.
   After traversal, this rightmost column is processed, so `right` is decremented.

3. Traverse Left: Move from the new `right` to `left` along the `bottom` row.
   This step is conditional: it only occurs if `top <= bottom` (i.e., if the current layer
   hasn't shrunk to be thinner than one row).
   After traversal, this bottom row is processed, so `bottom` is decremented.

4. Traverse Up: Move from the new `bottom` to `top` along the `left` column.
   This step is also conditional: it only occurs if `left <= right` (i.e., if the current layer
   hasn't shrunk to be narrower than one column).
   After traversal, this leftmost column is processed, so `left` is incremented.

The process repeats as long as `top <= bottom` AND `left <= right`, meaning there are still
valid layers or elements to process.

How the Code Works:

1. Initialization:
   - `std::vector<int> ans;`: An empty vector to store the elements in spiral order.
   - `int n = matrix.size();`: Gets the number of rows.
   - `if (n == 0) return ans;`: Handles the edge case of an empty matrix by returning an empty vector.
   - `int m = matrix[0].size();`: Gets the number of columns (assuming a non-empty matrix due to the previous check).
   - `if (m == 0) return ans;`: Handles the edge case of a matrix with rows but no columns.
   - Boundary Pointers:
     - `int top = 0;`: Index of the topmost row of the current layer.
     - `int left = 0;`: Index of the leftmost column of the current layer.
     - `int bottom = n - 1;`: Index of the bottommost row of the current layer.
     - `int right = m - 1;`: Index of the rightmost column of the current layer.

2. Main Traversal Loop:
   - `while (top <= bottom && left <= right)`:
     The loop continues as long as the top boundary is not below the bottom boundary AND
     the left boundary is not past the right boundary. This condition ensures there's
     at least one row and one column in the current layer to process.

3. Traversing One Layer (Inside the `while` loop):

   a. Traverse Right (Top Row):
      - `for (int i = left; i <= right; ++i) { ans.push_back(matrix[top][i]); }`
        Adds elements from `matrix[top][left]` to `matrix[top][right]` to `ans`.
      - `top++;`
        Moves the top boundary down, as this row has been processed.

   b. Traverse Down (Rightmost Column):
      - `for (int i = top; i <= bottom; ++i) { ans.push_back(matrix[i][right]); }`
        Adds elements from `matrix[top][right]` to `matrix[bottom][right]` to `ans`.
        (Note: `top` here is the updated `top` from the previous step).
      - `right--;`
        Moves the right boundary inwards, as this column has been processed.

   c. Traverse Left (Bottom Row) - Conditional:
      - `if (top <= bottom)`:
        This check is crucial. If `top` has crossed `bottom` (e.g., after processing the top row
        of a single-row remaining layer, `top` increments and might become > `bottom`),
        this part should be skipped to avoid re-processing or errors.
      - `for (int i = right; i >= left; --i) { ans.push_back(matrix[bottom][i]); }`
        Adds elements from `matrix[bottom][right]` to `matrix[bottom][left]` to `ans`.
        (Note: `right` here is the updated `right`).
      - `bottom--;`
        Moves the bottom boundary up.

   d. Traverse Up (Leftmost Column) - Conditional:
      - `if (left <= right)`:
        Similar check. If `left` has crossed `right` (e.g., after processing the right column
        of a single-column remaining layer), this part is skipped.
      - `for (int i = bottom; i >= top; --i) { ans.push_back(matrix[i][left]); }`
        Adds elements from `matrix[bottom][left]` to `matrix[top][left]` to `ans`.
        (Note: `bottom` and `top` are the updated values).
      - `left++;`
        Moves the left boundary inwards.

4. Return Result:
   - `return ans;`: After the loop terminates (boundaries have crossed), `ans` contains all
     elements in spiral order.

Visual Dry Run Example: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Initial: n=3, m=3. top=0, left=0, bottom=2, right=2. ans=[]

Iteration 1 (top=0, left=0, bottom=2, right=2):
- Traverse Right (row 0, col 0 to 2): Add 1, 2, 3. ans=[1,2,3]. top becomes 1.
- Traverse Down (col 2, row 1 to 2): Add 6, 9. ans=[1,2,3,6,9]. right becomes 1.
- Traverse Left (row 2, col 1 to 0) (since top=1 <= bottom=2): Add 8, 7. ans=[1,2,3,6,9,8,7]. bottom becomes 1.
- Traverse Up (col 0, row 1 to 1) (since left=0 <= right=1): Add 4. ans=[1,2,3,6,9,8,7,4]. left becomes 1.

Iteration 2 (top=1, left=1, bottom=1, right=1):
- Traverse Right (row 1, col 1 to 1): Add 5. ans=[1,2,3,6,9,8,7,4,5]. top becomes 2.
- Traverse Down (col 1, row 2 to 1) (since top=2 > bottom=1, this inner loop condition `i <= bottom` (2 <= 1) is false, loop doesn't run).
  Effectively, this step adds nothing. right becomes 0.
- Traverse Left (row 1, col 0 to 1) (Condition `top=2 <= bottom=1` is false). This step is skipped.
  (If it ran, `bottom` would become 0).
- Traverse Up (col 1, row 0 to 2) (Condition `left=1 <= right=0` is false). This step is skipped.
  (If it ran, `left` would become 2).

After top becomes 2, and bottom is 1, `top <= bottom` (2 <= 1) is false.
The main `while` loop condition `top <= bottom && left <= right` will fail.
For example, `top=2, bottom=1, left=1, right=0`. `top <= bottom` is false.
Loop terminates.

Final Result: ans = [1,2,3,6,9,8,7,4,5]

Algorithm Properties:

1. Time Complexity: O(N * M)
   - Where N is the number of rows and M is the number of columns.
   - Each element in the matrix is visited and added to the `ans` vector exactly once.

2. Space Complexity: O(N * M) or O(1) auxiliary
   - O(N * M) is required for the `ans` vector, which stores all elements. This is standard if the problem asks to return the spiral order as a new list.
   - If we only consider auxiliary space (space used besides the output), it's O(1) for the boundary pointers (`top`, `bottom`, `left`, `right`) and loop variables.

Edge Cases:
- Empty Matrix (`matrix = []` or `matrix = [[]]`):
  - `n=0` or `m=0`: Handled by initial checks, returns empty `ans`.
- Single Row Matrix (e.g., `[[1,2,3]]`):
  - `n=1, m=3`. top=0, left=0, bottom=0, right=2.
  - Iteration 1: Right adds [1,2,3]. top=1.
    `top=1 > bottom=0`, so subsequent Traverse Down, Left, Up (within the first full pass of while loop logic) are skipped or their loops don't execute due to `top <= bottom` or `i <= bottom` etc. conditions failing.
    Main `while` loop condition `top <= bottom` (1 <= 0) becomes false. Terminates.
    Correct: `ans = [1,2,3]`.
- Single Column Matrix (e.g., `[[1],[2],[3]]`):
  - `n=3, m=1`. top=0, left=0, bottom=2, right=0.
  - Iteration 1: Right adds [1]. top=1.
    Down adds [2,3]. right=-1.
    Traverse Left: `left=0 <= right=-1` is false. Skipped.
    Traverse Up: `left=0 <= right=-1` is false for the outer conditional. (If `left<=right` check in code is for `if(left <= right)` before the up traversal loop)
    Main `while` loop condition `left <= right` (0 <= -1) becomes false. Terminates.
    Correct: `ans = [1,2,3]`.
- 1x1 Matrix (e.g., `[[5]]`):
  - `n=1, m=1`. top=0, left=0, bottom=0, right=0.
  - Iteration 1: Right adds [5]. top=1.
    `top=1 > bottom=0`. Loop terminates. Correct: `ans = [5]`.

The conditional checks `if (top <= bottom)` before traversing left and `if (left <= right)` before traversing up are crucial for correctly handling matrices that are not square or that shrink into single rows/columns during the traversal, preventing out-of-bounds access or double-counting elements.
*/

class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        std::vector<int> ans;
        if (matrix.empty() || matrix[0].empty()) {
            return ans; // Handle empty matrix or matrix with no columns
        }
        
        int n = matrix.size();    // Number of rows
        int m = matrix[0].size(); // Number of columns
        
        // Initialize pointers for traversal boundaries
        int top = 0, left = 0;
        int bottom = n - 1, right = m - 1;
        
        // Traverse the matrix in spiral order
        while (top <= bottom && left <= right) {

            // 1. Traverse from left to right (top row)
            for (int i = left; i <= right; ++i) {
                ans.push_back(matrix[top][i]);
            }
            top++; // Move the top boundary down
            
            // 2. Traverse from top to bottom (rightmost column)
            for (int i = top; i <= bottom; ++i) {
                ans.push_back(matrix[i][right]);
            }
            right--; // Move the right boundary left
            
            // 3. Traverse from right to left (bottom row)
            // Check if there's still a valid row to traverse (top might have crossed bottom)
            if (top <= bottom) { 
                for (int i = right; i >= left; --i) {
                    ans.push_back(matrix[bottom][i]);
                }
                bottom--; // Move the bottom boundary up
            }
            
            // 4. Traverse from bottom to top (leftmost column)
            // Check if there's still a valid column to traverse (left might have crossed right)
            if (left <= right) {
                for (int i = bottom; i >= top; --i) {
                    ans.push_back(matrix[i][left]);
                }
                left++; // Move the left boundary right
            }
        }
        
        return ans; 
    }
};

// int main() {
//     Solution sol;
//     std::vector<std::vector<int>> matrix;
//     std::vector<int> result;

//     // Test Case 1
//     matrix = {{1,2,3},{4,5,6},{7,8,9}};
//     std::cout << "Matrix 1:" << std::endl;
//     // for(const auto& row : matrix) { for(int x : row) std::cout << x << " "; std::cout << std::endl; }
//     result = sol.spiralOrder(matrix);
//     std::cout << "Spiral Order 1: ";
//     for(int x : result) std::cout << x << " "; // Expected: 1 2 3 6 9 8 7 4 5
//     std::cout << std::endl << std::endl;

//     // Test Case 2
//     matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
//     std::cout << "Matrix 2:" << std::endl;
//     // for(const auto& row : matrix) { for(int x : row) std::cout << x << " "; std::cout << std::endl; }
//     result = sol.spiralOrder(matrix);
//     std::cout << "Spiral Order 2: ";
//     for(int x : result) std::cout << x << " "; // Expected: 1 2 3 4 8 12 11 10 9 5 6 7
//     std::cout << std::endl << std::endl;

//     // Test Case 3: Single Row
//     matrix = {{1,2,3,4,5}};
//     std::cout << "Matrix 3 (Single Row):" << std::endl;
//     result = sol.spiralOrder(matrix);
//     std::cout << "Spiral Order 3: ";
//     for(int x : result) std::cout << x << " "; // Expected: 1 2 3 4 5
//     std::cout << std::endl << std::endl;

//     // Test Case 4: Single Column
//     matrix = {{1},{2},{3},{4},{5}};
//     std::cout << "Matrix 4 (Single Column):" << std::endl;
//     result = sol.spiralOrder(matrix);
//     std::cout << "Spiral Order 4: ";
//     for(int x : result) std::cout << x << " "; // Expected: 1 2 3 4 5
//     std::cout << std::endl << std::endl;

//     // Test Case 5: 1x1 Matrix
//     matrix = {{7}};
//     std::cout << "Matrix 5 (1x1):" << std::endl;
//     result = sol.spiralOrder(matrix);
//     std::cout << "Spiral Order 5: ";
//     for(int x : result) std::cout << x << " "; // Expected: 7
//     std::cout << std::endl << std::endl;

//     // Test Case 6: 2x2 Matrix
//     matrix = {{1,2},{3,4}};
//     std::cout << "Matrix 6 (2x2):" << std::endl;
//     result = sol.spiralOrder(matrix);
//     std::cout << "Spiral Order 6: ";
//     for(int x : result) std::cout << x << " "; // Expected: 1 2 4 3
//     std::cout << std::endl << std::endl;

//     // Test Case 7: Empty matrix
//     matrix = {};
//     std::cout << "Matrix 7 (Empty):" << std::endl;
//     result = sol.spiralOrder(matrix);
//     std::cout << "Spiral Order 7: ";
//     for(int x : result) std::cout << x << " "; // Expected: [] (empty line)
//     std::cout << std::endl << std::endl;

//     // Test Case 8: Matrix with empty row (should be handled by matrix[0].empty())
//     matrix = {{}};
//     std::cout << "Matrix 8 (Empty Row):" << std::endl;
//     result = sol.spiralOrder(matrix);
//     std::cout << "Spiral Order 8: ";
//     for(int x : result) std::cout << x << " "; // Expected: [] (empty line)
//     std::cout << std::endl << std::endl;

//     return 0;
// }