/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return NULL;

        Node* curr = head;

        // Step 1: Insert copy nodes
        while(curr){
            Node* temp = new Node(curr->val);
            temp->next = curr->next;
            curr->next = temp;
            curr = temp->next;
        }

        // Step 2: Copy random pointers
        curr = head;
        while(curr){
            if(curr->random)
                curr->next->random = curr->random->next;
            curr = curr->next->next;
        }

        // Step 3: Separate lists
        Node* dummy = new Node(0);
        Node* copy = dummy;
        curr = head;

        while(curr){
            copy->next = curr->next;
            curr->next = curr->next->next;

            copy = copy->next;
            curr = curr->next;
        }

        return dummy->next;
    }
};