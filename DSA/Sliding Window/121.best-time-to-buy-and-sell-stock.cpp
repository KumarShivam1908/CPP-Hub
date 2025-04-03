/*
 * @lc app=leetcode id=121 lang=cpp
 *
 * [121] Best Time to Buy and Sell Stock
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // left pointer L = day we buy
        // right pointer R = day we sell
        int L = 0;
        int R = 0;
        int maxProfit = 0;
        while(R < prices.size()){
            if(prices[L] < prices[R]){
                int profit = prices[R] - prices[L];
                maxProfit = max(maxProfit,profit);
            }else{
                L = R;
            }
            R++;
        }
        return maxProfit;
    }
};
// @lc code=end

