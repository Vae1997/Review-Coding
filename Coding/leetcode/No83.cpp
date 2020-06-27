// 删除排序链表中的重复元素
#include<iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
ListNode* deleteDuplicates(ListNode* head) {
    if(!head||!head->next)return head;
    ListNode* p=head;
    while (p->next)
    {
        if(p->val==p->next->val)
        {
            p->next=p->next->next;//略过重复元素
        }
        else
        {
            p=p->next;
        }
    }
    return head;
}
int main()
{
   
   return 0;
}
