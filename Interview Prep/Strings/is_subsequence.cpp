class Solution {
public:
    // Approach 1: Two Pointers
    // Time Complexity: O(n) where n is length of string t
    // Space Complexity: O(1)
    bool isSubsequence(string s, string t) {
        /*
        Example Walkthrough:
        Input: s = "abc", t = "ahbgdc"
        
        Step 1: sp = 0, tp = 0
        s[0] = 'a', t[0] = 'a' -> Match! sp++ = 1, tp++ = 1
        
        Step 2: sp = 1, tp = 1
        s[1] = 'b', t[1] = 'h' -> No match, tp++ = 2
        
        Step 3: sp = 1, tp = 2
        s[1] = 'b', t[2] = 'b' -> Match! sp++ = 2, tp++ = 3
        
        Step 4: sp = 2, tp = 3
        s[2] = 'c', t[3] = 'g' -> No match, tp++ = 4
        
        Step 5: sp = 2, tp = 4
        s[2] = 'c', t[4] = 'd' -> No match, tp++ = 5
        
        Step 6: sp = 2, tp = 5
        s[2] = 'c', t[5] = 'c' -> Match! sp++ = 3, tp++ = 6
        
        sp == s.length() -> Return true
        */

        // Initialize pointers for both strings
        int sp = 0;  // pointer for string s
        int tp = 0;  // pointer for string t

        // Continue until we reach end of either string
        while (sp < s.length() && tp < t.length()) {
            // If characters match, move both pointers
            // If not, only move pointer in string t
            if (s[sp] == t[tp])
                sp++;
            tp++;
        }

        // If we've matched all characters in s, it's a subsequence
        return sp == s.length(); 
    }

    // Approach 2: Using find() function
    // Time Complexity: O(n) where n is length of string t
    // Space Complexity: O(1)
    bool isSubsequence_Find(string s, string t) {
        /*
        Example Walkthrough:
        Input: s = "abc", t = "ahbgdc"
        
        Step 1: Find 'a' in t starting from position 0
        Found at position 0
        
        Step 2: Find 'b' in t starting from position 1
        Found at position 2
        
        Step 3: Find 'c' in t starting from position 3
        Found at position 5
        
        All characters found in order -> Return true
        */
        
        size_t pos = 0;
        for (char c : s) {
            // Find next occurrence of current character
            pos = t.find(c, pos);
            if (pos == string::npos) return false;
            pos++;  // Move to next position
        }
        return true;
    }

    // Approach 3: Dynamic Programming (for multiple queries)
    // Time Complexity: O(m*n) for preprocessing, O(1) per query
    // Space Complexity: O(m*n) where m is length of s and n is length of t
    bool isSubsequence_DP(string s, string t) {
        /*
        Example Walkthrough:
        Input: s = "abc", t = "ahbgdc"
        
        Build next array for each character in t:
        For 'a': next[0] = 0
        For 'h': next[1] = 2
        For 'b': next[2] = 2
        For 'g': next[3] = 4
        For 'd': next[4] = 5
        For 'c': next[5] = 5
        
        Then check if we can form s using these positions
        */
        
        int n = t.length();
        vector<vector<int>> next(n + 1, vector<int>(26, n));
        
        // Build next array
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < 26; j++) {
                next[i][j] = next[i + 1][j];
            }
            next[i][t[i] - 'a'] = i;
        }
        
        // Check if s is subsequence
        int pos = 0;
        for (char c : s) {
            pos = next[pos][c - 'a'];
            if (pos == n) return false;
            pos++;
        }
        return true;
    }
};

/*
Comparison of Approaches:

1. Two Pointers (Original):
   - Pros: Simple, efficient, constant space
   - Cons: Can't be optimized for multiple queries
   - Best when: Single query, memory is limited

2. Find() Function:
   - Pros: Clean, readable, uses built-in function
   - Cons: Slightly less efficient than two pointers
   - Best when: Code readability is priority

3. Dynamic Programming:
   - Pros: O(1) per query after preprocessing
   - Cons: High memory usage, complex implementation
   - Best when: Multiple queries on same string t

Time Complexity:
- Approach 1: O(n) where n is length of t
- Approach 2: O(n) where n is length of t
- Approach 3: O(m*n) preprocessing, O(1) per query

Space Complexity:
- Approach 1: O(1)
- Approach 2: O(1)
- Approach 3: O(m*n) where m is length of s and n is length of t

Note: For single query, Approach 1 (Two Pointers) is most efficient.
For multiple queries on same string t, Approach 3 (DP) is better.
*/
