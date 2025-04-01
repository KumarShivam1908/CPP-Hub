/*
 * @lc app=leetcode id=1929 lang=cpp
 *
 * [1929] Concatenation of Array
 */

// @lc code=start
class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        vector<int> result(nums.size()*2);
        int n = nums.size();
        for(int i=0;i<n;i++){
            result[i] = nums[i];
            result[i+n] = nums[i];
        }

        return result;
    }
};
// @lc code=end

