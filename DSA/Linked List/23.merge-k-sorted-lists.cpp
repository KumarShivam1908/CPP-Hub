/*
 * @lc app=leetcode id=23 lang=cpp
 *
 * [23] Merge k Sorted Lists
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
            ListNode dummy(0);
            ListNode* current = &dummy;
    
            while (list1 && list2) {
                if (list1->val < list2->val) {
                    current->next = list1;
                    list1 = list1->next;
                } else {
                    current->next = list2;
                    list2 = list2->next;
                }
                current = current->next;
            }
    
            current->next = list1 ? list1 : list2; // Attach the remaining nodes
            return dummy.next;
        }
    
        ListNode* mergeKLists(vector<ListNode*>& lists) {
            if (lists.empty()) return nullptr;
    
            while (lists.size() > 1) {
                vector<ListNode*> newLists;
    
                for (int i = 0; i < lists.size(); i += 2) {
                    ListNode* l1 = lists[i];
                    ListNode* l2 = (i + 1 < lists.size()) ? lists[i + 1] : nullptr;
                    newLists.push_back(mergeTwoLists(l1, l2));
                }
    
                lists = newLists; // Update the list of merged lists
            }
    
            return lists[0]; // The final merged list
        }
    };
    
// @lc code=end

