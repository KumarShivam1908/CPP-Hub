/*
 * @lc app=leetcode id=234 lang=cpp
 *
 * [234] Palindrome Linked List
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode * slow = head;
        ListNode * fast = head;

        // Find the middle of the linked list
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }

        // Reverse the second half of the linked list
        ListNode * prev = nullptr;
        while(slow){
            ListNode *temp = slow->next;
            slow->next = prev;
            prev = slow;
            slow = temp;
        }
        // Check for palindrome
        ListNode* left = head;
        ListNode* right = prev;
        while(left && right){
            if(left->val != right->val){
                return false;
            }
            left = left->next;
            right = right->next;
        }

        return true;
    }
};
// @lc code=end

