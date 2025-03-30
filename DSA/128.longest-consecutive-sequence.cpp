/*
 * @lc app=leetcode id=128 lang=cpp
 *
 * [128] Longest Consecutive Sequence
 */

// @lc code=start
class Solution {
public:
    /**
     * @brief Finds the length of the longest consecutive elements sequence in an array.
     * 
     * This function uses a hash set to efficiently find consecutive sequences. For each number,
     * it checks if it's the start of a sequence (by verifying the number - 1 is not in the set),
     * then counts how many consecutive numbers follow it.
     * 
     * Time Complexity: O(n) where n is the number of elements in the array.
     * Space Complexity: O(n) for storing the elements in the hash set.
     * 
     * @param nums Vector of integers to search for consecutive sequences
     * @return int Length of the longest consecutive sequence
     */
    int longestConsecutive(vector<int>& nums) {
        // Create an unordered set to store unique elements from the array
        unordered_set<int> numset(nums.begin(), nums.end());
    
        int lcs = 0;  // Variable to keep track of the longest consecutive sequence
        int cur = 0;  // Variable to store the length of the current sequence
    
        // Iterate through each unique number in the set
        for (auto num : numset) {
            // Check if 'num' is the starting point of a sequence
            // A number is the start of a sequence if there is no smaller number before it
            if (numset.find(num - 1) == numset.end()) {
                cur = 1;  // Start a new sequence with this number
                
                // Continue checking if the next consecutive number exists in the set
                while (numset.find(num + 1) != numset.end()) {
                    cur++;  // Increase the count of the current sequence
                    num++;  // Move to the next number in the sequence
                }
                
                // Update the longest sequence length found so far
                lcs = max(lcs, cur);
            }
        }
    
        // Return the length of the longest consecutive sequence found
        return lcs;
    }
    
};
// @lc code=end

