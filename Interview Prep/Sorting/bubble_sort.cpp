#include <vector>
#include <iostream>
#include <algorithm> // For std::swap and std::is_sorted

/*
Bubble Sort Algorithm:

Concept:
Bubble Sort is a simple comparison-based sorting algorithm. It repeatedly steps through the list,
compares adjacent elements, and swaps them if they are in the wrong order. The pass through
the list is repeated until no swaps are needed, which indicates that the list is sorted.
The largest (or smallest, depending on sort order) elements "bubble" to their correct position
at the end (or beginning) of the array with each pass.

How it Works:
1. Outer Loop: Iterates from the beginning of the array up to n-1 times (where n is the array size).
   After each iteration of the outer loop, the largest unsorted element is guaranteed to be in its
   final sorted position at the end of the unsorted part of the array.
2. Inner Loop: In each pass of the outer loop, the inner loop iterates from the first element up to
   the last unsorted element. It compares `array[j]` with `array[j+1]`.
3. Swap: If `array[j] > array[j+1]` (for ascending order), these two elements are swapped.
4. Optimization: If a pass through the inner loop completes without any swaps, the array is already
   sorted, and the algorithm can terminate early.

Visual Example (Ascending Order):
Array: [5, 1, 4, 2, 8]

Pass 1:
- (5, 1) -> swap -> [1, 5, 4, 2, 8]
- (5, 4) -> swap -> [1, 4, 5, 2, 8]
- (5, 2) -> swap -> [1, 4, 2, 5, 8]
- (5, 8) -> no swap -> [1, 4, 2, 5, 8] (8 is in its correct place)
  Inner loop ran 4 times. One swap occurred. Array: [1, 4, 2, 5, 8]

Pass 2:
- (1, 4) -> no swap -> [1, 4, 2, 5, 8]
- (4, 2) -> swap -> [1, 2, 4, 5, 8]
- (4, 5) -> no swap -> [1, 2, 4, 5, 8] (5 is in its correct place)
  Inner loop ran 3 times. One swap occurred. Array: [1, 2, 4, 5, 8]

Pass 3:
- (1, 2) -> no swap -> [1, 2, 4, 5, 8]
- (2, 4) -> no swap -> [1, 2, 4, 5, 8] (4 is in its correct place)
  Inner loop ran 2 times. No swaps occurred. Array is sorted. Algorithm can terminate early due to optimization.

Final Sorted Array: [1, 2, 4, 5, 8]

Time Complexity:
- Worst Case: O(n^2) - When the array is in reverse order.
- Average Case: O(n^2) - When elements are in a jumbled order.
- Best Case: O(n) - When the array is already sorted, and the optimization (no swaps flag) is used.
  (The outer loop runs once, and the inner loop runs n-1 times).

Space Complexity:
- O(1) - It's an in-place sorting algorithm; it only requires a constant amount of extra space
  for temporary variables during swaps.

Stability:
- Bubble Sort is a stable sorting algorithm. This means that elements with equal values
  maintain their relative order in the sorted output.
  (e.g., if you have (5,a) and (5,b) where a appears before b, they will remain in that order).

When to Use / Not Use:
- Use: Mostly for educational purposes due to its simplicity.
       It can be practical for very small datasets or lists that are already nearly sorted
       (where its O(n) best-case performance can be achieved with the optimization).
- Not Use: For large datasets, as its O(n^2) average and worst-case complexity makes it very inefficient
         compared to algorithms like Merge Sort, Quick Sort, or Heap Sort (which are O(n log n)).

Optimization (Flag for no swaps):
- A boolean flag can be used to track if any swaps occurred during a pass of the inner loop.
- If no swaps occur, it means the array is sorted, and the algorithm can terminate early,
  leading to the O(n) best-case time complexity.
*/

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) {
        return; // Already sorted or empty
    }

    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        // Last i elements are already in place, so inner loop goes up to n-1-i
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped by inner loop, then break
        // This means the array is sorted.
        if (!swapped) {
            break;
        }
    }
}

// Helper function to print the vector
void printVector(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

// int main() {
//     std::vector<int> arr1 = {5, 1, 4, 2, 8};
//     std::cout << "Original array 1: ";
//     printVector(arr1);
//     bubbleSort(arr1);
//     std::cout << "Sorted array 1:   ";
//     printVector(arr1);
//     std::cout << "Is sorted: " << (std::is_sorted(arr1.begin(), arr1.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr2 = {64, 34, 25, 12, 22, 11, 90};
//     std::cout << "Original array 2: ";
//     printVector(arr2);
//     bubbleSort(arr2);
//     std::cout << "Sorted array 2:   ";
//     printVector(arr2);
//     std::cout << "Is sorted: " << (std::is_sorted(arr2.begin(), arr2.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr3 = {1, 2, 3, 4, 5};
//     std::cout << "Original array 3 (already sorted): ";
//     printVector(arr3);
//     bubbleSort(arr3);
//     std::cout << "Sorted array 3:   ";
//     printVector(arr3);
//     std::cout << "Is sorted: " << (std::is_sorted(arr3.begin(), arr3.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr4 = {5, 4, 3, 2, 1};
//     std::cout << "Original array 4 (reverse sorted): ";
//     printVector(arr4);
//     bubbleSort(arr4);
//     std::cout << "Sorted array 4:   ";
//     printVector(arr4);
//     std::cout << "Is sorted: " << (std::is_sorted(arr4.begin(), arr4.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr5 = {};
//     std::cout << "Original array 5 (empty): ";
//     printVector(arr5);
//     bubbleSort(arr5);
//     std::cout << "Sorted array 5:   ";
//     printVector(arr5);
//     std::cout << "Is sorted: " << (std::is_sorted(arr5.begin(), arr5.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr6 = {10};
//     std::cout << "Original array 6 (single element): ";
//     printVector(arr6);
//     bubbleSort(arr6);
//     std::cout << "Sorted array 6:   ";
//     printVector(arr6);
//     std::cout << "Is sorted: " << (std::is_sorted(arr6.begin(), arr6.end()) ? "Yes" : "No") << std::endl << std::endl;

//     return 0;
// }
