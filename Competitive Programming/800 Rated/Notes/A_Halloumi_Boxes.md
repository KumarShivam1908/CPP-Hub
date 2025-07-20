## Halloumi Boxes

**Problem Link:** [Codeforces 1903A - Halloumi Boxes](https://codeforces.com/problemset/problem/1903/A)

### Problem Summary

Given an array of boxes, you can reverse any subarray of length at most `k`. The task is to determine if you can sort the array in non-decreasing order using this operation.

### Solution Approach

There are two main cases to consider:

1. **Array is already sorted:**  
    - If the array is already sorted, print `YES`. No operations are needed.

2. **Array is not sorted:**  
    - If `k > 1`, you can always sort the array.  
      - For `k = 2`, you can swap any two adjacent elements, which is sufficient to sort any array (similar to bubble sort).
      - For `k > 2`, you can reverse larger subarrays, making sorting even easier.
    - If `k = 1`, you can only reverse subarrays of length 1 (i.e., do nothing).  
      - If the array is not already sorted, print `NO`.

### Key Observations

- For `k = 1`, no changes can be made.
- For `k > 1`, sorting is always possible.

### Example

Consider the array: `4 2 3 8` and `k = 2`  
- Reverse `4,2` → `2 4 3 8`  
- Reverse `4,3` → `2 3 4 8`  
Now the array is sorted.

### Implementation

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
     int t;
     cin >> t;
     while (t--) {
          long long n, k;
          cin >> n >> k;
          vector<long long> arr(n);
          for (int i = 0; i < n; i++) {
                cin >> arr[i];
          }
          vector<long long> temp = arr;
          sort(temp.begin(), temp.end());

          if (arr == temp || k > 1) {
                cout << "YES" << endl;
          } else {
                cout << "NO" << endl;
          }
     }
     return 0;
}
```

### Summary Table

| Case                | Output |
|---------------------|--------|
| Already sorted      | YES    |
| k > 1               | YES    |
| k = 1, not sorted   | NO     |

### Final Notes

- Always check if the array is already sorted.
- For any `k > 1`, sorting is always possible.
- For `k = 1`, only already sorted arrays are valid.
