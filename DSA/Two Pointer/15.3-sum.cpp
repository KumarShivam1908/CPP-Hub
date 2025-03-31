/*
 * @lc app=leetcode id=15 lang=cpp
 *
 * [15] 3Sum
 */

// @lc code=start
class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            vector<vector<int>> result;  // Fix 1: Correct vector type
            sort(nums.begin() , nums.end());
    
            // Iterate through index and value of nums at same time
            for(int i=0;i<nums.size();i++){
                if( i > 0 && nums[i]==nums[i-1]){
                    continue; // Skip duplicates
                }
                
                int l = i+1;
                int r = nums.size()-1;
                while(l < r ){
                    int threesome =  nums[i] + nums[l] + nums[r];
                    if(threesome > 0 ){
                        r--;
                    }else if(threesome < 0 ){
                        l++;
                    }else{
                        result.push_back({nums[i],nums[l],nums[r]});
                        l++;
                        while(l < r && nums[l] == nums[l-1]){
                            l++; // Skip duplicates
                        }
                    }
    
                }
    
    
            }
            return result;
    
        }
    };
// @lc code=end

