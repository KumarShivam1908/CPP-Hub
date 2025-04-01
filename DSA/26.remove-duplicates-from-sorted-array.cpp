/*
 * @lc app=leetcode id=26 lang=cpp
 *
 * [26] Remove Duplicates from Sorted Array
 */

// @lc code=start
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // TWO POINTER APPROACH
        int i=0;
        int j=0;

        int n = nums.size();

        while(j < n){
            nums[i] = nums[j];
            while(j < n && nums[i]==nums[j]){
                j++;
            }
            i++;
        }
        return i;
    }
    
};
// @lc code=end

