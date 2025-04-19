/*
 * @lc app=leetcode id=448 lang=cpp
 *
 * [448] Find All Numbers Disappeared in an Array
 */

// @lc code=start
class Solution {
    public:
        vector<int> findDisappearedNumbers(vector<int>& nums) {
            unordered_map<int, int> freq;
    
            for (int num : nums){
                freq[num]++;
            }
            vector<int> result;
            int n = nums.size();
    
            // Check which numbers from 1 to n are missing
            for (int i = 1; i <= n; ++i) {
                if (freq.find(i) == freq.end()) {
                    result.push_back(i);
                }
            }
    
            return result;
    
        }
    };
// @lc code=end

