#include <string>
#include <unordered_map>
#include <iostream> // For main example

/*
Problem: Ransom Note (LeetCode 383)
Given two strings, `ransomNote` and `magazine`, return `true` if `ransomNote` can be constructed
by using the letters from `magazine` and `false` otherwise. Each letter in `magazine` can only
be used once in `ransomNote`.

Constraints typically assume lowercase English letters, but the hash map approach is general.

Concept (Using Hash Map for Character Frequencies):
The core idea is to count the frequency of each character available in the `magazine` string.
Then, for each character required by the `ransomNote`, we check if it's available in our
`magazine` counts and decrement its count upon use. If we encounter a character in `ransomNote`
that is not available (either not present or its count has reached zero), then the note
cannot be constructed.

How it Works:
1. Initialize an `unordered_map<char, int> magazine_counts` to store the frequency of each character
   in the `magazine`.
2. Populate Frequencies: Iterate through each character `c` in the `magazine` string.
   For each `c`, increment `magazine_counts[c]`.
3. Check Ransom Note Characters: Iterate through each character `c` in the `ransomNote` string.
   a. For the current character `c` from `ransomNote`, check its count in `magazine_counts`.
      - If `magazine_counts[c]` is 0 (meaning the character `c` is either not present in the
        `magazine` at all, or all occurrences of `c` from `magazine` have already been used for
        the `ransomNote`), then the `ransomNote` cannot be constructed. Return `false`.
        (Note: Accessing `mp[c]` for a non-existent key `c` in an `unordered_map<char, int>`
        will insert `c` with a default value of 0 for `int`. So, `mp[c] == 0` correctly handles
        both cases: character not available or count depleted.)
   b. If `magazine_counts[c]` is greater than 0, it means the character is available. Decrement
      `magazine_counts[c]` by 1 to signify that one occurrence of this character has been used.
4. Construction Possible: If the loop over `ransomNote` completes without returning `false`,
   it means all characters required for the `ransomNote` were available in the `magazine`.
   Return `true`.

Visual Example 1:
ransomNote = "aa", magazine = "aab"

1. `magazine_counts = {}`
2. Populate from `magazine = "aab"`:
   - char 'a': `magazine_counts['a']` becomes 1.
   - char 'a': `magazine_counts['a']` becomes 2.
   - char 'b': `magazine_counts['b']` becomes 1.
   `magazine_counts` is now `{'a': 2, 'b': 1}`.

3. Check `ransomNote = "aa"`:
   - First char 'a':
     - `magazine_counts['a']` is 2 (which is > 0). Condition `mp[c] == 0` is false.
     - Decrement `magazine_counts['a']`. It becomes 1.
     `magazine_counts` is now `{'a': 1, 'b': 1}`.
   - Second char 'a':
     - `magazine_counts['a']` is 1 (which is > 0). Condition `mp[c] == 0` is false.
     - Decrement `magazine_counts['a']`. It becomes 0.
     `magazine_counts` is now `{'a': 0, 'b': 1}`.

4. Loop over `ransomNote` finished. Return `true`.

Visual Example 2:
ransomNote = "abc", magazine = "ab"

1. `magazine_counts = {}`
2. Populate from `magazine = "ab"`:
   - `magazine_counts` becomes `{'a': 1, 'b': 1}`.

3. Check `ransomNote = "abc"`:
   - First char 'a': `magazine_counts['a']` is 1 (>0). Decrement. `magazine_counts['a']` becomes 0.
   - Second char 'b': `magazine_counts['b']` is 1 (>0). Decrement. `magazine_counts['b']` becomes 0.
   - Third char 'c':
     - `magazine_counts['c']` is accessed. Since 'c' is not in the map, `magazine_counts['c']` becomes 0.
     - Condition `magazine_counts['c'] == 0` (i.e., `0 == 0`) is true.
     - Return `false`.

Algorithm Properties:

1. Time Complexity: O(m + n)
   - Where `m` is the length of the `magazine` string and `n` is the length of the `ransomNote` string.
   - The first loop iterates through `magazine` once (O(m) operations, as hash map insertions/updates are O(1) on average).
   - The second loop iterates through `ransomNote` once (O(n) operations, as hash map lookups/updates are O(1) on average).

2. Space Complexity: O(k) or O(1) (if character set is fixed and small)
   - Where `k` is the number of unique characters in the `magazine` string.
   - The `unordered_map` stores at most `k` distinct characters and their counts.
   - If the problem assumes a fixed character set (e.g., 26 lowercase English letters), then `k` is constant (e.g., 26), making the space complexity O(1).
     Otherwise, it depends on the diversity of characters in the `magazine`.

Edge Cases:
- `ransomNote` is empty: The second loop (over `ransomNote`) doesn't run. Returns `true` (correct, an empty note can always be constructed).
- `magazine` is empty (and `ransomNote` is not): `magazine_counts` remains empty. The first character check in the second loop will result in `magazine_counts[c] == 0`, returning `false` (correct).
- `ransomNote` is longer than `magazine`: Might return `true` or `false` depending on character reuse and availability, handled by the logic.
- Characters in `ransomNote` not present in `magazine`: Handled correctly by `magazine_counts[c] == 0` check.

Why Hash Map is Efficient:
- Fast Operations: `unordered_map` provides average O(1) time complexity for insertions, deletions, and lookups.
- Flexibility: Handles any character set, not just lowercase English letters (unlike a fixed-size array approach).

Alternative Approaches:

1. Using a Fixed-Size Array (e.g., for lowercase English letters):
   - If the character set is known and small (e.g., 'a' through 'z'), an integer array of size 26 (or 128 for ASCII, 256 for extended ASCII) can be used instead of a hash map.
   - `counts[c - 'a']++` for `magazine` and `counts[c - 'a']--` for `ransomNote`.
   - Time Complexity: O(m + n).
   - Space Complexity: O(1) (since the array size is constant, e.g., 26).
   - This can be slightly faster due to no hashing overhead if applicable.

2. Sorting:
   - Sort both `ransomNote` and `magazine` strings.
   - Use two pointers to iterate through them and check if all characters of `ransomNote` can be found in `magazine` sequentially.
   - Time Complexity: O(m log m + n log n) due to sorting, which is generally less efficient than the hash map approach.
   - Space Complexity: O(log m + log n) or O(m + n) depending on the sort implementation's space usage (if it sorts in-place or not).
*/

