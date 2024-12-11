/*
 * @lc app=leetcode.cn id=160 lang=cpp
 *
 * [160] 相交链表
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* listA = headA;
        ListNode* listB = headB;
        int lenA = 0;
        int lenB = 0;
        int k;
        while(listA != nullptr)
        {
            listA = listA->next;
            lenA++;
        }
        while(listB != nullptr)
        {
            listB = listB->next;
            lenB++;
        }
        k = lenA - lenB;
        listA = headA;
        listB = headB;
        if(lenA >= lenB)
        {
            while(k--)
                listA = listA->next;
        }
        else
        {
            while(k++)
                listB = listB->next;
        }
        while(listA != nullptr && listB != nullptr)
        {
            if(listA == listB)  return listA;
            listA = listA->next;
            listB = listB->next;
        }
        return nullptr;
    }
};
// @lc code=end

/*
只用各遍历一次，首先到nullptr的，说明是短的，直接跳转到长的首节点，继续遍历，
其次到nullptr的说明是长的，跳转到短的首节点，此时长的也已经走过了他们的长度之差
个节点，之后若相互遇到直接返回，返回的可能是nullptr（说明互换指针后都走到最后），
或者是相交处。
public class Solution {
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        if (headA == null || headB == null) {
            return null;
        }
        ListNode pA = headA, pB = headB;
        while (pA != pB) {
            pA = pA == null ? headB : pA.next;
            pB = pB == null ? headA : pB.next;
        }
        return pA;
    }
}
*/
