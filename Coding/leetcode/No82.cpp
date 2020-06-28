//删除所有含有重复数字的节点
#include<iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
ListNode* deleteDuplicates(ListNode* head) {
    if(!head||!head->next)return head;
    //避免头节点重复，加入空节点
    ListNode* res=new ListNode(-1);
    res->next=head;
    ListNode* p=head;
    ListNode* front=res;
    while (p)
    {
        if(p->next&&p->next->val==p->val)//p和next相等
        {
            int val=p->val;
            while (p&&p->val==val)//寻找第一个不相等
            {
                p=p->next;
            }
        }//p确保和next不相等
        else
        {
            front->next=p;
            front=p;
            p=p->next;
        }
    }
    front->next=p;
    return res->next;
}
int main()
{
   return 0;
}
