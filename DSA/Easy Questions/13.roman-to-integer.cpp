/*
 * @lc app=leetcode id=13 lang=cpp
 *
 * [13] Roman to Integer
 */

// @lc code=start
class Solution {
public:
    int romanToInt(string s) {
        // Lets first create a hashmap to store the symbols and the value
        unordered_map<char,int> roman = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };
        // Now we will iterate through the string and check if the current symbol is less than the next symbol
        // if current symbol is less than the next symbol then we will subtract the current symbol from the next symbol
        // else we will add the current symbol to the result
        int result = 0;
        for(int i = 0; i < s.size(); i++){
            // if the current symbol is less than the next symbol then we will subtract the current symbol from the next symbol
            if(i < s.size() - 1 && roman[s[i]] < roman[s[i + 1]]){
                result -= roman[s[i]];
            }else{
                // else we will add the current symbol to the result
                result += roman[s[i]];
            }
        }

        return result;


    }
};
// @lc code=end

