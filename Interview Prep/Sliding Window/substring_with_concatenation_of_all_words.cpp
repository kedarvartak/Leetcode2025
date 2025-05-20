class Solution {
public:
    // Sliding Window Approach
    // Time Complexity: O(n * m * k) where n is string length, m is word length, k is number of words
    // Space Complexity: O(k) for storing word counts
    vector<int> findSubstring(string s, vector<string>& words) {
        /*
        Simple Rules to Remember:
        1. All words are of same length
        2. Need to find all starting indices where concatenation exists
        3. Words can be in any order
        4. Each word must be used exactly once
        5. Use sliding window of fixed size (total length of all words)

        Visual Example:
        s = "barfoothefoobarman"
        words = ["foo","bar"]

        Step 1: Check "barfoo"
               - Count: bar(1), foo(1)
               - Matches target counts
               - Add index 0 to result

        Step 2: Check "arfoot"
               - Count: arf(1), oot(1)
               - Doesn't match target

        Step 3: Check "rfoothe"
               - Count: rfo(1), oth(1)
               - Doesn't match target

        Step 4: Check "foothef"
               - Count: foo(1), the(1)
               - Doesn't match target

        Step 5: Check "oothefo"
               - Count: oot(1), hef(1)
               - Doesn't match target

        Step 6: Check "othefoo"
               - Count: oth(1), efo(1)
               - Doesn't match target

        Step 7: Check "thefoob"
               - Count: the(1), foo(1)
               - Doesn't match target

        Step 8: Check "hefooba"
               - Count: hef(1), oob(1)
               - Doesn't match target

        Step 9: Check "efoobar"
               - Count: efo(1), oba(1)
               - Doesn't match target

        Step 10: Check "foobar"
               - Count: foo(1), bar(1)
               - Matches target counts
               - Add index 9 to result

        Final result: [0, 9]
        */

        vector<int> result;
        if (s.empty() || words.empty()) return result;

        // Get word length and total length
        int wordLen = words[0].length();
        int totalLen = wordLen * words.size();

        // Create target word count map
        unordered_map<string, int> targetCount;
        for (const string& word : words) {
            targetCount[word]++;
        }

        // Try each possible starting position
        for (int i = 0; i <= (int)s.length() - totalLen; i++) {
            // Create current window word count map
            unordered_map<string, int> currentCount;
            bool valid = true;

            // Check each word in the window
            for (int j = 0; j < words.size(); j++) {
                string word = s.substr(i + j * wordLen, wordLen);
                
                // If word not in target or count exceeds target, window is invalid
                if (targetCount.find(word) == targetCount.end() || 
                    ++currentCount[word] > targetCount[word]) {
                    valid = false;
                    break;
                }
            }

            // If window is valid, add starting index to result
            if (valid) {
                result.push_back(i);
            }
        }

        return result;
    }
};

/*
Simple Memory Aid:

1. Window Properties:
   - Fixed size (total length of all words)
   - Must contain all words exactly once
   - Words can be in any order
   - All words are same length

2. Key Steps:
   a. Calculate window size
   b. Create target word count map
   c. Slide window through string
   d. Check each word in window
   e. Add valid indices to result

3. Visual Process:
   For s = "barfoothefoobarman", words = ["foo","bar"]:

   Window 1: "barfoo"  -> Valid (index 0)
   Window 2: "arfoot"  -> Invalid
   Window 3: "rfoothe" -> Invalid
   Window 4: "foothef" -> Invalid
   Window 5: "oothefo" -> Invalid
   Window 6: "othefoo" -> Invalid
   Window 7: "thefoob" -> Invalid
   Window 8: "hefooba" -> Invalid
   Window 9: "efoobar" -> Invalid
   Window 10: "foobar" -> Valid (index 9)

4. Common Pitfalls:
   - Not handling empty input
   - Incorrect window size calculation
   - Not checking word counts exactly
   - Not handling word order
   - Not considering all possible starting positions

5. Time Complexity: O(n * m * k)
   - n: string length
   - m: word length
   - k: number of words
   - Each position checked
   - Each word in window checked
   - Each word compared

6. Space Complexity: O(k)
   - k: number of words
   - Store word counts
   - Store result indices

7. Key Properties:
   - All words same length
   - Words can be in any order
   - Each word used exactly once
   - Window size is fixed
   - Need all starting indices
*/
