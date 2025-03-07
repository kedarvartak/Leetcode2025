class Solution {
public:
    string maximumNumber(string num, vector<int>& change) {
        string maxi = num; 
        bool changed = false;

        for (int i = 0; i < num.size(); i++) {
            int digit = num[i] - '0'; 

            if (change[digit] > digit) { 
                num[i] = change[digit] + '0'; 
                changed = true;
            } else if (changed && change[digit] < digit) {
                break; 
            }
        }

        return num;
    }
};
