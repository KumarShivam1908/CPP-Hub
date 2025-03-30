# Contains Duplicate

## Problem Metadata
| Category   | Difficulty    | Likes | Dislikes |
|------------|---------------|-------|----------|
| algorithms | Easy (62.90%) | 12744 | 1323     |

## Tags
- array
- hash-table

## Companies
- airbnb
- palantir
- yahoo

## Problem Statement
Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

## Examples

### Example 1:
```
Input: nums = [1,2,3,1]
Output: true
```
**Explanation:** The element 1 occurs at the indices 0 and 3.

### Example 2:
```
Input: nums = [1,2,3,4]
Output: false
```
**Explanation:** All elements are distinct.

### Example 3:
```
Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true
```

## Constraints
- 1 <= nums.length <= 10^5
- -10^9 <= nums[i] <= 10^9

## Solution Approaches

### 1. Brute Force Approach
- Use nested loops to check if any element appears twice
- Time Complexity: O(n²)
- Space Complexity: O(1)
- Not optimal for large inputs

### 2. Sorting Approach
- Sort the array and check adjacent elements
- Time Complexity: O(n log n)
- Space Complexity: O(1) if sorted in-place
- Better than brute force but not optimal

### 3. Hash Set Approach (Optimal)
- Use a hash set to track seen elements
- Time Complexity: O(n)
- Space Complexity: O(n)
- Most efficient solution for this problem

## Optimal Solution Implementation

```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        // Creating hashset to store the elements
        unordered_set<int> hashset;
        // Iterating through the elements
        for(int i=0;i<nums.size();i++){
            // If the element is already present in the hashset, return true
            if(hashset.find(nums[i])!=hashset.end()){
                return true;
            }
            else{
                hashset.insert(nums[i]);
            }
        }
        return false;
    }
};
```

## Complexity Analysis

- **Time Complexity: O(n)** - We iterate through the array once, and hash set operations (insertion, lookup) are O(1) on average.
- **Space Complexity: O(n)** - In the worst case, we store all elements in the hash set (when all elements are unique).

## Solution Explanation

1. Create an unordered_set (hash set) to track elements we've already seen
2. Iterate through each element in the array
3. For each element:
   - Check if it already exists in the hash set
   - If it does, return true (duplicate found)
   - If not, add it to the hash set
4. If we complete the loop without finding duplicates, return false

This solution is optimal because it achieves linear time complexity while using hash table's O(1) lookup operations.