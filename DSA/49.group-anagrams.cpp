/*
 * @lc app=leetcode id=49 lang=cpp
 *
 * [49] Group Anagrams
 */

// @lc code=start
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // map to store the anagrams
        unordered_map<string, vector<string>> anagrams;
        // iterate through the strings and then for a string of 26 characters, where frequence of each character is stored ,  ex - abc it would be 11100000000000000000000000
        for(auto str:strs){
            string temp = string(26,'0');
            for(auto c:str){
                temp[c-'a']++;
            }
            // now we have the frequency of each character in the string and our key is string  and value is the vector of strings
            anagrams[temp].push_back(str);

        }
        // now we have the anagrams stored in the map, we just need to return the values of the map
        vector<vector<string>> result;
        for(auto it:anagrams){
            result.push_back(it.second);
        }
        return result;

    }
};
// @lc code=end

