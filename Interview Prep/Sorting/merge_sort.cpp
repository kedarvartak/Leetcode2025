#include <vector>
#include <iostream>
#include <algorithm> // For std::is_sorted

/*
Merge Sort Algorithm:

Concept:
Merge Sort is a highly efficient, comparison-based, divide and conquer sorting algorithm.
Its core idea is to divide the array into smaller sub-arrays, sort these sub-arrays recursively,
and then merge them back together to form a fully sorted array. It guarantees O(n log n)
performance, making it suitable for large datasets.

How it Works (Divide and Conquer Strategy):
1. Divide: If the given array has more than one element, split it into two (approximately) equal halves.
   This is typically done by finding the middle index of the array.
2. Conquer: Recursively sort the two sub-arrays created in the divide step.
   - Call `mergeSort` for the left half.
   - Call `mergeSort` for the right half.
   The recursion continues until the base case is reached: a sub-array with 0 or 1 element,
   which is considered inherently sorted.
3. Combine (Merge): Merge the two now-sorted sub-arrays back into a single, larger, sorted sub-array.
   This is the most critical step. It involves:
   a. Creating temporary arrays to hold the elements of the two sorted sub-arrays.
   b. Comparing elements from these temporary arrays one by one.
   c. Placing the smaller (for ascending order) of the two compared elements into the correct
      position in the original array.
   d. Repeating this process until all elements from both temporary arrays have been copied back
      to the original array in sorted order.

Visual Example (Ascending Order):
Array: [5, 1, 4, 2, 8, 3]

1. Split:
   mergeSort([5, 1, 4, 2, 8, 3])
   -> mergeSort([5, 1, 4]) and mergeSort([2, 8, 3])

   Left Half: mergeSort([5, 1, 4])
     -> mergeSort([5, 1]) and mergeSort([4])
        -> mergeSort([5]) and mergeSort([1])  -> Base cases: [5], [1]
           Merge [5] and [1] -> [1, 5]
     -> Merge [1, 5] and [4] (which is [4])
        - TempL=[1,5], TempR=[4]
        - 1 vs 4 -> take 1. Orig: [1, _, _]
        - 5 vs 4 -> take 4. Orig: [1, 4, _]
        - Remaining 5. Orig: [1, 4, 5]
        Result: [1, 4, 5]

   Right Half: mergeSort([2, 8, 3])
     -> mergeSort([2, 8]) and mergeSort([3])
        -> mergeSort([2]) and mergeSort([8]) -> Base cases: [2], [8]
           Merge [2] and [8] -> [2, 8]
     -> Merge [2, 8] and [3] (which is [3])
        - TempL=[2,8], TempR=[3]
        - 2 vs 3 -> take 2. Orig: [2, _, _]
        - 8 vs 3 -> take 3. Orig: [2, 3, _]
        - Remaining 8. Orig: [2, 3, 8]
        Result: [2, 3, 8]

2. Final Merge:
   Merge [1, 4, 5] and [2, 3, 8]
   - TempL=[1,4,5], TempR=[2,3,8]
   - 1 vs 2 -> take 1. Orig: [1, _, _, _, _, _]
   - 4 vs 2 -> take 2. Orig: [1, 2, _, _, _, _]
   - 4 vs 3 -> take 3. Orig: [1, 2, 3, _, _, _]
   - 4 vs 8 -> take 4. Orig: [1, 2, 3, 4, _, _]
   - 5 vs 8 -> take 5. Orig: [1, 2, 3, 4, 5, _]
   - Remaining 8. Orig: [1, 2, 3, 4, 5, 8]
   Result: [1, 2, 3, 4, 5, 8]

Final Sorted Array: [1, 2, 3, 4, 5, 8]

Algorithm Properties:

1. Time Complexity:
   - Worst Case: O(n log n)
   - Average Case: O(n log n)
   - Best Case: O(n log n)
   Explanation: The process of dividing the array into halves results in `log n` levels of recursion.
   At each level, the `merge` operation processes all `n` elements in total (across all merges at that level).
   Thus, the total time complexity is O(n * log n). This performance is very consistent and not
   dependent on the initial order of the data, unlike some O(n^2) sorts.

2. Space Complexity:
   - Definition (In-Place Algorithm): An algorithm is in-place if it primarily transforms input using
     the same storage that holds the input, and the additional space used is constant (O(1)).
   - Merge Sort: O(n). Merge Sort is typically NOT an in-place algorithm. The `merge` step requires
     auxiliary arrays (or a single auxiliary array of size n) to temporarily store the elements
     from the two sub-arrays being merged. This auxiliary space is proportional to the number of
     elements being merged at each step, leading to O(n) overall auxiliary space.
     (Note: In-place merge algorithms exist but are significantly more complex and may not be stable
     or might have a worse constant factor for time complexity).

3. Stability (Stable Sort):
   - Definition (Stable Sort): A sorting algorithm is stable if it preserves the relative order of
     records with equal keys (values). If two items have the same key, their relative order in the
     input will be the same as their relative order in the sorted output.
   - Merge Sort: Yes, it is a stable sorting algorithm, provided the `merge` operation is implemented
     carefully. When merging two sub-arrays, if an element from the left sub-array and an element
     from the right sub-array have equal values, the element from the left sub-array should be chosen
     first. This ensures that elements that were originally to the left (and thus appeared earlier
     for equal values) remain to the left in the merged output.

4. Online Algorithm:
   - Definition (Online Algorithm): An online algorithm can process its input piece-by-piece as it
     arrives, without having the entire input available from the start.
   - Merge Sort: No, it is not an online algorithm. It is a batch algorithm. The divide-and-conquer
     approach requires the entire dataset (or at least significant portions for each recursive call)
     to be available to perform the splitting and subsequent merging operations. It cannot sort
     elements effectively as they arrive one by one.

When to Use / Not Use:
- Use:
    - For sorting large datasets where O(n log n) time complexity is essential.
    - When stability is a requirement (it's one of the few efficient stable sorts).
    - It's often used in external sorting scenarios (where data doesn't fit in main memory) because
      the merging process can be adapted to work with data on disk.
    - Its performance is predictable and not heavily influenced by the initial data order.
- Not Use:
    - For very small datasets, where simpler O(n^2) algorithms like Insertion Sort might be faster
      due to lower constant overhead factors.
    - In environments with extremely limited memory, as its O(n) auxiliary space requirement can be an issue.
      (Bubble, Insertion, Selection sorts are O(1) space).
    - If an in-place sort with O(n log n) is strictly required (then HeapSort or an in-place QuickSort variant might be considered, though QuickSort isn't stable).

Key Differences from O(n^2) Sorts (Bubble, Insertion, Selection):
- Approach: Merge Sort employs a "Divide and Conquer" paradigm, breaking the problem into smaller, identical
  subproblems, solving them, and combining results. O(n^2) sorts are typically iterative, working on the
  array directly through swaps or element insertions one by one.
- Efficiency: O(n log n) time complexity is asymptotically much better than O(n^2) for large `n`.
- Space: Most simple O(n^2) sorts (Bubble, Insertion, Selection) are in-place (O(1) space). Merge Sort
  requires O(n) auxiliary space for its standard implementation.
- Recursive vs. Iterative: Merge Sort is naturally recursive (though can be implemented iteratively). Most simple
  O(n^2) sorts are iterative.
- Data Movement: Merge Sort copies data to temporary arrays and then back. O(n^2) sorts often involve direct swaps
  or shifts within the original array.
*/

