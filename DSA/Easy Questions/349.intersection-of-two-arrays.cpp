/*
 * @lc app=leetcode id=349 lang=cpp
 *
 * [349] Intersection of Two Arrays
 */

// @lc code=start
class Solution {
    public:
        vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
            unordered_set<int> set1(nums1.begin(), nums1.end());
            unordered_set<int> result;
    
            for (int num : nums2) {
                // Check if the number is in the first set
                // If it is, add it to the result set
                // This ensures that each number is only added once
                // even if it appears multiple times in nums2
                if (set1.count(num)) {
                    result.insert(num);
                }
            }
    
            return vector<int>(result.begin(), result.end());
        }
    };
    
// @lc code=end

