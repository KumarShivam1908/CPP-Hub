/*
 * @lc app=leetcode id=219 lang=cpp
 *
 * [219] Contains Duplicate II
 */

// @lc code=start
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        //SLIDING WINDOW TECHNIQUE
        // use a hash set to store the elements in the current window of size k
        unordered_set<int> window;
        int l = 0; // left pointer of the window
        for(int r=0;r<nums.size();r++){
            if(r-l > k){
                // if the window size exceeds k, remove the leftmost element from the set
                window.erase(nums[l]);
                l++;
            }
            // check if the current element is already in the set
            if(window.find(nums[r]) != window.end()){
                // if it is, return true
                return true;
            }
            // add the current element to the set
            window.insert(nums[r]);
        }
        // if no duplicates are found in the window, return false
        return false;
    }
};
// @lc code=end