// Helper function to merge two sorted sub-arrays: arr[left...mid] and arr[mid+1...right]
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of the left sub-array
    int n2 = right - mid;    // Size of the right sub-array

    // Create temporary arrays
    std::vector<int> L(n1);
    std::vector<int> R(n2);

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left...right]
    int i = 0; // Initial index of first (left) sub-array
    int j = 0; // Initial index of second (right) sub-array
    int k = left; // Initial index of merged sub-array (in original arr)

    while (i < n1 && j < n2) {
        // For stability: if L[i] == R[j], take from L first.
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Main recursive function that sorts arr[left...right] using merge()
void mergeSortRecursive(std::vector<int>& arr, int left, int right) {
    if (left < right) { // Base case: if left >= right, sub-array has 0 or 1 element
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves recursively
        mergeSortRecursive(arr, left, mid);
        mergeSortRecursive(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Wrapper function to initiate Merge Sort
void mergeSort(std::vector<int>& arr) {
    if (arr.empty()) {
        return;
    }
    mergeSortRecursive(arr, 0, arr.size() - 1);
}

// Helper function to print the vector
void printVector(const std::vector<int>& arr) {
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

// For stability testing
struct Item {
    int value;
    char id;
    bool operator<=(const Item& other) const { // Used for merge condition
        if (value != other.value) return value <= other.value;
        return id <= other.id; // Consistent tie-breaking for testing, though merge relies on value only for stability
    }
     // For std::is_sorted
    bool operator<(const Item& other) const {
        if (value != other.value) return value < other.value;
        return id < other.id; 
    }
};

// void mergeItems(std::vector<Item>& arr, int left, int mid, int right) {
//     int n1 = mid - left + 1;
//     int n2 = right - mid;
//     std::vector<Item> L(n1), R(n2);
//     for(int i=0; i<n1; ++i) L[i] = arr[left + i];
//     for(int j=0; j<n2; ++j) R[j] = arr[mid + 1 + j];
//     int i = 0, j = 0, k = left;
//     while (i < n1 && j < n2) {
//         if (L[i].value <= R[j].value) { // Ensures stability: take from left if values are equal
//             arr[k++] = L[i++];
//         } else {
//             arr[k++] = R[j++];
//         }
//     }
//     while (i < n1) arr[k++] = L[i++];
//     while (j < n2) arr[k++] = R[j++];
// }

// void mergeSortItemsRecursive(std::vector<Item>& arr, int left, int right) {
//     if (left < right) {
//         int mid = left + (right - left) / 2;
//         mergeSortItemsRecursive(arr, left, mid);
//         mergeSortItemsRecursive(arr, mid + 1, right);
//         mergeItems(arr, left, mid, right);
//     }
// }

// void mergeSortItems(std::vector<Item>& items) {
//    if(items.empty()) return;
//    mergeSortItemsRecursive(items, 0, items.size() -1);
// }

// void printItems(const std::vector<Item>& items) {
//     for (const auto& item : items) {
//         std::cout << "(" << item.value << "," << item.id << ") ";
//     }
//     std::cout << std::endl;
// }

// int main() {
//     std::vector<int> arr1 = {5, 1, 4, 2, 8, 3};
//     std::cout << "Original array 1: ";
//     printVector(arr1);
//     mergeSort(arr1);
//     std::cout << "Sorted array 1:   ";
//     printVector(arr1);
//     std::cout << "Is sorted: " << (std::is_sorted(arr1.begin(), arr1.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr2 = {64, 34, 25, 12, 22, 11, 90, 7};
//     std::cout << "Original array 2: ";
//     printVector(arr2);
//     mergeSort(arr2);
//     std::cout << "Sorted array 2:   ";
//     printVector(arr2);
//     std::cout << "Is sorted: " << (std::is_sorted(arr2.begin(), arr2.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr3 = {1, 2, 3, 4, 5};
//     std::cout << "Original array 3 (already sorted): ";
//     printVector(arr3);
//     mergeSort(arr3);
//     std::cout << "Sorted array 3:   ";
//     printVector(arr3);
//     std::cout << "Is sorted: " << (std::is_sorted(arr3.begin(), arr3.end()) ? "Yes" : "No") << std::endl << std::endl;

//     std::vector<int> arr4 = {5, 4, 3, 2, 1};
//     std::cout << "Original array 4 (reverse sorted): ";
//     printVector(arr4);
//     mergeSort(arr4);
//     std::cout << "Sorted array 4:   ";
//     printVector(arr4);
//     std::cout << "Is sorted: " << (std::is_sorted(arr4.begin(), arr4.end()) ? "Yes" : "No") << std::endl << std::endl;

//     // Stability Test
//     // std::cout << "Stability Test for Merge Sort:" << std::endl;
//     // std::vector<Item> items = {{5, 'a'}, {2, 'b'}, {5, 'c'}, {1, 'd'}, {2, 'e'}};
//     // // Expected original order for 5s: (5,a), (5,c). For 2s: (2,b), (2,e)
//     // std::cout << "Original items: ";
//     // printItems(items);
//     // mergeSortItems(items); // You would need to implement mergeSortItems similar to mergeSort for ints
//     // std::cout << "Sorted items:   ";
//     // printItems(items);
//     // // Expected stable sort: (1,d), (2,b), (2,e), (5,a), (5,c)
//     // std::cout << "Is stable sorted (expected): (1,d), (2,b), (2,e), (5,a), (5,c)" << std::endl;
//     // bool stable = true;
//     // if (!(items[2].id == 'b' && items[3].id == 'e')) stable = false; // Check order of 2s
//     // if (!(items[4].id == 'a' && items[5].id == 'c')) stable = false; // Check order of 5s (adjust indices based on final size)
//     // std::cout << "Verified stable (if logic correct): " << (stable ? "Yes" : "No") << std::endl << std::endl;

//     return 0;
// }
