class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size();
        int countZeros = 0;
        
        for (int num : arr) {
            if (num == 0) countZeros++;
        }
        
        int i = n - 1;
        int j = n + countZeros - 1; 
        
        while (i >= 0) {
            if (j < n) {
                arr[j] = arr[i]; 
            }
            j--; 
            
            if (arr[i] == 0) { 
                if (j < n) {
                    arr[j] = 0;
                }
                j--; 
            }
            i--; 
        }
    }
};