class Solution {
public:
    bool canConstruct(std::string ransomNote, std::string magazine) {
        std::unordered_map<char, int> magazine_counts;

        // Count frequencies of characters in the magazine
        for (char c : magazine) {
            magazine_counts[c]++;
        }

        // Check if ransomNote can be constructed from the magazine characters
        for (char c : ransomNote) {
            // If the character is not available in the magazine (count is 0 or char not present)
            if (magazine_counts[c] == 0) { 
                // Accessing magazine_counts[c] for a non-existent key default-initializes it to 0.
                // So this condition correctly checks for both depleted counts and absent characters.
                return false;
            }
            // If character is available, decrement its count (as it's being used)
            magazine_counts[c]--;
        }

        // If all characters in ransomNote were found and used from magazine_counts
        return true;
    }
};

// int main() {
//     Solution sol;

//     std::cout << "Test Case 1: ransomNote = \"a\", magazine = \"b\"" << std::endl;
//     std::cout << "Expected: false, Got: " << (sol.canConstruct("a", "b") ? "true" : "false") << std::endl << std::endl;

//     std::cout << "Test Case 2: ransomNote = \"aa\", magazine = \"ab\"" << std::endl;
//     std::cout << "Expected: false, Got: " << (sol.canConstruct("aa", "ab") ? "true" : "false") << std::endl << std::endl;

//     std::cout << "Test Case 3: ransomNote = \"aa\", magazine = \"aab\"" << std::endl;
//     std::cout << "Expected: true, Got: " << (sol.canConstruct("aa", "aab") ? "true" : "false") << std::endl << std::endl;

//     std::cout << "Test Case 4: ransomNote = \"\", magazine = \"abc\"" << std::endl;
//     std::cout << "Expected: true, Got: " << (sol.canConstruct("", "abc") ? "true" : "false") << std::endl << std::endl;

//     std::cout << "Test Case 5: ransomNote = \"abc\", magazine = \"\"" << std::endl;
//     std::cout << "Expected: false, Got: " << (sol.canConstruct("abc", "") ? "true" : "false") << std::endl << std::endl;
    
//     std::cout << "Test Case 6: ransomNote = \"fihjjjjei\", magazine = \"hjibagacbhadfaefdjaeaefgi\"" << std::endl;
//     std::cout << "Expected: false, Got: " << (sol.canConstruct("fihjjjjei", "hjibagacbhadfaefdjaeaefgi") ? "true" : "false") << std::endl << std::endl;

//     return 0;
// }