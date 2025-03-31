/*
 * @lc app=leetcode id=344 lang=cpp
 *
 * [344] Reverse String
 */

// @lc code=start
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size()-1;

        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
};
// @lc code=end

