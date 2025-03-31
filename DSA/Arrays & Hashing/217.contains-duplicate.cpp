/*
 * @lc app=leetcode id=217 lang=cpp
 *
 * [217] Contains Duplicate
 */

// @lc code=start
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        // Creating hashset to store the elements
        unordered_set<int> hashset;
        // Iterating through the elements
        for(int i=0;i<nums.size();i++){
            // If the element is already present in the hashset , return true
            if(hashset.find(nums[i])!=hashset.end()){
                return true;
            }
            else{
                hashset.insert(nums[i]);
            }
        }
        return false;
        
    }
};
// @lc code=end

