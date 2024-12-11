/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第 N 个结点
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head->next == nullptr) return nullptr;
        int len = 0;
        ListNode* p = head;
        while(p != nullptr)
        {
            len++;
            p = p->next;
        }
        int pos = len - n - 1;
        if(pos < 0)
            return head->next;
        ListNode* front = head;
        while(pos--)
        {
            front = front->next;
        }
        front->next = front->next->next;
        return head;
    }
};

// @lc code=end

/*
只用遍历一次
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int len = 0;
        ListNode* p = head;
        ListNode* q = head;
        while(n--)
        {
            p = p->next;
        }
        if(p == nullptr) return head->next;
        while(p->next != nullptr)
        {
            p = p->next;
            q = q->next;
        }
        q->next = q->next->next;
        return head;
    }
};
*/

/* 
可以构造一个头结点，类似于保存前一个结点，方便删除节点，而且不用判断
p是否为空，上面的代码判断p为空是因为，删除的就是第一个节点，p已经走到了
最后的节点，而下面的while循环条件是p->next != nullptr，nullp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* first = head;
        ListNode* second = dummy;
        for (int i = 0; i < n; ++i) {
            first = first->next;
        }
        while (first) {
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
    }
};

作者：力扣官方题解
*/

