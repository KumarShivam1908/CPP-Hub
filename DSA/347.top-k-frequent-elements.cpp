/*
 * @lc app=leetcode id=347 lang=cpp
 *
 * [347] Top K Frequent Elements
 */

// @lc code=start
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for(int i=0;i<nums.size();i++){
            freq[nums[i]]++;
        }
        // create a priority ques and store elements according to their frequency
        priority_queue<pair<int,int>> pq;
        for(auto it=freq.begin();it!=freq.end();it++){
            pq.push({it->second,it->first});
        }
        vector<int> ans;
        // pop k elements from the priority queue and store them in the ans vector
        for(int i=0;i<k;i++){
            ans.push_back(pq.top().second);
            pq.pop();
        }        
        return ans;
    }
};
// @lc code=end

