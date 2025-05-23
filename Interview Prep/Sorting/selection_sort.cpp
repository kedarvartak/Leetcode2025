#include <vector>
#include <iostream>
#include <algorithm> // For std::is_sorted and std::swap

/*
Selection Sort Algorithm:

Concept:
Selection Sort is an in-place comparison-based sorting algorithm. It divides the input list
into two parts: a sorted sublist of items which is built up from left to right at the front (head)
of the list and a sublist of the remaining unsorted items that occupy the rest of the list.
Initially, the sorted sublist is empty and the unsorted sublist is the entire input list.
The algorithm proceeds by finding the smallest (or largest, depending on sorting order) element
in the unsorted sublist, exchanging (swapping) it with the leftmost unsorted element
(putting it in sorted order), and moving the sublist boundaries one element to the right.

How it Works:
1. Outer Loop: Iterate from the first element (index `i` = 0) to the second to last element (index `i` = n-2).
   The element at index `i` is considered the first element of the current unsorted sub-array.
2. Inner Loop (Find Minimum/Maximum): In each iteration of the outer loop, assume the element at the
   current index `i` is the minimum (or maximum). Iterate from `i+1` to `n-1` to find the actual
   minimum (or maximum) element in the remaining unsorted part of the array.
   Keep track of the index of this minimum/maximum element (`min_idx` or `max_idx`).
3. Swap: After the inner loop finds the minimum/maximum element in the unsorted portion, swap the element
   at `arr[i]` with the element at `arr[min_idx]` (or `arr[max_idx]`).
   This places the smallest (or largest) element of the unsorted part at its correct sorted position.
4. Repeat: The outer loop continues, shrinking the unsorted part by one element in each iteration.

Visual Example (Ascending Order):
Array: [5, 1, 4, 2, 8]

Pass 1 (i=0):
  - Unsorted sub-array: [5, 1, 4, 2, 8]
  - Assume `arr[0]=5` is min. `min_idx = 0`.
  - Scan from `j=1`:
    - `arr[1]=1 < arr[min_idx]=5`. Update `min_idx = 1`.
    - `arr[2]=4 > arr[min_idx]=1`.
    - `arr[3]=2 > arr[min_idx]=1`.
    - `arr[4]=8 > arr[min_idx]=1`.
  - Smallest element is `arr[1]=1` (at `min_idx = 1`).
  - Swap `arr[0]` (5) with `arr[1]` (1).
  - Array: `[1, 5, 4, 2, 8]` (1 is sorted)

Pass 2 (i=1):
  - Sorted: [1], Unsorted: [5, 4, 2, 8]
  - Assume `arr[1]=5` is min. `min_idx = 1`.
  - Scan from `j=2`:
    - `arr[2]=4 < arr[min_idx]=5`. Update `min_idx = 2`.
    - `arr[3]=2 < arr[min_idx]=4`. Update `min_idx = 3`.
    - `arr[4]=8 > arr[min_idx]=2`.
  - Smallest element is `arr[3]=2` (at `min_idx = 3`).
  - Swap `arr[1]` (5) with `arr[3]` (2).
  - Array: `[1, 2, 4, 5, 8]` (1, 2 are sorted)

Pass 3 (i=2):
  - Sorted: [1, 2], Unsorted: [4, 5, 8]
  - Assume `arr[2]=4` is min. `min_idx = 2`.
  - Scan from `j=3`:
    - `arr[3]=5 > arr[min_idx]=4`.
    - `arr[4]=8 > arr[min_idx]=4`.
  - Smallest element is `arr[2]=4` (at `min_idx = 2`). No change in `min_idx`.
  - Swap `arr[2]` (4) with `arr[2]` (4) (no actual change if min is already at `arr[i]`)
  - Array: `[1, 2, 4, 5, 8]` (1, 2, 4 are sorted)

Pass 4 (i=3):
  - Sorted: [1, 2, 4], Unsorted: [5, 8]
  - Assume `arr[3]=5` is min. `min_idx = 3`.
  - Scan from `j=4`:
    - `arr[4]=8 > arr[min_idx]=5`.
  - Smallest element is `arr[3]=5`.
  - Swap `arr[3]` (5) with `arr[3]` (5).
  - Array: `[1, 2, 4, 5, 8]` (1, 2, 4, 5 are sorted)

Outer loop finishes as `i` goes up to `n-2`. The last element `arr[n-1]` will be in place.
Final Sorted Array: [1, 2, 4, 5, 8]

Algorithm Properties:

1. Time Complexity:
   - Worst Case: O(n^2) comparisons, O(n) swaps.
   - Average Case: O(n^2) comparisons, O(n) swaps.
   - Best Case: O(n^2) comparisons, O(n) swaps.
   The number of comparisons is always the same regardless of the initial order of elements because
   the inner loop always iterates through the rest of the unsorted part to find the minimum.
   The number of swaps is at most n-1.

2. Space Complexity (In-Place):
   - Definition (In-Place Algorithm): Uses constant O(1) additional memory space beyond the input storage.
   - Selection Sort: Yes, it is an in-place algorithm. It sorts the array by modifying it directly and
     only requires a few extra variables (for loop indices, `min_idx`), which is O(1) auxiliary space.

3. Stability (Stable Sort):
   - Definition (Stable Sort): Preserves the relative order of records with equal keys.
   - Selection Sort: Generally No, it is not a stable sorting algorithm in its typical implementation.
     When the algorithm swaps the current element with the found minimum element, it can change the
     relative order of identical elements. For example:
     Array: `[(4,a), (4,b), (1,c)]` (sorting by the integer key).
     Pass 1 (i=0): `min_idx` points to `(1,c)`. Swap `arr[0]` (`(4,a)`) with `arr[min_idx]` (`(1,c)`).
     Array becomes: `[(1,c), (4,b), (4,a)]`.
     The relative order of `(4,a)` and `(4,b)` is now `(4,b)` then `(4,a)`, whereas it was `(4,a)` then `(4,b)`.
     Thus, stability is lost. It can be made stable with modifications (e.g., by using a linked list and inserting
     the minimum element, or by shifting elements instead of swapping if the swap would break stability),
     but the standard version is not stable.

4. Online Algorithm:
   - Definition (Online Algorithm): Can process input piece-by-piece as it arrives.
   - Selection Sort: No, it is not an online algorithm. To find the minimum (or maximum) element
     for the current position, it needs to scan the entire remaining unsorted portion of the list.
     It cannot place an element correctly until it has seen all other elements in the unsorted part.

When to Use / Not Use:
- Use:
    - For small datasets, where its simplicity is acceptable.
    - When the cost of swapping elements is very high compared to the cost of comparisons, as Selection
      Sort makes at most O(n) swaps.
    - When memory is limited (O(1) space complexity).
- Not Use:
    - For large datasets due to its O(n^2) time complexity for comparisons.
    - When stability is a requirement (unless modified).

Key Differences: Selection Sort vs. Bubble Sort vs. Insertion Sort

- Selection Sort:
    - Mechanism: Finds the minimum element in the unsorted part and swaps it to the correct sorted position.
    - Swaps: Minimal (O(n)). This is its main advantage in specific scenarios.
    - Comparisons: Always O(n^2).
    - Stability: Not stable.
    - Data Movement: Moves elements over long distances in a single swap.

- Bubble Sort:
    - Mechanism: Compares adjacent elements and swaps them if out of order, causing elements to "bubble" up/down.
    - Swaps: Can be many (O(n^2) in worst case).
    - Comparisons: O(n^2) generally, O(n) in best case (optimized).
    - Stability: Stable.
    - Data Movement: Only adjacent elements are swapped.

- Insertion Sort:
    - Mechanism: Builds a sorted sub-array by taking elements from the unsorted part and inserting them into
      their correct position in the sorted sub-array (by shifting other elements).
    - Swaps (Shifts): Involves shifting multiple elements, can be O(n^2) movements.
    - Comparisons: O(n^2) generally, O(n) in best case (adaptive for nearly sorted data).
    - Stability: Stable.
    - Data Movement: Elements are shifted one position at a time to make space.

Summary of Core Operations:
- Selection Sort: Scans for the smallest/largest, then one swap per pass.
- Bubble Sort: Repeated adjacent comparisons and swaps.
- Insertion Sort: Takes an element, finds its place in sorted part by shifting.
*/

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) {
        return; // Already sorted or empty
    }

    for (int i = 0; i < n - 1; ++i) {
        // Find the minimum element in the unsorted part of the array arr[i..n-1]
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // Swap the found minimum element with the first element of the unsorted part
        // (only if min_idx is different from i to avoid self-swap, though std::swap handles self-swap fine)
        if (min_idx != i) {
            std::swap(arr[i], arr[min_idx]);
        }
    }
}

