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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *dummy=new ListNode(-1);
        dummy->next=head;
        ListNode *groupPrev=dummy;

        ListNode* next = head;
        ListNode* cur = head;

        int sz = 0;
        while (next != nullptr) {
            sz++;
            next = next->next;
            if (sz == k) {
                ListNode* groupTail = cur;
                ListNode* prev = next;
                while (sz--) {
                    ListNode* next2 = cur->next;
                    cur->next = prev;
                    prev = cur;
                    cur = next2;
                }
                groupPrev->next = prev;
                groupPrev = groupTail;
                sz=0;
            }
        }
        return dummy->next;
    }
};
