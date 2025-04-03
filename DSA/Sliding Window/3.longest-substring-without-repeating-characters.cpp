/*
 * @lc app=leetcode id=3 lang=cpp
 *
 * [3] Longest Substring Without Repeating Characters
 */

// @lc code=start
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // Sliding Window Approach
        int l , r = 0; // left pointer and right pointer
        int maxLength = 0;
        // create a hashset
        unordered_set<char> stringset;
        for(r=0;r<s.size();r++){
            while(stringset.find(s[r]) != stringset.end()){
                stringset.erase(s[l]);
                l++;
            }
            stringset.insert(s[r]);
            maxLength = max(maxLength,r-l+1);
        }

        return maxLength;
    }
};
// @lc code=end

