class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;

        Node* curr = head;
        while (curr != nullptr) {
            Node* clone = new Node(curr->val);
            clone->next = curr->next;
            curr->next = clone;
            curr = clone->next;
        }

        curr = head;
        while (curr != nullptr) {
            if (curr->random != nullptr) {
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }

        curr = head;
        Node* cloneHead = head->next;
        Node* cloneCurr = cloneHead;

        while (curr != nullptr) {
            curr->next = curr->next->next;
            
            if (cloneCurr->next != nullptr) {
                cloneCurr->next = cloneCurr->next->next;
            }
            curr = curr->next;
            cloneCurr = cloneCurr->next;
        }
        return cloneHead;
    }
};