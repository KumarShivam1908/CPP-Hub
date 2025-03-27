/*
 * @lc app=leetcode id=242 lang=cpp
 *
 * [242] Valid Anagram
 */

// @lc code=start

class Solution {
public:
    bool isAnagram(string s, string t) {
        // If their length is not equal , they cant be anagram
        if(s.length()!=t.length()){
            return false;
        }
        // Creating a hash map to store the frquecy of each character
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
            // If the frequency becomes negative , return false
            if(hashmap[t[i]]<0){
                return false;
            }
        }
        // If all the frequencies are zero , return true
        return true;
    }   
};
// @lc code=end

