# Product of Array Except Self

## Problem

| Category    | Difficulty      | Likes | Dislikes |
|-------------|-----------------|-------|----------|
| algorithms  | Medium (67.45%) | 23880 | 1535     |

### Tags
array

### Companies
amazon | apple | facebook | linkedin | microsoft

Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all the elements of `nums` except `nums[i]`.

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

### Example 1:
```
Input: nums = [1,2,3,4]
Output: [24,12,8,6]
```

### Example 2:
```
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
```

### Constraints:
- 2 <= nums.length <= 10^5
- -30 <= nums[i] <= 30
- The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

### Follow up:
Can you solve the problem in O(1) extra space complexity? (The output array does not count as extra space for space complexity analysis.)

## Approach 1: Brute Force

### Intuition
For each element in the array, calculate the product of all other elements by iterating through the array and skipping the current element.

### Code
```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> result(nums.size(), 1);
        for(int i = 0; i < nums.size(); i++) {
            for(int j = 0; j < nums.size(); j++) {
                if(i == j) {
                    continue;
                } else {
                    result[i] *= nums[j];
                }
            }
        }
        return result;        
    }
};
```

### Time Complexity
- O(n²) - We have two nested loops, each iterating through the array of size n.

### Space Complexity
- O(1) extra space (excluding output array).


## Approach 2: Using Prefix and Postfix Arrays

## Intuition
This approach explicitly maintains separate prefix and postfix arrays to compute the product of all elements except the current one.

### Steps:
1. **Prefix Array:** Stores cumulative product of elements before the current index.
2. **Postfix Array:** Stores cumulative product of elements after the current index.
3. **Final Calculation:** Multiply corresponding values from the prefix and postfix arrays to get the result.

---

## Dry Run
### **Input:** `nums = [1,2,3,4]`

### **Prefix Calculation:**
- `prefix[0] = 1`
- `i = 1`: `prefix[1] = nums[0] * prefix[0] = 1 * 1 = 1`
- `i = 2`: `prefix[2] = nums[1] * prefix[1] = 2 * 1 = 2`
- `i = 3`: `prefix[3] = nums[2] * prefix[2] = 3 * 2 = 6`
- **Prefix array:** `[1, 1, 2, 6]`

### **Postfix Calculation:**
- `postfix[3] = 1`
- `i = 2`: `postfix[2] = nums[3] * postfix[3] = 4 * 1 = 4`
- `i = 1`: `postfix[1] = nums[2] * postfix[2] = 3 * 4 = 12`
- `i = 0`: `postfix[0] = nums[1] * postfix[1] = 2 * 12 = 24`
- **Postfix array:** `[24, 12, 4, 1]`

### **Final Calculation:**
- `result[i] = prefix[i] * postfix[i]`
- `result = [24, 12, 8, 6]`

---
## Code
```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> prefix(nums.size(), 1);
        vector<int> postfix(nums.size(), 1);
        
        prefix[0]=1;
        for(int i=1;i<nums.size();i++){
            prefix[i] = nums[i-1] * prefix[i-1];
        }
        postfix[nums.size()-1]=1;
        for(int i=nums.size()-2;i>=0;i--){
            postfix[i] = nums[i+1] * postfix[i+1];
        }
        vector<int> result(nums.size(), 1);
        for(int i=0;i<nums.size();i++){
            result[i]= prefix[i] * postfix[i];
        }
        return result;
    }
};
```

## Time Complexity
- **Prefix Computation:** O(n)
- **Postfix Computation:** O(n)
- **Final Computation:** O(n)
- **Overall Complexity:** O(n)

## Space Complexity
- **Prefix Array:**  O(n)
- **Postfix Array:**  O(n)
- **Result Array:**  O(n) (not counted in extra space analysis)
- **Total Extra Space:**  O(n) (due to prefix and postfix arrays)

## Comparison with Optimal Solution
- This approach requires **O(n) extra space**, whereas the optimal approach reduces space to **O(1)** by computing prefix and postfix on the result array itself.
- However, this approach is easier to understand conceptually as it explicitly stores prefix and postfix values.


## Approach 3: Prefix and Postfix Products

## Intuition
Instead of calculating the product for each element separately, we can use the concept of prefix and postfix products:
1. For each position `i`, calculate the product of all elements to the left (prefix).
2. For each position `i`, calculate the product of all elements to the right (postfix).
3. The final result at position `i` is `prefix[i] * postfix[i]`.

## Dry Run
For array `[1,2,3,4]`:

### First Pass (Prefix Calculation):
We initialize `result` with `1`s:

```cpp
result = [1, 1, 1, 1]
```

Now, we compute the **prefix products**:

```cpp
prefix = 1
result[0] = 1 // no elements to the left
prefix = prefix * nums[0] = 1 * 1 = 1
result[1] = prefix = 1
prefix = prefix * nums[1] = 1 * 2 = 2
result[2] = prefix = 2
prefix = prefix * nums[2] = 2 * 3 = 6
result[3] = prefix = 6
prefix = prefix * nums[3] = 6 * 4 = 24
```

After first pass:
```cpp
result = [1, 1, 2, 6]
```

### Second Pass (Postfix Calculation):
We initialize `postfix = 1` and traverse from **right to left**, multiplying each `result[i]` by the **postfix product**.

```cpp
postfix = 1
result[3] = result[3] * postfix = 6 * 1 = 6
postfix = postfix * nums[3] = 1 * 4 = 4
result[2] = result[2] * postfix = 2 * 4 = 8
postfix = postfix * nums[2] = 4 * 3 = 12
result[1] = result[1] * postfix = 1 * 12 = 12
postfix = postfix * nums[1] = 12 * 2 = 24
result[0] = result[0] * postfix = 1 * 24 = 24
```

Final result:
```cpp
result = [24, 12, 8, 6]
```

## Code Implementation
```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> result(nums.size(), 1);
        
        // Calculate prefix products and store in result
        int prefix = 1;
        for(int i = 0; i < nums.size(); i++) {
            result[i] = prefix;
            prefix *= nums[i];
        }
        
        // Calculate postfix products on the fly and multiply with prefix
        int postfix = 1;
        for(int i = nums.size() - 1; i >= 0; i--) {
            result[i] *= postfix;
            postfix *= nums[i];
        }
        
        return result;
    }
};
```

## Time Complexity
- **O(n)** - We make two passes through the array, each taking O(n) time.

## Space Complexity
- **O(1) extra space** (excluding output array) - We only use two additional variables.

This ensures an efficient solution without extra space usage apart from the output array.




