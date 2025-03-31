/*
 * @lc app=leetcode id=42 lang=cpp
 *
 * [42] Trapping Rain Water
 */

// @lc code=start
class Solution {
public:
    int trap(vector<int>& height) {
        if(height.size()==0) return 0;
        int n = height.size();
        int l = 0, r = n - 1;
        int leftMax = height[l], rightMax = height[r];
        int ans = 0;

        while(l < r ){
            if(leftMax < rightMax){
                l++;
                leftMax = max(leftMax, height[l]);
                ans += leftMax - height[l];
            }else{
                r--;
                rightMax = max(rightMax,height[r]);
                ans += rightMax - height[r];
            }
        }
        return ans;
    }
};
// @lc code=end

