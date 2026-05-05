class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) return head;

        // Step 1: Find length
        ListNode* temp = head;
        int n = 1;
        while (temp->next) {
            temp = temp->next;
            n++;
        }

        // Step 2: Make circular
        temp->next = head;

        // Step 3: Reduce k
        k = k % n;

        // Step 4: Find new tail
        int steps = n - k;
        temp = head;
        while (--steps) {
            temp = temp->next;
        }

        // Step 5: Break circle
        ListNode* newHead = temp->next;
        temp->next = NULL;

        return newHead;
    }
};