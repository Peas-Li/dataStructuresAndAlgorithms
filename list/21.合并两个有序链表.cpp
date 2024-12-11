/*
 * @lc app=leetcode.cn id=21 lang=cpp
 *
 * [21] 合并两个有序链表
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(list1 == nullptr)    return list2;
        if(list2 == nullptr)    return list1;

        ListNode* head;
        
        if(list1->val < list2->val)
        {
            head = list1;
            list1 = list1->next;
        }
        else
        {
            head = list2;
            list2 = list2->next;
        }
        ListNode* k = head;;
        while(list1 != nullptr && list2 != nullptr)
        {
            if(list1->val <= list2->val)
            {
                k->next = list1;
                list1 = list1->next;
            }
            else
            {
                k->next = list2;
                list2 = list2->next;
            }
            k = k->next;
        }
        /*
        没必要再依次遍历
        while(list1 != nullptr)
        {
            k->next = list1;
            list1 = list1->next;
            k = k->next;
        }
        while(list2 != nullptr)
        {
            k->next = list2;
            list2 = list2->next;
            k = k->next;
        }
        */
        if(list1 != nullptr)
        {
            k->next = list1;
        }
        else
        {
            k->next = list2;
        }
        return head;
    }
};
// @lc code=end

/*
可以构造一个头结点，这样就不用判断该用哪个节点作为头节点，而且也可以没有开始的判空
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* preHead = new ListNode(-1);

        ListNode* prev = preHead;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                prev->next = l1;
                l1 = l1->next;
            } else {
                prev->next = l2;
                l2 = l2->next;
            }
            prev = prev->next;
        }

        // 合并后 l1 和 l2 最多只有一个还未被合并完，我们直接将链表末尾指向未合并完的链表即可
        prev->next = l1 == nullptr ? l2 : l1;

        return preHead->next;
    }
};
*/

