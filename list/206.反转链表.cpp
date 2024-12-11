/*
 * @lc app=leetcode.cn id=206 lang=cpp
 *
 * [206] 反转链表
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
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr || head->next == nullptr)
            return head;
        ListNode* k = head;
        ListNode* p = head->next;
        ListNode* q = p->next;
        k->next = nullptr;
        while(p != nullptr)
        {
            q = p->next;
            p->next = k;
            k = p;
            p = q;
        }
        return k;
    }
};
// @lc code=end

