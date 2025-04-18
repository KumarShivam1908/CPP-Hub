/*
 * @lc app=leetcode id=485 lang=cpp
 *
 * [485] Max Consecutive Ones
 */

// @lc code=start
class Solution {
    public:
        int findMaxConsecutiveOnes(vector<int>& nums) {
            int cnt = 0, maxi = 0;
            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] == 1) {
                    cnt++;
                    maxi = max(maxi, cnt);
                } else {
                    cnt = 0;
                }
            }
            return maxi;
        }
    };
    
// @lc code=end

