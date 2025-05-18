class Solution {
public:
    int strStr(string haystack, string needle) {
        /*
        Example Walkthrough:
        Input: haystack = "hello", needle = "ll"
        
        Step 1: Check if needle can fit in haystack
        haystack length = 5, needle length = 2
        Since 5 >= 2, we proceed
        
        Step 2: Start checking from each position
        Position 0: "he" != "ll"
        Position 1: "el" != "ll"
        Position 2: "ll" == "ll" -> Found match!
        Position 3: "lo" != "ll"
        
        Return 2 (index where match was found)
        
        Another Example:
        Input: haystack = "aaaaa", needle = "bba"
        haystack length = 5, needle length = 3
        No match found, return -1
        */

        // Base Case:
        // If needle is longer than haystack, it can't be a substring
        if (haystack.length() < needle.length()) {
            return -1;
        }
        
        // Main Algorithm:
        // Check each possible starting position in haystack
        // We only need to check positions where needle can fit
        // i.e., from 0 to (haystack.length() - needle.length())
        for (int i = 0; i <= haystack.length() - needle.length(); i++) {
            // Extract substring of same length as needle
            // Compare with needle
            // If match found, return current position
            if (haystack.substr(i, needle.length()) == needle) {
                return i;
            }
        }
        
        // If no match found after checking all positions
        return -1;        
    }
};

// alternately you can directly use find function in c++
// return haystack.find(needle);
