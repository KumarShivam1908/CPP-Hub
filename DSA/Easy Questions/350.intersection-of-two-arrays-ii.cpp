/*
 * @lc app=leetcode id=350 lang=cpp
 *
 * [350] Intersection of Two Arrays II
 */

// @lc code=start
class Solution {
    public:
        vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
            unordered_map<int,int> map;
            vector<int> res;
            
            // Step 1: Count frequency of elements in nums1
            for(int num : nums1){
                map[num]++;
            }
    
            // Step 2: Check if elements in nums2 exist in map
            for(int num : nums2){
                if(map[num] > 0){
                    res.push_back(num);
                    map[num]--;
                }
            }
    
            return res;
        }
    };
    
// @lc code=end

