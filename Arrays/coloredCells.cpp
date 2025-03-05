class Solution {
public:
    long long coloredCells(int n) {
        return 2LL * n * n - 2 * n + 1;   
    }
};