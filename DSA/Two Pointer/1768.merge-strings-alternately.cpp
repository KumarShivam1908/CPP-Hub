/*
 * @lc app=leetcode id=1768 lang=cpp
 *
 * [1768] Merge Strings Alternately
 */

// @lc code=start
#include<string>
class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string result;
        int i = 0; // pointer to word1
        for(int i=0; i<word1.size() && i < word2.size();i++){
            if(i < word1.size()){
                result += word1[i];
            }
            if(i < word2.size()){
                result += word2[i];
            }
        }

        return result;

    }
};
// @lc code=end

