/*
 * @lc app=leetcode id=682 lang=cpp
 *
 * [682] Baseball Game
 */

// @lc code=start
class Solution {
public:
    int calPoints(vector<string>& operations) {
        stack<int> st;

        for(int i=0 ; i < operations.size();i++){
            if(operations[i]=='C'){
                st.pop();
            }else if(operations[i]=='D'){
                int top = st.top();
                st.push(top*2);
            }else if(operations[i]=='+'){
                int last = st.top();
                st.pop();
                int secondLast = st.top();
                st.push(last);
                st.push(last+secondLast);
            }else{
                st.push(stoi(operations[i]));
            }
        }

        return sum(st);
    }
};
// @lc code=end

