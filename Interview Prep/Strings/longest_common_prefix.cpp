class Solution {
public:
    // Approach 1: Character by Character Comparison
    // Time Complexity: O(S) where S is the sum of all characters in all strings
    // Space Complexity: O(1)
    string longestCommonPrefix(vector<string>& strs) {
        /*
        Example Walkthrough:
        Input: strs = ["flower", "flow", "flight"]
        
        Step 1: Check first character 'f' in all strings
        "flower"[0] = 'f'
        "flow"[0] = 'f'
        "flight"[0] = 'f'
        Match found, continue
        
        Step 2: Check second character 'l' in all strings
        "flower"[1] = 'l'
        "flow"[1] = 'l'
        "flight"[1] = 'l'
        Match found, continue
        
        Step 3: Check third character 'o' in all strings
        "flower"[2] = 'o'
        "flow"[2] = 'o'
        "flight"[2] = 'i' -> Mismatch found!
        Return "fl"
        */

        // Base case: empty input
        if (strs.empty()) return "";

        // Compare characters at each position across all strings
        for (int i = 0; i < strs[0].size(); i++) {
            char c = strs[0][i];  // Get character from first string
            // Compare with same position in all other strings
            for (int j = 1; j < strs.size(); j++) {
                // If we reach end of any string or find mismatch
                if (i >= strs[j].size() || strs[j][i] != c) {
                    return strs[0].substr(0, i);  // Return prefix found so far
                }
            }
        }

        // If we complete the loop, first string is the common prefix
        return strs[0];
    }

    // Approach 2: Using Sorting
    // Time Complexity: O(nlogn) for sorting + O(min_len) for comparison
    // Space Complexity: O(1)
    string longestCommonPrefix_Sorting(vector<string>& strs) {
        /*
        Example Walkthrough:
        Input: strs = ["flower", "flow", "flight"]
        
        After sorting:
        ["flight", "flow", "flower"]
        
        Compare first and last string:
        "flight" and "flower"
        Common prefix: "fl"
        */
        
        if (strs.empty()) return "";
        
        // Sort the array of strings
        sort(strs.begin(), strs.end());
        
        // Compare first and last string
        string first = strs[0];
        string last = strs[strs.size() - 1];
        
        int i = 0;
        while (i < first.size() && i < last.size() && first[i] == last[i]) {
            i++;
        }
        
        return first.substr(0, i);
    }

    // Approach 3: Using Hash Map (Trie-like approach)
    // Time Complexity: O(S) where S is the sum of all characters
    // Space Complexity: O(S) for storing the trie
    string longestCommonPrefix_HashMap(vector<string>& strs) {
        /*
        Example Walkthrough:
        Input: strs = ["flower", "flow", "flight"]
        
        Build prefix frequency map:
        "f": 3
        "fl": 3
        "flo": 2
        "flow": 2
        "flowe": 1
        "flower": 1
        "fli": 1
        "flig": 1
        "fligh": 1
        "flight": 1
        
        Longest prefix with frequency = n: "fl"
        */
        
        if (strs.empty()) return "";
        
        // Map to store prefix frequencies
        unordered_map<string, int> prefixFreq;
        
        // Count frequency of each prefix
        for (const string& str : strs) {
            string prefix = "";
            for (char c : str) {
                prefix += c;
                prefixFreq[prefix]++;
            }
        }
        
        // Find longest prefix that appears in all strings
        string result = "";
        string current = "";
        
        // Check prefixes of first string
        for (char c : strs[0]) {
            current += c;
            if (prefixFreq[current] == strs.size()) {
                result = current;
            } else {
                break;
            }
        }
        
        return result;
    }
};

/*
Comparison of Approaches:

1. Character by Character (Original):
   - Pros: Simple, easy to understand, good for small inputs
   - Cons: May do unnecessary comparisons
   - Best when: Input size is small or strings are similar

2. Sorting Approach:
   - Pros: Only need to compare first and last string
   - Cons: Sorting overhead, modifies input array
   - Best when: Input size is large and strings are diverse

3. Hash Map Approach:
   - Pros: Can be extended to find other common patterns
   - Cons: Uses more memory, more complex
   - Best when: Need to find other common patterns or prefixes

Time Complexity:
- Approach 1: O(S) where S is sum of all characters
- Approach 2: O(nlogn) for sorting + O(min_len) for comparison
- Approach 3: O(S) for building map + O(min_len) for finding result

Space Complexity:
- Approach 1: O(1)
- Approach 2: O(1) if in-place sort, O(n) if not
- Approach 3: O(S) for storing the map
*/
