/*
 * @lc app=leetcode id=27 lang=cpp
 *
 * [27] Remove Element
 */

// @lc code=start
class Solution {
    public:
        int removeElement(vector<int>& nums, int val) {
            vector<int> res;
            for(int i=0;i<nums.size();i++){
                if(nums[i]!=val){
                    res.push_back(nums[i]);
                }
            }
            nums = res;
            return res.size();
        }
    };
// @lc code=end

