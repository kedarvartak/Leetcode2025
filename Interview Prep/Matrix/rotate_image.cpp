#include <vector>
#include <algorithm> // For std::swap and std::reverse
#include <iostream>  // For main example

/*
Problem: Rotate Image (LeetCode 48)
You are given an n x n 2D matrix representing an image. Rotate the image by 90 degrees
clockwise. You have to rotate the image in-place, which means you have to modify the
input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]
Visual:
1 2 3   ->   7 4 1
4 5 6   ->   8 5 2
7 8 9   ->   9 6 3

Example 2:
Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

Concept (Transpose and Reverse Rows Method for In-Place Rotation):
The most common and intuitive in-place method to achieve a 90-degree clockwise rotation
of an N x N matrix involves two main steps:

1. Transpose the Matrix:
   - The transpose of a matrix is obtained by flipping the matrix over its main diagonal.
     This means swapping `matrix[i][j]` with `matrix[j][i]` for all `i` and `j` where `j < i`
     (or `j > i` to process elements on one side of the diagonal once).
   - Effect: An element at `(row, col)` moves to `(col, row)`.

2. Reverse Each Row:
   - After transposing the matrix, iterate through each row and reverse its elements.
   - Effect: An element in the transposed matrix at `(new_row, new_col)` moves to
     `(new_row, N - 1 - new_col)` within that row.

Combining these two steps results in a 90-degree clockwise rotation.
   Original `(row, col)` -> Transpose to `(col, row)` -> Reverse row `col` gives final position
   `(col, N - 1 - row)`, which is the correct mapping for a 90-degree clockwise rotation.

How the Code Works:

1. Get Matrix Size:
   - `int n = matrix.size();`
     `n` represents the number of rows (and columns, as it's an N x N matrix).
     The problem constraints usually state `n >= 1`, so an empty matrix check might not be
     strictly necessary based on LeetCode constraints, but good practice for general functions.

2. Step 1: Transpose the Matrix
   - `for(int i = 0; i < n; i++) { ... }`:
     The outer loop iterates from the first row (`i=0`) to the last row (`i=n-1`).
   - `for(int j = 0; j < i; j++) { ... }`:
     The inner loop iterates from the first column (`j=0`) up to, but not including,
     the current row index `i`. This is crucial: `j < i` ensures that we only process
     elements in the lower triangle of the matrix (below the main diagonal).
     Swapping `matrix[i][j]` with `matrix[j][i]` for these elements effectively swaps
     each corresponding pair across the diagonal exactly once. For example, if `i=1, j=0`,
     `matrix[1][0]` is swapped with `matrix[0][1]`. We don't need `j > i` because that would
     re-swap them.
   - `std::swap(matrix[i][j], matrix[j][i]);`:
     Swaps the element at `(i,j)` with the element at `(j,i)`.

3. Step 2: Reverse Each Row
   - `for(int i = 0; i < n; i++) { ... }`:
     This loop iterates through each row of the now-transposed matrix, from row `0` to `n-1`.
   - `std::reverse(matrix[i].begin(), matrix[i].end());`:
     `matrix[i]` represents the i-th row (which is a `std::vector<int>`).
     `std::reverse` is a standard algorithm that reverses the elements in the range
     specified by the iterators `matrix[i].begin()` (start of the row) and
     `matrix[i].end()` (one past the end of the row).

Visual Dry Run Example: matrix = [[1,2,3],[4,5,6],[7,8,9]], n=3

Initial Matrix:
1 2 3
4 5 6
7 8 9

Step 1: Transpose
- i=0: inner loop `j < 0` doesn't run.
- i=1:
  - j=0 (`j < 1`): `swap(matrix[1][0], matrix[0][1])` -> `swap(4, 2)`
    Matrix: [[1,4,3],[2,5,6],[7,8,9]]
- i=2:
  - j=0 (`j < 2`): `swap(matrix[2][0], matrix[0][2])` -> `swap(7, 3)`
    Matrix: [[1,4,7],[2,5,6],[3,8,9]]
  - j=1 (`j < 2`): `swap(matrix[2][1], matrix[1][2])` -> `swap(8, 6)`
    Matrix: [[1,4,7],[2,5,8],[3,6,9]]

Matrix after Transposition:
1 4 7
2 5 8
3 6 9

Step 2: Reverse Each Row
- i=0: `reverse(matrix[0].begin(), matrix[0].end())` -> `reverse([1,4,7])` -> `[7,4,1]`
  Matrix: [[7,4,1],[2,5,8],[3,6,9]]
- i=1: `reverse(matrix[1].begin(), matrix[1].end())` -> `reverse([2,5,8])` -> `[8,5,2]`
  Matrix: [[7,4,1],[8,5,2],[3,6,9]]
- i=2: `reverse(matrix[2].begin(), matrix[2].end())` -> `reverse([3,6,9])` -> `[9,6,3]`
  Matrix: [[7,4,1],[8,5,2],[9,6,3]]

Final Rotated Matrix:
7 4 1
8 5 2
9 6 3

Algorithm Properties:

1. Time Complexity: O(N*N) (or O(M) where M is the total number of cells)
   - Transposition: The nested loops iterate roughly (N*N)/2 times for the swaps. Each swap is O(1).
   - Reversing rows: There are N rows, and reversing each row takes O(N) time.
     So, this step is N * O(N) = O(N*N).
   - Total time complexity is O(N*N) + O(N*N) = O(N*N).

2. Space Complexity: O(1)
   - The rotation is performed in-place. No extra data structures proportional to the
     matrix size are allocated.

Edge Cases:
- 1x1 Matrix: `n=1`.
  - Transpose loop: `i=0`, inner `j<0` doesn't run. No swaps.
  - Reverse loop: `i=0`, `reverse(matrix[0])` (a single element vector) does nothing.
  - Correctly leaves the 1x1 matrix unchanged.
- Empty Matrix (`n=0`): If allowed (LeetCode constraints usually `n >= 1`), `matrix.size()` is 0.
  The loops won't execute. Code is safe.

Alternative Approaches (Briefly):
- Layer-by-Layer Rotation: Iterate from the outermost square layer of the matrix inwards.
  For each layer, perform a cyclic swap of the four corresponding elements (top -> right, right -> bottom, etc.).
  This is also O(N*N) time and O(1) space but can be more complex to get the indices right for the cyclic swaps.
- Using an Auxiliary Matrix: Create a new N x N matrix. For each element `matrix[row][col]`
  in the original, place it at `new_matrix[col][N-1-row]` in the new matrix.
  Time: O(N*N), Space: O(N*N).

The transpose-and-reverse method is generally favored for its conceptual simplicity and ease of implementation for in-place rotation.
*/

