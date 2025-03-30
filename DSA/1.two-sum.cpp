/*
 * @lc app=leetcode id=1 lang=cpp
 *
 * [1] Two Sum
 */

// @lc code=start
class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            // Hash map to store number -> index mapping
            unordered_map<int,int> hashmap;
            
            // Iterate through each element in the array
            for(int i=0;i<nums.size();i++){
                // Calculate the complement needed to reach target
                int diff = target - nums[i];
                
                // Check if we've already seen the required complement
                if(hashmap.find(diff) != hashmap.end()){
                    // Found a pair! Return both indices
                    return {hashmap[diff],i};
                } else {
                    // Store current number and its index for future lookups
                    hashmap[nums[i]] = i;
                }
            }
            
            // Problem guarantees a solution, so this is just a fallback
            return {};
        }
    };
// @lc code=end

