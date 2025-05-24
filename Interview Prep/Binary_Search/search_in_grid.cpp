#include <vector>
#include <iostream> // For main example

/*
Problem: Search a 2D Matrix (LeetCode 74)

You are given an m x n integer matrix `matrix` with the following two properties:
1. Each row is sorted in non-decreasing order.
2. The first integer of each row is greater than the last integer of the previous row.

Given an integer `target`, return `true` if `target` is in `matrix` or `false` otherwise.
You must write a solution in O(log(m * n)) time complexity.

Example 1:
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true

Example 2:
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false

Concept (Binary Search on a "Flattened" Conceptual Array):
The two properties of the matrix are key:
1. Rows are sorted.
2. The first element of row `i` is greater than the last element of row `i-1`.
These properties together imply that if we were to "flatten" the 2D matrix into a 1D array
by concatenating its rows, the resulting 1D array would be sorted.

Example: [[1,3,5], [10,11,16], [23,30,34]] conceptually becomes [1,3,5,10,11,16,23,30,34].

Since we have a conceptually sorted 1D array of size `rows * cols`, we can perform a
standard binary search on it. The main challenge is to map a 1D index `mid` (from the
binary search) back to its corresponding 2D `(row, col)` coordinates in the original matrix.

Mapping 1D Index to 2D Coordinates:
If the matrix has `cols` columns:
- `row = mid / cols` (integer division gives the row index)
- `col = mid % cols` (modulo operation gives the column index)

How the Code Works:

1. Handle Empty Matrix:
   - `if (matrix.empty() || matrix[0].empty()) { return false; }`
     Checks if the matrix itself is empty or if it contains rows but those rows are empty.
     If so, the target cannot be present.

2. Initialization:
   - `int rows = matrix.size();`: Get the number of rows.
   - `int cols = matrix[0].size();`: Get the number of columns.
   - `int left = 0;`: `left` pointer for binary search, representing the start of the
     conceptual 1D array (index 0).
   - `int right = rows * cols - 1;`: `right` pointer for binary search, representing the end
     of the conceptual 1D array (index `rows * cols - 1`).

3. Binary Search Loop:
   - `while (left <= right)`: The loop continues as long as the search space (`[left, right]`)
     is valid.
   - `int mid = left + (right - left) / 2;`: Calculate the middle index of the conceptual 1D array.
     This form helps prevent potential integer overflow compared to `(left + right) / 2`, though the original code uses the latter.
     (The provided solution has `int mid = (left + right)/2;`)
   - Convert 1D `mid` to 2D `(row, col)`:
     - `int row = mid / cols;`
     - `int col = mid % cols;`
   - `int num = matrix[row][col];`: Retrieve the element at these 2D coordinates.

4. Comparison and Search Space Adjustment:
   - `if (num == target)`:
     - If `num` is the `target`, it's found, so return `true`.
   - `else if (num < target)`:
     - If `num` is less than `target`, the `target` (if it exists) must be in the "upper" half
       of the conceptual 1D array (i.e., at indices greater than `mid`).
     - `left = mid + 1;`: Adjust the `left` pointer.
   - `else` (i.e., `num > target`):
     - If `num` is greater than `target`, the `target` (if it exists) must be in the "lower" half.
     - `right = mid - 1;`: Adjust the `right` pointer.

5. Target Not Found:
   - `return false;`: If the loop completes without finding the `target`, it means the `target`
     is not in the matrix.

Visual Dry Run Example: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
rows = 3, cols = 4. Total elements = 12.
left = 0, right = 11.

1. left=0, right=11: mid=(0+11)/2 = 5.
   row = 5/4 = 1. col = 5%4 = 1.
   num = matrix[1][1] = 11.
   11 > 3 (target). So, right = mid - 1 = 5 - 1 = 4.
   (left=0, right=4)

2. left=0, right=4: mid=(0+4)/2 = 2.
   row = 2/4 = 0. col = 2%4 = 2.
   num = matrix[0][2] = 5.
   5 > 3 (target). So, right = mid - 1 = 2 - 1 = 1.
   (left=0, right=1)

3. left=0, right=1: mid=(0+1)/2 = 0.
   row = 0/4 = 0. col = 0%4 = 0.
   num = matrix[0][0] = 1.
   1 < 3 (target). So, left = mid + 1 = 0 + 1 = 1.
   (left=1, right=1)

4. left=1, right=1: mid=(1+1)/2 = 1.
   row = 1/4 = 0. col = 1%4 = 1.
   num = matrix[0][1] = 3.
   3 == 3 (target). Return true.

Algorithm Properties:

- Time Complexity: O(log(rows * cols))
  - The binary search is performed on `rows * cols` elements.
- Space Complexity: O(1)
  - The search is done in-place with a few variables.

Edge Cases:
- Empty matrix: `matrix = []` or `matrix = [[]]`. Handled by the initial check.
- 1x1 matrix: `matrix = [[5]], target = 5` (true), `target = 2` (false).
- Single row matrix: `matrix = [[1,2,3,4]], target = 3`.
- Single column matrix: `matrix = [[1],[2],[3]], target = 2`.
- Target smaller than all elements or larger than all elements.

Correctness:
The method's correctness hinges on the matrix properties ensuring the conceptual 1D array
is sorted. If these properties didn't hold, simple binary search on the "flattened"
representation wouldn't guarantee finding the element or correctly determining its absence.
*/

