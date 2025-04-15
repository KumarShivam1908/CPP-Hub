/*
 * @lc app=leetcode id=20 lang=cpp
 *
 * [20] Valid Parentheses
 */

// @lc code=start
class Solution {
    public:
        bool isValid(const string& s) {
            stack<char> st;
            const map<char, char> mp = {
                {')', '('},
                {']', '['},
                {'}', '{'}
            };
            
            for(char c : s) {
                if (c == '(' || c == '[' || c == '{') {
                    st.push(c);
                } else {
                    if (st.empty() || st.top() != mp.at(c)) {
                        return false;
                    }
                    st.pop();
                }
            }
            return st.empty();
        }
    };
    
// @lc code=end

