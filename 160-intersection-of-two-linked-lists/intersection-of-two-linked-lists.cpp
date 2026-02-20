/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    int getLength(ListNode *head){
        int len = 0 ;
        while(head){
            len++ ;
            head = head->next ;
        }
        return len ;
    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == NULL || headB == NULL) {
            return NULL ;
        }
        // find length of both lists
        int lenA = getLength(headA) ;
        int lenB = getLength(headB) ;

        // find diff and traverse diff in bigger ll
        int diff = abs(lenA - lenB) ;
        if(lenA >= lenB){
            while(diff--) {
                headA = headA->next ;
            } 
        } else {
            while(diff--) {
                headB = headB->next ;
            }
        }

        // traverse together and check for match
        while(headA && headB){
            if(headA == headB) {
                return headA ;    // first match
            }     
            headA = headA->next ;
            headB = headB->next ;
        }
        return NULL ;        // no intersection point
    }
};