class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) { // Check for empty matrix or matrix with empty rows
            return false;
        }

        int rows = matrix.size();
        int cols = matrix[0].size();

        int left = 0;
        // The conceptual 1D array has indices from 0 to (rows*cols - 1)
        int right = rows * cols - 1; 
        
        while (left <= right) {
            // int mid = (left + right) / 2; // Original calculation
            int mid = left + (right - left) / 2; // Preferred to avoid potential overflow

            // Convert 1D mid-point to 2D matrix coordinates
            int row = mid / cols;
            int col = mid % cols;
            int num = matrix[row][col];

            if (num == target) {
                return true; // Target found
            } else if (num < target) {
                left = mid + 1; // Target might be in the "upper" half
            } else { // num > target
                right = mid - 1; // Target might be in the "lower" half
            }
        }

        return false; // Target not found after searching the entire conceptual array
    }
};

// int main() {
//     Solution sol;
//     std::vector<std::vector<int>> matrix;
//     int target;

//     // Test Case 1: Target found
//     matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
//     target = 3;
//     std::cout << "Matrix1, Target 3: Expected: true, Got: " << sol.searchMatrix(matrix, target) << std::endl;

//     // Test Case 2: Target not found
//     target = 13;
//     std::cout << "Matrix1, Target 13: Expected: false, Got: " << sol.searchMatrix(matrix, target) << std::endl;

//     // Test Case 3: Target is the first element
//     target = 1;
//     std::cout << "Matrix1, Target 1: Expected: true, Got: " << sol.searchMatrix(matrix, target) << std::endl;

//     // Test Case 4: Target is the last element
//     target = 60;
//     std::cout << "Matrix1, Target 60: Expected: true, Got: " << sol.searchMatrix(matrix, target) << std::endl;

//     // Test Case 5: Target smaller than all elements
//     target = 0;
//     std::cout << "Matrix1, Target 0: Expected: false, Got: " << sol.searchMatrix(matrix, target) << std::endl;

//     // Test Case 6: Target larger than all elements
//     target = 100;
//     std::cout << "Matrix1, Target 100: Expected: false, Got: " << sol.searchMatrix(matrix, target) << std::endl;
    
//     // Test Case 7: Single element matrix, target found
//     matrix = {{5}};
//     target = 5;
//     std::cout << "Matrix {{5}}, Target 5: Expected: true, Got: " << sol.searchMatrix(matrix, target) << std::endl;

//     // Test Case 8: Single element matrix, target not found
//     target = 10;
//     std::cout << "Matrix {{5}}, Target 10: Expected: false, Got: " << sol.searchMatrix(matrix, target) << std::endl;

//     // Test Case 9: Single row matrix
//     matrix = {{1,2,3,4,5,6}};
//     target = 4;
//     std::cout << "Matrix {{1,2,3,4,5,6}}, Target 4: Expected: true, Got: " << sol.searchMatrix(matrix, target) << std::endl;
//     target = 7;
//     std::cout << "Matrix {{1,2,3,4,5,6}}, Target 7: Expected: false, Got: " << sol.searchMatrix(matrix, target) << std::endl;

//     // Test Case 10: Single column matrix
//     matrix = {{1},{2},{3},{4},{5}};
//     target = 3;
//     std::cout << "Matrix {{1},{2},{3},{4},{5}}, Target 3: Expected: true, Got: " << sol.searchMatrix(matrix, target) << std::endl;
//     target = 0;
//     std::cout << "Matrix {{1},{2},{3},{4},{5}}, Target 0: Expected: false, Got: " << sol.searchMatrix(matrix, target) << std::endl;

//     // Test Case 11: Empty matrix
//     matrix = {};
//     target = 5;
//     std::cout << "Matrix {}, Target 5: Expected: false, Got: " << sol.searchMatrix(matrix, target) << std::endl;

//     // Test Case 12: Matrix with empty row (should be handled by matrix[0].empty())
//     matrix = {{}}; // This is an edge case: a matrix with one row, and that row is empty.
//     target = 5;
//     std::cout << "Matrix {{}}, Target 5: Expected: false, Got: " << sol.searchMatrix(matrix, target) << std::endl;
    
//     // Test Case 13: A larger matrix
//     matrix = {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
//     // This matrix is sorted row-wise and column-wise, but does not satisfy the "first of next > last of prev" condition for this specific problem.
//     // Let's use a valid one for LeetCode 74.
//     matrix = {{1,2,3},{4,5,6},{7,8,9}};
//     target = 5;
//     std::cout << "Matrix {{1,2,3},{4,5,6},{7,8,9}}, Target 5: Expected: true, Got: " << sol.searchMatrix(matrix, target) << std::endl;
//     target = 10;
//     std::cout << "Matrix {{1,2,3},{4,5,6},{7,8,9}}, Target 10: Expected: false, Got: " << sol.searchMatrix(matrix, target) << std::endl;


//     return 0;
// }