class Solution {
public:
  int helper(int mid, int n, int m){
    long long ans = 1;
    long long base = mid;

    while(n > 0){
        if(n%2){
            ans = ans * base;
            if(ans > m) return 2;
            n--;
        }
        else{
            n /= 2;
            base = base * base;
            if(base > m) return 2;
        }
    }

    if(ans == m) return 1;
    return 0;
  }

  int NthRoot(int N, int M) {
        int low = 1;
        int high = M;

        while(low <= high){
            int mid = (low + high)/2;
            int midN = helper(mid, N, M);

            if(midN == 1){
                return mid;
            }
            else if(midN == 0){
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
        }

        return -1;
    }
};
