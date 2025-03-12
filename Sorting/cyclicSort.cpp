#include <iostream>
#include <vector>
using namespace std;

void cyclicSort(vector<int>& arr) {
    int i = 0;
    while (i < arr.size()) {
        int correctIndex = arr[i] - 1; // Expected index of arr[i]
        if (arr[i] > 0 && arr[i] <= arr.size() && arr[i] != arr[correctIndex]) {
            swap(arr[i], arr[correctIndex]); // Swap with the correct index
        } else {
            i++; // Move to the next element
        }
    }
}

int main() {
    vector<int> arr = {3, 1, 5, 4, 2};
    cyclicSort(arr);

    cout << "Sorted Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    return 0;
}
