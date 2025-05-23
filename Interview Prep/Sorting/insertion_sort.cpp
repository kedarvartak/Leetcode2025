#include <vector>
#include <iostream>
#include <algorithm> // For std::is_sorted, and std::swap (though not directly used by typical insertion sort key-shifting)

/*
Insertion Sort Algorithm:

Concept:
Insertion Sort is a simple comparison-based sorting algorithm that builds the final sorted array
(or list) one item at a time. It is much less efficient on large lists than more advanced
algorithms such as quicksort, heapsort, or merge sort, but it provides several advantages:
- Simple implementation.
- Efficient for (quite) small data sets.
- Efficient for data sets that are already substantially sorted: if each element is not more than k
  places away from its sorted position, insertion sort runs in O(nk) time.
- More efficient in practice than most other simple quadratic (i.e., O(n^2)) algorithms such as
  selection sort or bubble sort.
- Stable (does not change the relative order of elements with equal keys).
- In-place (only requires a constant amount O(1) of additional memory space).
- Online (can sort a list as it receives it).

How it Works:
1. Iterate from arr[1] to arr[n-1] (the first element arr[0] is considered sorted by itself).
2. For each element arr[i] (let's call it the `key`):
   a. Compare `key` with the elements in the sorted sub-array arr[0...i-1] by iterating backwards
      from arr[i-1] down to arr[0] (or until an element smaller than or equal to `key` is found).
   b. Shift all the elements in the sorted sub-array that are greater than the `key` one position
      to the right to make space for the `key`.
   c. Insert the `key` into its correct position in the sorted sub-array.

Visual Example (Ascending Order):
Array: [5, 1, 4, 2, 8]

Iteration 1 (i=1, key=arr[1]=1):
  - Sorted sub-array: [5]
  - `key = 1`. Compare with `arr[0]=5`.
  - `5 > 1`, so shift 5 to the right: `[_, 5, 4, 2, 8]`
  - Insert 1 at index 0: `[1, 5, 4, 2, 8]`
  - Sorted sub-array is now [1, 5]

Iteration 2 (i=2, key=arr[2]=4):
  - Sorted sub-array: [1, 5]
  - `key = 4`. Compare with `arr[1]=5`.
  - `5 > 4`, so shift 5 to the right: `[1, _, 5, 2, 8]`
  - Compare `key=4` with `arr[0]=1`.
  - `1 < 4`, so 4 is inserted at index 1 (after 1).
  - Insert 4 at index 1: `[1, 4, 5, 2, 8]`
  - Sorted sub-array is now [1, 4, 5]

Iteration 3 (i=3, key=arr[3]=2):
  - Sorted sub-array: [1, 4, 5]
  - `key = 2`. Compare with `arr[2]=5`.
  - `5 > 2`, shift 5: `[1, 4, _, 5, 8]`
  - Compare `key=2` with `arr[1]=4`.
  - `4 > 2`, shift 4: `[1, _, 4, 5, 8]`
  - Compare `key=2` with `arr[0]=1`.
  - `1 < 2`, so 2 is inserted at index 1 (after 1).
  - Insert 2 at index 1: `[1, 2, 4, 5, 8]`
  - Sorted sub-array is now [1, 2, 4, 5]

Iteration 4 (i=4, key=arr[4]=8):
  - Sorted sub-array: [1, 2, 4, 5]
  - `key = 8`. Compare with `arr[3]=5`.
  - `5 < 8`, so 8 is already in its correct relative position with respect to the sorted sub-array.
  - No shifts needed. Array remains: `[1, 2, 4, 5, 8]`
  - Sorted sub-array is now [1, 2, 4, 5, 8]

Final Sorted Array: [1, 2, 4, 5, 8]

Algorithm Properties:

1. Time Complexity:
   - Worst Case: O(n^2) - When the array is in reverse sorted order. Each element needs to be compared
     and shifted against all preceding elements.
   - Average Case: O(n^2) - When elements are in a jumbled order.
   - Best Case: O(n) - When the array is already sorted. The inner loop condition (while j >= 0 and arr[j] > key)
     will immediately fail for each element, resulting in only n-1 comparisons.

2. Space Complexity (In-Place):
   - Definition (In-Place Algorithm): An algorithm is in-place if it primarily transforms the input using
     the same storage that holds the input, and the additional space used is constant (O(1)),
     not dependent on the input size.
   - Insertion Sort: Yes, it is an in-place algorithm. It sorts the array by modifying it directly.
     It only requires a single additional memory cell to store the `key` element during comparisons and shifts.
     The space used for loop counters is also constant. Thus, auxiliary space is O(1).

3. Stability (Stable Sort):
   - Definition (Stable Sort): A sorting algorithm is stable if two objects with equal keys appear in the
     same order in the sorted output as they appear in the input data set.
   - Insertion Sort: Yes, it is a stable sorting algorithm. When searching for the correct position for the
     `key`, it stops shifting and inserts the `key` as soon as it finds an element less than or equal to
     the `key`. This means if there are equal elements, the `key` (which came later in the original array)
     will be placed after the existing equal elements in the sorted portion, preserving their relative order.

4. Online Algorithm:
   - Definition (Online Algorithm): An online algorithm can process its input piece-by-piece as it arrives,
     without requiring the entire input to be available from the start.
   - Insertion Sort: Yes, it is an online algorithm. It can sort elements as they are received.
     When a new element arrives, it can be inserted into its correct position within the already sorted
     elements without needing to re-process the entire set or know about future elements.

When to Use / Not Use:
- Use:
    - For small datasets, where its simplicity and low overhead make it faster than more complex O(n log n) algorithms.
    - When the input array is nearly sorted (adaptive behavior leads to O(n) performance).
    - When memory is limited (O(1) space complexity).
    - When new elements are continuously added to a list that needs to be kept sorted (online nature).
- Not Use:
    - For large, unsorted datasets, as its O(n^2) average and worst-case complexity is too slow.

Key Differences: Insertion Sort vs. Bubble Sort (using example [5, 1, 4, 2, 8])

Conceptual Difference:
- Insertion Sort: Builds the sorted list one element at a time by taking an element from the unsorted part
  and inserting it into its correct position in the already sorted part (on its left).
- Bubble Sort: Repeatedly steps through the list, compares adjacent elements, and swaps them if they are in
  the wrong order. In each pass, the largest (or smallest) unsorted element "bubbles" to its final position.

Dry Run Comparison with Array: [5, 1, 4, 2, 8]

Bubble Sort (Pass by Pass):
  Initial: [5, 1, 4, 2, 8]
  Pass 1: Compare (5,1)->swap; (5,4)->swap; (5,2)->swap; (5,8)->no swap. Result: [1, 4, 2, 5, 8] (8 is sorted)
  Pass 2: Compare (1,4)->no swap; (4,2)->swap; (4,5)->no swap. Result: [1, 2, 4, 5, 8] (5 is sorted)
  Pass 3: Compare (1,2)->no swap; (2,4)->no swap. Result: [1, 2, 4, 5, 8] (4 is sorted, no swaps in this pass, so terminates)
  Final: [1, 2, 4, 5, 8]
  Focus: Moves largest unsorted elements to their final positions at the end of the array in each pass.

Insertion Sort (Element by Element into Sorted Sub-array):
  Initial: [5, 1, 4, 2, 8]
  i=1 (key=1): [5] | [1, 4, 2, 8] -> key=1. Shift 5. Insert 1. Result: [1, 5, 4, 2, 8] (Sorted: [1, 5])
  i=2 (key=4): [1, 5] | [4, 2, 8] -> key=4. Shift 5. Insert 4. Result: [1, 4, 5, 2, 8] (Sorted: [1, 4, 5])
  i=3 (key=2): [1, 4, 5] | [2, 8] -> key=2. Shift 5, shift 4. Insert 2. Result: [1, 2, 4, 5, 8] (Sorted: [1, 2, 4, 5])
  i=4 (key=8): [1, 2, 4, 5] | [8] -> key=8. No shifts. Insert 8. Result: [1, 2, 4, 5, 8] (Sorted: [1, 2, 4, 5, 8])
  Final: [1, 2, 4, 5, 8]
  Focus: Builds a sorted sub-array from left to right, inserting each new element into its proper place within this sorted sub-array.

Summary of Differences from Dry Run:
- Operations: Bubble sort uses adjacent swaps. Insertion sort uses shifts to make space and then one insertion.
- Sorted Portion: Bubble sort establishes the correct position of one extreme element (largest/smallest)
  per pass. Insertion sort expands a sorted sub-array from the beginning.
- Comparisons: Bubble sort always compares adjacent elements. Insertion sort compares the current element
  with elements in the sorted sub-array to find its insertion point.
- Adaptivity: Insertion sort is naturally adaptive (performs well on nearly sorted data). Bubble sort can be
  made adaptive with a flag, but its fundamental mechanism of bubbling is less direct for nearly sorted data.
*/

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) {
        return; // Already sorted or empty
    }

    for (int i = 1; i < n; ++i) {
        int key = arr[i]; // The element to be inserted into the sorted portion
        int j = i - 1;    // Start comparing with the element before the key

        // Move elements of arr[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key; // Place the key at after the element just smaller than it.
    }
}