// Helper function to print the vector
void printVector(const std::vector<int>& arr) {
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

// To represent items for stability testing (e.g., (value, original_index_char))
struct Item {
    int value;
    char id; // To distinguish items with the same value

    bool operator<(const Item& other) const {
        return value < other.value;
    }
};

// void printItems(const std::vector<Item>& items) {
//     for (const auto& item : items) {
//         std::cout << "(" << item.value << "," << item.id << ") ";
//     }
//     std::cout << std::endl;
// }

// void selectionSortItems(std::vector<Item>& items) {
//     int n = items.size();
//     if (n <= 1) return;
//     for (int i = 0; i < n - 1; ++i) {
//         int min_idx = i;
//         for (int j = i + 1; j < n; ++j) {
//             if (items[j] < items[min_idx]) { // Uses Item::operator<
//                 min_idx = j;
//             }
//         }
//         if (min_idx != i) {
//             std::swap(items[i], items[min_idx]);
//         }
//     }
// }

// int main() {
//     std::vector<int> arr1 = {5, 1, 4, 2, 8};
//     std::cout << "Original array 1: ";
//     printVector(arr1);
//     selectionSort(arr1);
//     std::cout << "Sorted array 1:   ";
//     printVector(arr1);
//     std::cout << "Is sorted: " << (std::is_sorted(arr1.begin(), arr1.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr2 = {64, 34, 25, 12, 22, 11, 90};
//     std::cout << "Original array 2: ";
//     printVector(arr2);
//     selectionSort(arr2);
//     std::cout << "Sorted array 2:   ";
//     printVector(arr2);
//     std::cout << "Is sorted: " << (std::is_sorted(arr2.begin(), arr2.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr3 = {1, 2, 3, 4, 5};
//     std::cout << "Original array 3 (already sorted): ";
//     printVector(arr3);
//     selectionSort(arr3);
//     std::cout << "Sorted array 3:   ";
//     printVector(arr3);
//     std::cout << "Is sorted: " << (std::is_sorted(arr3.begin(), arr3.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr4 = {5, 4, 3, 2, 1};
//     std::cout << "Original array 4 (reverse sorted): ";
//     printVector(arr4);
//     selectionSort(arr4);
//     std::cout << "Sorted array 4:   ";
//     printVector(arr4);
//     std::cout << "Is sorted: " << (std::is_sorted(arr4.begin(), arr4.end()) ? "Yes" : "No") << std::endl << std::endl;

//     // Stability Test
//     std::cout << "Stability Test for Selection Sort:" << std::endl;
//     std::vector<Item> items = {{4, 'a'}, {1, 'b'}, {4, 'c'}, {2, 'd'}};
//     // Expected original order for 4s: (4,a), (4,c)
//     std::cout << "Original items: ";
//     // printItems(items);
//     // selectionSortItems(items);
//     std::cout << "Sorted items (manually showing typical non-stable result for selection sort): (1,b), (2,d), (4,c), (4,a) or (1,b), (2,d), (4,a), (4,c)" << std::endl;
//     std::cout << "If (4,a) and (4,c) changed order, it's not stable. Selection sort is typically not stable." << std::endl;
//     std::cout << "Example: [(4,a), (4,b), (1,c)] -> Pass 1 swaps (4,a) with (1,c) -> [(1,c), (4,b), (4,a)]. Order of 4s changed." << std::endl << std::endl;

//     return 0;
// }
