/*
 * @lc app=leetcode id=58 lang=cpp
 *
 * [58] Length of Last Word
 */

// @lc code=start
class Solution {
    public:
        int lengthOfLastWord(string s) {
            int i = s.length()-1;
            int ans = 0;
            while(i >=0 && s[i]==' '){
                i--;
            }
            while(i>=0 && s[i] != ' '){
                ans++;
                i--;
            }
    
            return ans;
    
            
    }
};
// @lc code=end

