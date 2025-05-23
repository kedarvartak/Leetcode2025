#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> // For std::sort
#include <iostream>  // For main example

/*
Problem: Group Anagrams (LeetCode 49)
Given an array of strings `strs`, group the anagrams together. You can return the answer in any order.
An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
typically using all the original letters exactly once.

Example: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Concept (Using Sorted String as Key):
The core idea is that all anagrams of a word will become identical if their characters are sorted.
For instance, "eat", "tea", and "ate" all become "aet" when sorted.
This sorted version of the string can serve as a unique canonical key in a hash map.
We can then group all original strings that map to the same sorted key.

How it Works:
1. Initialize an `unordered_map<std::string, std::vector<std::string>> anagram_groups`.
   The key of this map will be the sorted string (canonical form), and the value will be a
   vector containing all original strings that are anagrams of this canonical form.

2. Iterate through each string `s` in the input vector `strs`:
   a. Create a copy of the string `s`. Let's call it `key_str`.
   b. Sort the characters of `key_str` alphabetically.
   c. Now, `key_str` is the canonical representation for all anagrams of `s`.
   d. Add the original string `s` to the vector associated with `key_str` in the `anagram_groups` map.
      `anagram_groups[key_str].push_back(s);`

3. Prepare the final result: Initialize an empty `std::vector<std::vector<std::string>> result`.

4. Iterate through each key-value pair in the `anagram_groups` map:
   a. For each pair, the value is a vector of strings that are all anagrams of each other (corresponding to the sorted key).
   b. Add this vector of anagrams to the `result` vector.
      `result.push_back(pair.second);`

5. Return the `result` vector.

Visual Example:
strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
`anagram_groups = {}`

1. s = "eat":
   key_str = "eat" -> sort -> "aet"
   anagram_groups["aet"].push_back("eat") -> `anagram_groups = {{"aet": ["eat"]}}`

2. s = "tea":
   key_str = "tea" -> sort -> "aet"
   anagram_groups["aet"].push_back("tea") -> `anagram_groups = {{"aet": ["eat", "tea"]}}`

3. s = "tan":
   key_str = "tan" -> sort -> "ant"
   anagram_groups["ant"].push_back("tan") -> `anagram_groups = {{"aet": ["eat", "tea"]}, {"ant": ["tan"]}}`

4. s = "ate":
   key_str = "ate" -> sort -> "aet"
   anagram_groups["aet"].push_back("ate") -> `anagram_groups = {{"aet": ["eat", "tea", "ate"]}, {"ant": ["tan"]}}`

5. s = "nat":
   key_str = "nat" -> sort -> "ant"
   anagram_groups["ant"].push_back("nat") -> `anagram_groups = {{"aet": ["eat", "tea", "ate"]}, {"ant": ["tan", "nat"]}}`

6. s = "bat":
   key_str = "bat" -> sort -> "abt"
   anagram_groups["abt"].push_back("bat") -> `anagram_groups = {{"aet": ["eat", "tea", "ate"]}, {"ant": ["tan", "nat"]}, {"abt": ["bat"]}}`

7. Convert map to result vector:
   result.push_back(["eat", "tea", "ate"])
   result.push_back(["tan", "nat"])
   result.push_back(["bat"])
   (Order of groups in result doesn't matter)

Algorithm Properties:

1. Time Complexity: O(N * K log K)
   - `N` is the number of strings in the input vector `strs`.
   - `K` is the maximum length of a string in `strs`.
   - For each of the `N` strings, we create a copy (O(K)) and then sort it. Sorting a string of
     length `K` takes O(K log K) time.
   - Hash map operations (insertion, lookup) take O(K) on average for string keys (as hashing and equality checking depend on string length).
   - So, the dominant part is N * (K for copy + K log K for sort + K for map op) = O(N * K log K).
   - Iterating through the map at the end takes roughly O(N*K) to copy strings to result.

2. Space Complexity: O(N * K)
   - In the worst case, the `unordered_map` might store all `N` strings, and the total number of
     characters across all strings is roughly `N * K` (if average length is K).
   - The keys (sorted strings) also take space.
   - The `result` vector also stores all the original strings.

Edge Cases:
- Empty `strs` vector: Loop doesn't run, empty map, returns empty vector of vectors (correct).
- `strs` contains empty strings: `sort("")` is fine, empty string becomes key. `["", ""]` -> `{{"":["", ""]}}`.
- `strs` contains single-character strings: `["a", "b"]` -> `{{"a":["a"]}, {"b":["b"]}}`.
- All strings are anagrams of each other: One entry in map, value is vector of all strings.
- No strings are anagrams of each other: N entries in map, each value is a vector with one string.

Why Sorted String Key is Effective:
- Provides a unique canonical representation for any group of anagrams.
- `std::string` is hashable and can be used directly as a key in `std::unordered_map`.
- Sorting is a standard and well-understood operation.

Alternative Key Generation (Briefly):
1. Character Count Array/Frequency Map as Key:
   - For each string, count the frequency of its characters (e.g., using an array of 26 integers for lowercase English letters).
   - Convert this frequency count into a string key (e.g., "a2b1c0...z0") or use `std::array<int, 26>` as a key if the map is `std::map` or `std::unordered_map` with a custom hasher for `std::array`.
   - Time Complexity for key generation: O(K) per string (to count chars).
   - Overall Time Complexity: O(N * K) (N strings * (K to generate key + K for map op)). This can be faster than O(N * K log K) if K is large.
   - Space Complexity: Similar O(N * K) for storing strings. Key space might be smaller (e.g., fixed 26-char string for counts).
*/

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> anagram_groups;

        for (const std::string& s : strs) { // Iterate by const reference
            std::string key_str = s;
            std::sort(key_str.begin(), key_str.end()); // Sort to get the canonical key
            anagram_groups[key_str].push_back(s);    // Group original string under this key
        }

        std::vector<std::vector<std::string>> result;
        // Iterate through the map (C++17 structured binding, or use .first, .second)
        for (const auto& pair : anagram_groups) { 
            result.push_back(pair.second); // Add the vector of anagrams to the result
        }

        return result;
    }
};

