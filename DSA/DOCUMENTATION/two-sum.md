# Two Sum

## Problem Information
- **Category**: Algorithms
- **Difficulty**: Easy (55.23%)
- **Likes**: 60919
- **Dislikes**: 2187
- **Tags**: Array, Hash Table
- **Companies**: Adobe, Airbnb, Amazon, Apple, Bloomberg, Dropbox, Facebook, LinkedIn, Microsoft, Uber, Yahoo, Yelp

## Problem Statement

Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

## Examples

### Example 1:
```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
```

### Example 2:
```
Input: nums = [3,2,4], target = 6
Output: [1,2]
```

### Example 3:
```
Input: nums = [3,3], target = 6
Output: [0,1]
```

## Constraints
- 2 <= nums.length <= 10⁴
- -10⁹ <= nums[i] <= 10⁹
- -10⁹ <= target <= 10⁹
- Only one valid answer exists.

## Approaches

### Approach 1: Brute Force
#### Algorithm
- Use two nested loops to check every possible pair of numbers in the array.
- For each number, check if there's another number that adds up to the target.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {}; // No solution found
    }
};
```

#### Complexity Analysis
- **Time Complexity**: O(n²) - We need to check all possible pairs.
- **Space Complexity**: O(1) - No extra space required.

### Approach 2: Two-Pass Hash Table
#### Algorithm
- Create a hash table and store each element's value and its index.
- Iterate through the array again, checking if the complement (target - current number) exists in the hash table.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashmap;
        int n = nums.size();
        
        // First pass: build the hash table
        for (int i = 0; i < n; i++) {
            hashmap[nums[i]] = i;
        }
        
        // Second pass: check for complements
        for (int i = 0; i < n; i++) {
            int complement = target - nums[i];
            // Make sure we don't use the same element twice
            if (hashmap.find(complement) != hashmap.end() && hashmap[complement] != i) {
                return {i, hashmap[complement]};
            }
        }
        
        return {}; // No solution found
    }
};
```

#### Complexity Analysis
- **Time Complexity**: O(n) - We traverse the list twice: once to build the hash table and once to find complements.
- **Space Complexity**: O(n) - The extra space required depends on the number of items stored in the hash table.

### Approach 3: One-Pass Hash Table (Optimal)
#### Algorithm
- Create a hash table to store each element's value and its index.
- While iterating through the array, check if the complement exists in the hash table.
- If it does, we've found our solution; if not, add the current element to the hash table.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Hash map to store number -> index mapping
        unordered_map<int, int> hashmap;
        
        // Iterate through each element in the array
        for (int i = 0; i < nums.size(); i++) {
            // Calculate the complement needed to reach target
            int complement = target - nums[i];
            
            // Check if we've already seen the required complement
            if (hashmap.find(complement) != hashmap.end()) {
                // Found a pair! Return both indices
                return {hashmap[complement], i};
            } else {
                // Store current number and its index for future lookups
                hashmap[nums[i]] = i;
            }
        }
        
        // Problem guarantees a solution, so this is just a fallback
        return {};
    }
};
```

#### Complexity Analysis
- **Time Complexity**: O(n) - We traverse the list only once. Each lookup in the hash table costs O(1) on average.
- **Space Complexity**: O(n) - The extra space required depends on the number of items stored in the hash table.

## Follow-up
The problem asks for an algorithm with less than O(n²) time complexity, which is achieved by both hash table approaches with O(n) time complexity. The optimal solution is the one-pass hash table method, which combines building the hash table and finding the solution in a single pass.
