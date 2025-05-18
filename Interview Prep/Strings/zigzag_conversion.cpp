class Solution {
public:
    string convert(string s, int numRows) {
        /*
        Example Walkthrough:
        Input: s = "PAYPALISHIRING", numRows = 3
        
        Step 1: Initial state
        Row 0: []
        Row 1: []
        Row 2: []
        
        Step 2: After processing "PAY"
        Row 0: [P]
        Row 1: [A]
        Row 2: [Y]
        
        Step 3: After processing "PAL"
        Row 0: [P]
        Row 1: [A, P, L]
        Row 2: [Y]
        
        Step 4: After processing "ISH"
        Row 0: [P, A]
        Row 1: [A, P, L, S]
        Row 2: [Y, I]
        
        Step 5: After processing "IRI"
        Row 0: [P, A, H]
        Row 1: [A, P, L, S, I]
        Row 2: [Y, I, R]
        
        Final state:
        Row 0: [P, A, H, N]
        Row 1: [A, P, L, S, I, I, G]
        Row 2: [Y, I, R]
        
        Final output: "PAHNAPLSIIGYIR"
        */

        // Base Cases:
        // 1. If numRows is 1, return original string as no zigzag pattern is possible
        // 2. If numRows is greater than or equal to string length, return original string
        if(numRows == 1 || numRows >= s.length())
            return s;

        // Initialize variables:
        // index: tracks current row position (0 to numRows-1)
        // d: direction of movement (1 for down, -1 for up)
        int index = 0;
        int d = 1;
        
        // Create a vector of vectors to store characters in each row
        // Each inner vector represents one row in the zigzag pattern
        vector<vector<char>> rows(numRows);

        // Main Algorithm:
        // Process each character and place it in appropriate row
        // For example with "PAYPALISHIRING":
        // 1. 'P' goes to row 0
        // 2. 'A' goes to row 1
        // 3. 'Y' goes to row 2
        // 4. 'P' goes to row 1 (direction changed to up)
        // 5. 'A' goes to row 0 (direction changed to down)
        // And so on...
        for(char c : s) {
            // Add current character to the current row
            rows[index].push_back(c);

            // Change direction when reaching top or bottom row
            if(index == 0) {
                d = 1;  // Move down when at top row
            }
            else if (index == numRows - 1) {
                d = -1; // Move up when at bottom row
            }

            // Update row index based on direction
            index += d;
        }

        // Result Construction:
        // Read characters row by row to form final string
        // For our example:
        // 1. Read row 0: "PAHN"
        // 2. Read row 1: "APLSIIG"
        // 3. Read row 2: "YIR"
        // Final result: "PAHNAPLSIIGYIR"
        string result;
        for(auto row : rows) {
            for(char c : row) {
                result += c;
            }
        }

        return result;
    }
};