// Helper function to print the result for testing
// void printResult(const std::vector<std::vector<std::string>>& result) {
//     std::cout << "[";
//     for (size_t i = 0; i < result.size(); ++i) {
//         std::cout << "[";
//         for (size_t j = 0; j < result[i].size(); ++j) {
//             std::cout << "\"" << result[i][j] << "\"";
//             if (j < result[i].size() - 1) {
//                 std::cout << ",";
//             }
//         }
//         std::cout << "]";
//         if (i < result.size() - 1) {
//             std::cout << ",";
//         }
//     }
//     std::cout << "]" << std::endl;
// }

// int main() {
//     Solution sol;
//     std::vector<std::string> strs1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
//     std::cout << "Input: [\"eat\",\"tea\",\"tan\",\"ate\",\"nat\",\"bat\"]" << std::endl;
//     std::vector<std::vector<std::string>> result1 = sol.groupAnagrams(strs1);
//     std::cout << "Output: ";
//     // printResult(result1); // Expected (order of groups and strings within groups can vary for unordered_map):
//                          // [["bat"],["nat","tan"],["ate","eat","tea"]]
//                          // For consistent output for comparison, one might sort the groups and strings within groups.

//     std::vector<std::string> strs2 = {""};
//     std::cout << "\nInput: [\"\"]" << std::endl;
//     std::vector<std::vector<std::string>> result2 = sol.groupAnagrams(strs2);
//     std::cout << "Output: ";
//     // printResult(result2); // Expected: [[""]]

//     std::vector<std::string> strs3 = {"a"};
//     std::cout << "\nInput: [\"a\"]" << std::endl;
//     std::vector<std::vector<std::string>> result3 = sol.groupAnagrams(strs3);
//     std::cout << "Output: ";
//     // printResult(result3); // Expected: [["a"]]

//     std::vector<std::string> strs4 = {};
//     std::cout << "\nInput: []" << std::endl;
//     std::vector<std::vector<std::string>> result4 = sol.groupAnagrams(strs4);
//     std::cout << "Output: ";
//     // printResult(result4); // Expected: []

//     return 0;
// }
