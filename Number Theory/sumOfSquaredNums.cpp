
class Solution {
public:
    bool judgeSquareSum(int c) {
        for (long long i = 0; i * i <= c; i++) {
            long long remain = c - i * i;
            long long sqrtRemain = sqrt(remain);
            if (sqrtRemain * sqrtRemain == remain) return true;
        }
        return false;
    }
};
