/*
 * @lc app=leetcode.cn id=142 lang=cpp
 *
 * [142] 环形链表 II
 */

// @lc code=start
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
    ListNode *detectCycle(ListNode *head) {
        ListNode* first = head;
        ListNode* second = head;
        ListNode* pos = head;
        while(second != nullptr && second->next != nullptr)
        {
            first = first->next;
            second = second->next->next;;
            if(first == second)
            {
                while(pos != first)
                {
                    pos = pos->next;
                    first = first->next;
                }
                return  pos;
            }
        }
        return nullptr;
    }
};
// @lc code=end

