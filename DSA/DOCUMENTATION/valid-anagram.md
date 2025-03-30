# Valid Anagram

## Problem Information

| Category    | Difficulty      | Likes | Dislikes |
|-------------|-----------------|-------|----------|
| Algorithms  | Easy (66.26%)   | 12854 | 425      |

## Description

Given two strings `s` and `t`, return `true` if `t` is an anagram of `s`, and `false` otherwise.

An **anagram** is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

## Examples

### Example 1:

```
Input: s = "anagram", t = "nagaram"
Output: true
```

### Example 2:

```
Input: s = "rat", t = "car"
Output: false
```

## Constraints

- 1 <= s.length, t.length <= 5 * 10^4
- `s` and `t` consist of lowercase English letters.

## Approach

### 1. Brute Force Approach
The most intuitive approach would be to:
- Generate all possible permutations of string `s`
- Check if any permutation matches string `t`

**Time Complexity**: O(n!), where n is the length of the string
**Space Complexity**: O(n)

This is extremely inefficient for longer strings.

### 2. Sorting Approach
- Sort both strings
- Check if the sorted strings are identical

**Time Complexity**: O(n log n), dominated by the sorting operation
**Space Complexity**: O(1) if sorting in place, otherwise O(n)

```cpp
bool isAnagram(string s, string t) {
    if(s.length() != t.length()) return false;
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
}
```

### 3. Hash Map Approach (Optimal)
- Count frequency of each character in both strings
- Compare the frequencies

**Time Complexity**: O(n), where n is the length of the string
**Space Complexity**: O(1) since alphabet size is fixed (26 letters)

## Optimal Solution

### Intuition
For two strings to be anagrams, they must contain the same characters with the same frequency. We can use a hash map to count character occurrences in the first string, then decrement counts while checking the second string.

### Implementation

```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        // If their length is not equal, they can't be anagram
        if(s.length()!=t.length()){
            return false;
        }
        // Creating a hash map to store the frequency of each character
        unordered_map<char,int> hashmap;
        // Iterating through the first string
        for(int i=0;i<s.length();i++){
            // Incrementing the frequency of the character
            hashmap[s[i]]++;
        }
        // Iterating through the second string
        for(int i=0;i<t.length();i++){
            // Decrementing the frequency of the character
            hashmap[t[i]]--;
            // If the frequency becomes negative, return false
            if(hashmap[t[i]]<0){
                return false;
            }
        }
        // If all the frequencies are zero, return true
        return true;
    }   
};
```

### Time Complexity Analysis
- First check for length equality: O(1)
- Creating the hash map: O(1)
- First loop to count frequencies: O(n)
- Second loop to verify frequencies: O(n)
- Overall time complexity: O(n)

### Space Complexity
- We use a hash map that stores at most 26 characters (lowercase English letters): O(1)

## Follow-up

If the inputs contain Unicode characters, our hash map approach still works with minimal adjustment. Since Unicode has far more characters than the English alphabet, we can't use a fixed-size array of 26 elements, but the `unordered_map` in our solution already handles this case correctly. The time and space complexity would remain O(n) and O(k) respectively, where k is the number of unique characters in the input.