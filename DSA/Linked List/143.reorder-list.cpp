/*
 * @lc app=leetcode id=143 lang=cpp
 *
 * [143] Reorder List
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
    void reorderList(ListNode* head) {
        // Slow and Fast Pointer Approch to reach the middle
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        // Reverse the second half of the list
        ListNode* prev = nullptr;
        ListNode* curr = slow;
        while(curr){
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        // Merge the two halves
        ListNode* first = head;
        ListNode* second = prev; // This is the head of the reversed second half

        while(second->next){
            ListNode * temp1 = first->next;
            ListNode* temp2 = second->next;
            first->next=second;
            second->next = temp1;
            first = temp1;
            second = temp2;
        }

    }
};
// @lc code=end

