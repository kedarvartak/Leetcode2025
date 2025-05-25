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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* dummy = new ListNode(0);
        dummy -> next = head;

        ListNode* preNext = dummy;
        ListNode* currNode = head;

        for(int i = 0; i < left - 1; i++){
            preNext = preNext -> next;
            currNode = currNode -> next;
        } 

        ListNode* sublisthead = currNode;
        ListNode* preNode = NULL;

        for(int i = 0; i < right - left + 1; i++){
            ListNode* nextNode = currNode -> next;
            currNode -> next = preNode;
            preNode = currNode;
            currNode = nextNode;
        }

        preNext-> next = preNode;
        sublisthead -> next = currNode;

        return dummy-> next;
    }
};