// Helper function to print the vector
void printVector(const std::vector<int>& arr) {
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

// int main() {
//     std::vector<int> arr1 = {5, 1, 4, 2, 8};
//     std::cout << "Original array 1: ";
//     printVector(arr1);
//     insertionSort(arr1);
//     std::cout << "Sorted array 1:   ";
//     printVector(arr1);
//     std::cout << "Is sorted: " << (std::is_sorted(arr1.begin(), arr1.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr2 = {64, 34, 25, 12, 22, 11, 90};
//     std::cout << "Original array 2: ";
//     printVector(arr2);
//     insertionSort(arr2);
//     std::cout << "Sorted array 2:   ";
//     printVector(arr2);
//     std::cout << "Is sorted: " << (std::is_sorted(arr2.begin(), arr2.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr3 = {1, 2, 3, 4, 5};
//     std::cout << "Original array 3 (already sorted): ";
//     printVector(arr3);
//     insertionSort(arr3);
//     std::cout << "Sorted array 3:   ";
//     printVector(arr3);
//     std::cout << "Is sorted: " << (std::is_sorted(arr3.begin(), arr3.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr4 = {5, 4, 3, 2, 1};
//     std::cout << "Original array 4 (reverse sorted): ";
//     printVector(arr4);
//     insertionSort(arr4);
//     std::cout << "Sorted array 4:   ";
//     printVector(arr4);
//     std::cout << "Is sorted: " << (std::is_sorted(arr4.begin(), arr4.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr5 = {};
//     std::cout << "Original array 5 (empty): ";
//     printVector(arr5);
//     insertionSort(arr5);
//     std::cout << "Sorted array 5:   ";
//     printVector(arr5);
//     std::cout << "Is sorted: " << (std::is_sorted(arr5.begin(), arr5.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr6 = {10};
//     std::cout << "Original array 6 (single element): ";
//     printVector(arr6);
//     insertionSort(arr6);
//     std::cout << "Sorted array 6:   ";
//     printVector(arr6);
//     std::cout << "Is sorted: " << (std::is_sorted(arr6.begin(), arr6.end()) ? "Yes" : "No") << std::endl << std::endl;
    
//     // Test with duplicates to show stability
//     std::vector<std::pair<int, char>> arr_pairs = {{5, 'a'}, {2, 'b'}, {5, 'c'}, {1, 'd'}};
//     std::cout << "Original pair array (for stability check): ";
//     for(const auto& p : arr_pairs) std::cout << "(" << p.first << "," << p.second << ") ";
//     std::cout << std::endl;
    
//     // Custom insertion sort for pairs (adapting the logic)
//     // The provided insertionSort is for int, for pairs we'd need a template or specific version.
//     // For demonstration, let's assume a conceptual sort. Actual stability is inherent in the logic.
//     // std::stable_sort(arr_pairs.begin(), arr_pairs.end(), [](const auto& p1, const auto& p2){ return p1.first < p2.first; });
//     // If we were to implement insertion sort for pairs, it would look like:
//     /*
//     for (int i = 1; i < arr_pairs.size(); ++i) {
//         std::pair<int, char> key_pair = arr_pairs[i];
//         int j = i - 1;
//         while (j >= 0 && arr_pairs[j].first > key_pair.first) {
//             arr_pairs[j + 1] = arr_pairs[j];
//             j = j - 1;
//         }
//         arr_pairs[j + 1] = key_pair;
//     }
//     */
//     // After applying such an insertion sort:
//     // Expected if stable: (1,'d'), (2,'b'), (5,'a'), (5,'c') 
//     // If (5,'a') and (5,'c') preserve their order, it's stable.
//     // Insertion sort guarantees this.
//     std::cout << "Pairs conceptually sorted (Insertion Sort is stable): (1,'d'), (2,'b'), (5,'a'), (5,'c')" << std::endl << std::endl;

//     return 0;
// }
