/*
 * @lc app=leetcode id=88 lang=cpp
 *
 * [88] Merge Sorted Array
 */

// @lc code=start
class Solution {
    public:
        void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
            vector<int> result; // Start with an empty vector
            int num1_start = 0, num2_start = 0;
    
            // Merge two sorted arrays
            while (num1_start < m && num2_start < n) {
                if (nums1[num1_start] <= nums2[num2_start]) {
                    result.push_back(nums1[num1_start++]);
                } else {
                    result.push_back(nums2[num2_start++]);
                }
            }
    
            // Add remaining elements from nums1
            while (num1_start < m) {
                result.push_back(nums1[num1_start++]);
            }
    
            // Add remaining elements from nums2
            while (num2_start < n) {
                result.push_back(nums2[num2_start++]);
            }
    
            // Copy back to nums1
            nums1 = result;
        }
    };
// @lc code=end



