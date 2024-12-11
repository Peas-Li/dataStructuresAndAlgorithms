/*
 * @lc app=leetcode.cn id=61 lang=cpp
 *
 * [61] 旋转链表
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
    ListNode* rotateRight(ListNode* head, int k) {
        int len = 0;
        int pos;
        ListNode* p = head;
        ListNode* temphead = new ListNode(0, head);
        ListNode* q = temphead;
        for(; p != nullptr; p = p->next)
            len++;
        if(len == 0) return head;
        pos = k % len;
        if(pos == 0) return head;
        p = head;
        while(pos--)
            p = p->next;
        while(p != nullptr)
        {
            p = p->next;
            q = q->next;
        }
        p = q->next;
        q->next = nullptr;
        q = temphead->next;
        temphead->next = p;
        while(p->next != nullptr)
            p = p->next;
        p->next = q;
        ListNode* newHead = temphead->next;
        delete temphead;
        return newHead;
    }
};
// @lc code=end

/*
不需要其他节点保存前一个节点，只需要iter，遍历到nullptr的前一个结点后，
把尾指针链接到头指针上，然后遍历len-pos个节点，把iter->next指向空即可

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (k == 0 || head == nullptr || head->next == nullptr) {
            return head;
        }
        int n = 1;
        ListNode* iter = head;
        while (iter->next != nullptr) {
            iter = iter->next;
            n++;
        }
        int add = n - k % n;
        if (add == n) {
            return head;
        }
        iter->next = head;
        while (add--) {
            iter = iter->next;
        }
        ListNode* ret = iter->next;
        iter->next = nullptr;
        return ret;
    }
};

作者：力扣官方题解
*/