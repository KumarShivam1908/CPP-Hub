/*
 * @lc app=leetcode id=167 lang=cpp
 *
 * [167] Two Sum II - Input Array Is Sorted
 */

// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0 ;
        int right = numbers.size() - 1 ;
        while(left < right){
            int currsum = numbers[left] + numbers[right] ;
            if(currsum > target){
                right--; // we can do this as we know the array is sorted
            }else if (currsum < target ){
                left++;
            }else{
                return {left + 1 , right + 1};
            }
        }

        return {-1,-1}; // this line will never be reached as per the problem statement
    }
};
// @lc code=end

