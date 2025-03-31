/*
 * @lc app=leetcode id=125 lang=cpp
 *
 * [125] Valid Palindrome
 */

// @lc code=start
class Solution {
    public:
        bool checkIsAlnum(char c){
            // check using ASCII values for alphanumeric characters
            if((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
                return true;
            }
            return false;
        }
        bool isPalindrome(string s) {
            int left = 0;
            int right = s.size() - 1;
    
            while(left < right){
    
                while(left < right && !checkIsAlnum(s[left])){
                    left++;
                }
                while(left < right && !checkIsAlnum(s[right])){
                    right--;
                }
    
                if(tolower(s[left]) != tolower(s[right])){
                    return false;
                }
                left++;
                right--;
            }
    
            return true;
        }
    };
// @lc code=end

