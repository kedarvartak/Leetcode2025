#include <iostream>
#include <vector>
using namespace std;

pair<int, int> partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int lowBoundary = low, mid = low, highBoundary = high;
    while (mid <= highBoundary) {
        if (arr[mid] < pivot) {
            swap(arr[lowBoundary], arr[mid]);
            lowBoundary++;
            mid++;
        } else if (arr[mid] > pivot) {
            swap(arr[mid], arr[highBoundary]);
            highBoundary--;
        } else {
            mid++;
        }
    }
    return {lowBoundary - 1, highBoundary + 1};
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        pair<int, int> bounds = partition(arr, low, high);
        quickSort(arr, low, bounds.first);
        quickSort(arr, bounds.second, high);
    }
}

int main() {
    vector<int> arr = {4, 1, 2, 4, 3, 4, 5, 3, 1};
    quickSort(arr, 0, arr.size() - 1);
    for (int num : arr) {
        cout << num << " ";
    }
    return 0;
}
