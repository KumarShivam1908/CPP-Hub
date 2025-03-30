# 347. Top K Frequent Elements

## Problem Statement
Given an integer array `nums` and an integer `k`, return the `k` most frequent elements. You may return the answer in any order.

## Examples

**Example 1:**
```
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
```

**Example 2:**
```
Input: nums = [1], k = 1
Output: [1]
```

## Constraints
- 1 <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4
- k is in the range [1, the number of unique elements in the array].
- It is guaranteed that the answer is unique.

## Approach 1: Hash Map + Max Heap

### Algorithm
1. Count frequency of each element using a hash map
2. Use a max heap (priority queue) to store elements by frequency
3. Extract the top k elements from the heap

### Implementation
```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for(int i=0; i<nums.size(); i++){
            freq[nums[i]]++;
        }
        
        // Create a priority queue and store elements according to their frequency
        priority_queue<pair<int,int>> pq;
        for(auto it=freq.begin(); it!=freq.end(); it++){
            pq.push({it->second, it->first});
        }
        
        vector<int> ans;
        // Pop k elements from the priority queue and store them in the ans vector
        for(int i=0; i<k; i++){
            ans.push_back(pq.top().second);
            pq.pop();
        }        
        return ans;
    }
};
```

### Dry Run
Example: nums = [1,1,1,2,2,3], k = 2

1. Count frequencies:
   - freq[1] = 3
   - freq[2] = 2
   - freq[3] = 1

2. Build max-heap based on frequencies:
   - Insert (3, 1): pq = [(3, 1)]
   - Insert (2, 2): pq = [(3, 1), (2, 2)]
   - Insert (1, 3): pq = [(3, 1), (2, 2), (1, 3)]

3. Extract k=2 elements:
   - Pop (3, 1): ans = [1]
   - Pop (2, 2): ans = [1, 2]

4. Return ans = [1, 2]

### Complexity Analysis
- **Time Complexity**: O(n log n)
  - Building frequency map: O(n)
  - Creating priority queue: O(n log n)
  - Extracting k elements: O(k log n)
- **Space Complexity**: O(n)

## Approach 2: Bucket Sort

### Algorithm
1. Count frequency of each element
2. Create n buckets where bucket[i] contains elements appearing i times
3. Collect top k elements from highest frequency buckets

### Implementation
```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int n = nums.size();
        
        // Count frequencies
        for(int num : nums) {
            freq[num]++;
        }
        
        // Create buckets
        vector<vector<int>> buckets(n + 1);
        for(auto& [num, count] : freq) {
            buckets[count].push_back(num);
        }
        
        // Collect top k elements
        vector<int> result;
        for(int i = n; i >= 0 && result.size() < k; i--) {
            for(int num : buckets[i]) {
                result.push_back(num);
                if(result.size() == k) break;
            }
        }
        
        return result;
    }
};
```

### Complexity Analysis
- **Time Complexity**: O(n)
- **Space Complexity**: O(n)

## Approach 3: Hash Map + QuickSelect

This approach uses the QuickSelect algorithm to find the kth most frequent element in O(n) average time. It requires partitioning elements based on their frequency counts.

### Complexity Analysis
- **Time Complexity**: O(n) average case, O(n²) worst case
- **Space Complexity**: O(n)
