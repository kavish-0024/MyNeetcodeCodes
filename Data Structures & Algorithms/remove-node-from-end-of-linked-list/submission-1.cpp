class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

        ListNode *dummy=new ListNode(-1);
        dummy->next = head;
        
        ListNode *fp = dummy;
        ListNode *sp = dummy;

        for (int i = 0; i <= n; i++) {
            fp = fp->next;
        }

        while (fp != nullptr) {
            fp = fp->next;
            sp = sp->next;
        }
        
        ListNode* toDelete = sp->next;
        sp->next = sp->next->next;
        
        delete toDelete; 
        
        return dummy->next;
    }
};