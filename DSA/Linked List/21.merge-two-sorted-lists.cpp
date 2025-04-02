/*
 * @lc app=leetcode id=21 lang=cpp
 *
 * [21] Merge Two Sorted Lists
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
        ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
            // Create a dummy node as the starting point of our result list
            // This eliminates the need for special handling of the first node
            ListNode dummy(0);
              
            // 'current' will track the last node in our growing result list
            ListNode* current = &dummy;
              
            // Continue processing while there are nodes in both lists
            while (list1 && list2) {
                // Compare the values of the current nodes in both lists
                if (list1->val < list2->val) {
                    // If list1's node has smaller value, add it to our result
                    current->next = list1;
                    // Move forward in list1
                    list1 = list1->next;
                }else{
                    // If list2's node has smaller or equal value, add it to our result
                    current->next = list2;
                    // Move forward in list2
                    list2 = list2->next;
                }
                    
                // Advance our pointer in the result list
                current = current->next;
            }
            // At this point, at least one of the lists is empty
            if(list1) {
                // If there are remaining nodes in list1, append them to the result
                current->next = list1;
            }else{
                // If there are remaining nodes in list2, append them to the result
                current->next = list2;
            }


              return dummy.next;
        }


    };
// @lc code=end

