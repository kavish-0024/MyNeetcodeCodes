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
    ListNode* reverse(ListNode* sp) {
        ListNode *cur = sp, *prev = nullptr;
        while (cur != nullptr) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
    void reorderList(ListNode* head) {
        ListNode *fp = head, *sp = head;
        int count = 0;
        while (fp != nullptr && fp->next != nullptr) {
            fp = fp->next->next;
            count += 2;
            sp = sp->next;
        }
        ListNode* secondHalf = sp->next;
        sp->next = nullptr;

        ListNode* l2 = reverse(secondHalf);
        ListNode* l1 = head;

        while (l2 != nullptr) {
            ListNode* temp1 = l1->next;
            ListNode* temp2 = l2->next;

            l1->next = l2;
            l2->next = temp1;

            l1 = temp1;
            l2 = temp2;
        }
    }
};
