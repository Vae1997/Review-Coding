//删除链表的倒数第N个节点
#include<iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
//前后指针
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if(!head||!head->next)return nullptr;
    ListNode* L=head;
    ListNode* R=head;
    ListNode* mem=head;
    while (n)//L和R间隔n
    {
        R=R->next;
        n--;
    }
    while (R)//L和R同时右移
    {
        mem=L;//保存前一个节点
        L=L->next;
        R=R->next;
    }
    if(L->next)//L不是尾节点
    {
        L->val=L->next->val;//覆盖
        L->next=L->next->next;//略过
    }
    else//L为尾节点
    {
        mem->next=nullptr;//前一个节点next为空
    }
    return head;   
}
int main()
{
   
   return 0;
}
