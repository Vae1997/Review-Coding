//合并两个排序的链表
#include<iostream>
#include<vector>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if(l1 != nullptr && l2 == nullptr)
        return l1;
    if(l1 == nullptr && l2 != nullptr)
        return l2;
    if(l1 == nullptr && l2 == nullptr)
        return nullptr;
    ListNode* head = new ListNode(0);
    ListNode* res=head;
    while (l1 != nullptr && l2 != nullptr)
    {
        if(l1->val<=l2->val)
        {
            head->val=l1->val;
            l1=l1->next;
        }
        else
        {
            head->val=l2->val;
            l2=l2->next;
        }
        head->next=new ListNode(0);
        head=head->next;
    }
    if(l1 == nullptr)
    {
        head->val=l2->val;
        head->next=l2->next;
    }
    else 
    {
        head->val=l1->val;
        head->next=l1->next;
    }
    return res;
}
//迭代，不创建新节点
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if(l1 != nullptr && l2 == nullptr)
        return l1;
    if(l1 == nullptr && l2 != nullptr)
        return l2;
    if(l1 == nullptr && l2 == nullptr)
        return nullptr;
    ListNode* head = new ListNode(-1);
    ListNode* res=head;
    while (l1 != nullptr && l2 != nullptr)
    {
        if(l1->val<=l2->val)
        {
            head->next=l1;
            l1=l1->next;
        }
        else
        {
            head->next=l2;
            l2=l2->next;
        }
        head=head->next;
    }
    if(l1 == nullptr)
    {
        head->next=l2;
    }
    else 
    {
        head->next=l1;
    }
    return res->next;
}
//递归
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if(l1 == nullptr)
        return l2;
    if(l2 == nullptr)
        return l1;
    if(l1->val<=l2->val)
    {
        l1->next=mergeTwoLists(l1->next,l2);
        return l1;
    }
    else
    {
        l2->next=mergeTwoLists(l1,l2->next);
        return l2;
    }
}
int main()
{
   return 0;
}
