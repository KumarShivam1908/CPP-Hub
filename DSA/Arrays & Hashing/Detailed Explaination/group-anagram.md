# Group Anagrams

## Problem Description

| Category    | Difficulty       | Likes | Dislikes |
|-------------|------------------|-------|----------|
| algorithms  | Medium (70.48%)  | 20279 | 673      |

### Tags
- Hash Table
- String

### Companies
Amazon, Bloomberg, Facebook, Uber, Yelp

## Problem Statement
Given an array of strings `strs`, group the anagrams together. You can return the answer in any order.

### Examples

**Example 1:**
```
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
```

**Example 2:**
```
Input: strs = [""]
Output: [[""]]
```

**Example 3:**
```
Input: strs = ["a"]
Output: [["a"]]
```

### Constraints
- 1 <= strs.length <= 10^4
- 0 <= strs[i].length <= 100
- strs[i] consists of lowercase English letters.

## Sub-Optimal Solution

### Intuition
When two strings are anagrams, they contain the same characters with the same frequency. This means that if we sort both strings, they will become identical. We can use this property to group anagrams together.

### Approach
1. Iterate through each string in the input array
2. Sort each string to get its character signature
3. Use the sorted string as a key in a hash map, with the value being a list of original strings that sort to this key
4. After processing all strings, convert the hash map values to the result array

### Time Complexity
- Time Complexity: O(n * k log k) where:
    - n is the number of strings in the input array
    - k is the maximum length of a string in the input array
    - For each string, we perform a sort operation that takes O(k log k) time
- Space Complexity: O(n * k) to store the hash map and result

### Code (C++)

```cpp
class Solution {
public:
        vector<vector<string>> groupAnagrams(vector<string>& strs) {
                // Store original string and sorted string in a map
                unordered_map<string, vector<string>> mp;
                
                for(auto str : strs) {
                        string temp = str;
                        sort(temp.begin(), temp.end());
                        mp[temp].push_back(str);
                }
                
                vector<vector<string>> res;
                for(auto it : mp) {
                        res.push_back(it.second);
                }
                
                return res;
        }
};
```

### Walkthrough
Let's trace through the algorithm with the example input: `["eat","tea","tan","ate","nat","bat"]`

1. `"eat"` → sorted to `"aet"` → mp["aet"] = ["eat"]
2. `"tea"` → sorted to `"aet"` → mp["aet"] = ["eat", "tea"]
3. `"tan"` → sorted to `"ant"` → mp["ant"] = ["tan"]
4. `"ate"` → sorted to `"aet"` → mp["aet"] = ["eat", "tea", "ate"]
5. `"nat"` → sorted to `"ant"` → mp["ant"] = ["tan", "nat"]
6. `"bat"` → sorted to `"abt"` → mp["abt"] = ["bat"]

**Final hash map:**
- Key `"aet"` → ["eat", "tea", "ate"]
- Key `"ant"` → ["tan", "nat"]
- Key `"abt"` → ["bat"]

We then convert these values to our result: `[["eat", "tea", "ate"], ["tan", "nat"], ["bat"]]`


## Optimal Solution

### Intuition
Instead of sorting each string (which costs O(k log k) time), we can use a character frequency counter as the key. Since we know the strings only contain lowercase English letters (26 possible characters), we can create a unique signature based on character counts.

### Approach
1. Iterate through each string in the input array
2. For each string, create a frequency counter for all 26 lowercase letters
3. Use this frequency counter as a key in a hash map, with the value being a list of original strings that have this frequency pattern
4. After processing all strings, convert the hash map values to the result array

### Time Complexity
- Time Complexity: O(n * k) where:
    - n is the number of strings in the input array
    - k is the maximum length of a string in the input array
    - For each string, we simply iterate through its characters once
- Space Complexity: O(n * k) to store the hash map and result

### Code (C++)
```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // map to store the anagrams
        unordered_map<string, vector<string>> anagrams;
        // iterate through the strings and create frequency counters
        for(auto str : strs){
            string temp = string(26, '0');
            for(auto c : str){
                temp[c - 'a']++;
            }
            // use frequency counter as key, store original string in the vector
            anagrams[temp].push_back(str);
        }
        // extract the grouped anagrams from the map
        vector<vector<string>> result;
        for(auto it : anagrams){
            result.push_back(it.second);
        }
        return result;
    }
};
```

### Walkthrough
Let's trace through the algorithm with the example input: `["eat","tea","tan","ate","nat","bat"]`

1. `"eat"` → frequency: `e(1), a(1), t(1)` → key: `"10001000000000000000100000"` → anagrams[key] = ["eat"]
2. `"tea"` → frequency: `e(1), a(1), t(1)` → key: `"10001000000000000000100000"` → anagrams[key] = ["eat", "tea"]
3. `"tan"` → frequency: `a(1), n(1), t(1)` → key: `"10000000000001000000100000"` → anagrams[key] = ["tan"]
4. `"ate"` → frequency: `e(1), a(1), t(1)` → key: `"10001000000000000000100000"` → anagrams[key] = ["eat", "tea", "ate"]
5. `"nat"` → frequency: `a(1), n(1), t(1)` → key: `"10000000000001000000100000"` → anagrams[key] = ["tan", "nat"]
6. `"bat"` → frequency: `a(1), b(1), t(1)` → key: `"11000000000000000000100000"` → anagrams[key] = ["bat"]

**Final hash map:**
- Key for `e(1), a(1), t(1)` → ["eat", "tea", "ate"]
- Key for `a(1), n(1), t(1)` → ["tan", "nat"]
- Key for `a(1), b(1), t(1)` → ["bat"]

We then convert these values to our result: `[["eat", "tea", "ate"], ["tan", "nat"], ["bat"]]`