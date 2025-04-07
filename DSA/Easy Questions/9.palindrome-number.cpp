/*
 * @lc app=leetcode id=9 lang=cpp
 *
 * [9] Palindrome Number
 */

// @lc code=start
class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) return false; // Negative numbers are not palindromes
        string str = to_string(x); // Convert the number to a string
        int left = 0;
        int right = str.size() - 1; // Initialize two pointers
        while(left < right){
            if(str[left] != str[right]) return false; // Check if the characters are equal
            left++; // Move the left pointer to the right
            right--; // Move the right pointer to the left
        }
        return true; // If all characters are equal, it's a palindrome
    }
};
// @lc code=end

