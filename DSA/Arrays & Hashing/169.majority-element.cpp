/*
 * @lc app=leetcode id=169 lang=cpp
 *
 * [169] Majority Element
 */

// @lc code=start
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // create a hashmap to store the count of each element
        unordered_map<int,int> countMap;
        // iterate through the array and count the occurrences of each element
        for(int i=0;i<nums.size();i++){
            countMap[nums[i]]++; // increment the count of the current element
            
            // if the count of the current element is greater than half the size of the array, return it
            if(countMap[nums[i]] > nums.size()/2){
                return nums[i];
            }

             // this line will never be reached, but is needed to avoid compilation error
        }
        return -1;
    }
};
// @lc code=end

