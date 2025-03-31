/*
 * @lc app=leetcode id=238 lang=cpp
 *
 * [238] Product of Array Except Self
 */

// @lc code=start
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> prefix(nums.size(), 1);
        vector<int> postfix(nums.size(), 1);
        
        prefix[0]=1;
        for(int i=1;i<nums.size();i++){
            prefix[i] = nums[i-1] * prefix[i-1];
        }
        postfix[nums.size()-1]=1;
        for(int i=nums.size()-2;i>=0;i--){
            postfix[i] = nums[i+1] * postfix[i+1];
        }
        vector<int> result(nums.size(), 1);
        for(int i=0;i<nums.size();i++){
            result[i]= prefix[i] * postfix[i];
        }
        return result;
    }
};
// @lc code=end

