
# **Valid Sudoku**

## **Problem Statement**
Determine if a **9 × 9 Sudoku board** is valid. A valid board must follow these rules:

1. Each **row** must contain the digits **1-9** without repetition.
2. Each **column** must contain the digits **1-9** without repetition.
3. Each of the **nine 3 × 3 sub-boxes** must contain the digits **1-9** without repetition.

### **Notes:**
- The board is **partially filled**, meaning empty cells (denoted by `'.'`) do not affect validity.
- A board can be **valid but not necessarily solvable** (i.e., there might be no way to complete it to a full Sudoku solution).


## **Examples**

### **Example 1:**
#### **Input:**
```cpp
board =
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
```
#### **Output:**
```cpp
true
```

---

### **Example 2:**
#### **Input:**
```cpp
board =
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
```
#### **Output:**
```cpp
false
```
#### **Explanation:**
- The number `8` appears **twice in the first 3×3 sub-box** (top-left).
- Thus, the board is **invalid**.

---

## **Constraints**
- `board.length == 9`
- `board[i].length == 9`
- `board[i][j]` is a **digit ('1'-'9')** or **'.'** (empty cell).

---

## **Optimized C++ Solution**

```cpp
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int N = 9;

        // Use unordered_set to track seen numbers
        vector<unordered_set<char>> rows(N);
        vector<unordered_set<char>> cols(N);
        vector<unordered_set<char>> boxes(N);

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                char val = board[r][c];

                // Skip empty cells
                if (val == '.') continue;

                // Check row validity
                if (rows[r].count(val)) return false;
                rows[r].insert(val);

                // Check column validity
                if (cols[c].count(val)) return false;
                cols[c].insert(val);

                // Check 3x3 sub-box validity
                int idx = (r / 3) * 3 + (c / 3);
                if (boxes[idx].count(val)) return false;
                boxes[idx].insert(val);
            }
        }
        return true;
    }
};
```

---

## **Explanation of Approach**

### **1. Using Hash Sets to Track Values**
- We use **three vectors of unordered_sets**:
  - `rows[N]` → To track numbers in each row.
  - `cols[N]` → To track numbers in each column.
  - `boxes[N]` → To track numbers in each 3×3 sub-box.

### **2. Iterating Through the Board**
- Traverse the board using two nested loops (`r` for rows and `c` for columns).
- If `board[r][c] == '.'`, skip to the next iteration.
- Check if `val` is already present in:
  - The corresponding row set → If yes, return `false`.
  - The corresponding column set → If yes, return `false`.
  - The corresponding **3×3 sub-box** (computed using `(r/3) * 3 + (c/3)`) → If yes, return `false`.
- If no duplicates are found, insert `val` into the respective sets.

### **3. Time & Space Complexity**
- **Time Complexity:** \(O(9^2) = O(81) \approx O(1)\) → Constant time, since we always process a **fixed 9×9 grid**.
- **Space Complexity:** \(O(9) + O(9) + O(9) = O(27) \approx O(1)\) → Three **hash sets** store at most 9 values each.