class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0) { // Handles empty matrix, though constraints usually n>=1
            return;
        }

        // Step 1: Transpose the matrix
        // Swap matrix[i][j] with matrix[j][i]
        // We iterate j from 0 to i-1 to only process elements below the main diagonal once.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Step 2: Reverse each row
        for (int i = 0; i < n; i++) {
            std::reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

// Helper function to print the matrix (for testing)
// void printMatrix(const std::vector<std::vector<int>>& matrix) {
//     if (matrix.empty()) {
//         std::cout << "[]" << std::endl;
//         return;
//     }
//     std::cout << "[";
//     for (size_t i = 0; i < matrix.size(); ++i) {
//         std::cout << "[";
//         for (size_t j = 0; j < matrix[i].size(); ++j) {
//             std::cout << matrix[i][j] << (j == matrix[i].size() - 1 ? "" : ",");
//         }
//         std::cout << "]" << (i == matrix.size() - 1 ? "" : ",");
//         if (i < matrix.size() - 1) std::cout << std::endl << " "; // For better multi-line printing
//     }
//     std::cout << "]" << std::endl;
// }

// int main() {
//     Solution sol;

//     // Test Case 1
//     std::vector<std::vector<int>> matrix1 = {{1,2,3},{4,5,6},{7,8,9}};
//     std::cout << "Original Matrix 1:" << std::endl;
//     // printMatrix(matrix1);
//     sol.rotate(matrix1);
//     std::cout << "Rotated Matrix 1:" << std::endl;
//     // printMatrix(matrix1); // Expected: [[7,4,1],[8,5,2],[9,6,3]]
//     std::cout << std::endl;

//     // Test Case 2
//     std::vector<std::vector<int>> matrix2 = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
//     std::cout << "Original Matrix 2:" << std::endl;
//     // printMatrix(matrix2);
//     sol.rotate(matrix2);
//     std::cout << "Rotated Matrix 2:" << std::endl;
//     // printMatrix(matrix2); // Expected: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
//     std::cout << std::endl;

//     // Test Case 3: 1x1 matrix
//     std::vector<std::vector<int>> matrix3 = {{10}};
//     std::cout << "Original Matrix 3:" << std::endl;
//     // printMatrix(matrix3);
//     sol.rotate(matrix3);
//     std::cout << "Rotated Matrix 3:" << std::endl;
//     // printMatrix(matrix3); // Expected: [[10]]
//     std::cout << std::endl;

//     // Test Case 4: 2x2 matrix
//     std::vector<std::vector<int>> matrix4 = {{1,2},{3,4}};
//     std::cout << "Original Matrix 4:" << std::endl;
//     // printMatrix(matrix4);
//     sol.rotate(matrix4);
//     std::cout << "Rotated Matrix 4:" << std::endl;
//     // printMatrix(matrix4); // Expected: [[3,1],[4,2]]
//     std::cout << std::endl;

//     // Test Case 5: Empty matrix (if supported, though constraints usually N>=1)
//     // std::vector<std::vector<int>> matrix5 = {};
//     // std::cout << "Original Matrix 5:" << std::endl;
//     // printMatrix(matrix5);
//     // sol.rotate(matrix5);
//     // std::cout << "Rotated Matrix 5:" << std::endl;
//     // printMatrix(matrix5); // Expected: []

//     return 0;
// }