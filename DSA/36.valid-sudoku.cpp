/*
 * @lc app=leetcode id=36 lang=cpp
 *
 * [36] Valid Sudoku
 */

// @lc code=start
class Solution {
    public:
        bool isValidSudoku(vector<vector<char>>& board) {
            int N = 9;
    
            // Use unordered_set to record the status
            vector<unordered_set<char>> rows(N);
            vector<unordered_set<char>> cols(N);
            vector<unordered_set<char>> boxes(N);
    
            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N; c++) {
                    char val = board[r][c];
    
                    // Skip empty cells
                    if (val == '.') {
                        continue;
                    }
    
                    // Check row
                    if (rows[r].count(val)) {
                        return false;
                    }
                    rows[r].insert(val);
    
                    // Check column
                    if (cols[c].count(val)) {
                        return false;
                    }
                    cols[c].insert(val);
    
                    // Check 3x3 box
                    int idx = (r / 3) * 3 + (c / 3);
                    if (boxes[idx].count(val)) {
                        return false;
                    }
                    boxes[idx].insert(val);
                }
            }
            return true;
        }
    };
// @lc code=end

