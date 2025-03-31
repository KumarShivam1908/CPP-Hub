/*
 * @lc app=leetcode id=680 lang=cpp
 *
 * [680] Valid Palindrome II
 */

// @lc code=start
class Solution {
public:
    bool isPalindrome(string s){
        int l = 0 , r = s.size() - 1;
        while(l < r){
            if(s[l] != s[r]){
                return false;
            }
            l++;
            r--;
        }
        return true;
    }
    bool validPalindrome(string s) {
        int l = 0 ;
        int r = s.size()-1;

        while(l < r ){
            if(s[l] != s[r]){
                return isPalindrome(s.substr(0,l)+s.substr(l+1)) || isPalindrome(s.substr(0,r)+s.substr(r+1));
            }
            l++;
            r--;
        }
        return true;
    }
};
// @lc code=end

