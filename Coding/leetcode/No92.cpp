//反转链表 II
#include<iostream>
#include<vector>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
//m之前的和n之后的不动
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if(head == nullptr || head->next == nullptr || m == n)
        return head;
    int count=1;
    ListNode* L=head;
    ListNode* res=new ListNode(-1);
    res->next=head;
    while (count<m-1)//让L指向m-1
    {
        L=L->next;
        count++;
    }
    // cout<<count<<" "<<L->val<<endl;
    ListNode* frontM=nullptr;//保存m-1节点
    if(m!=1)
        frontM=L;//保存第M-1个节点
    else frontM=res;//m==1的情况，将m的前一个节点置为res即可
    ListNode* R=L->next;//R指向第M个节点
    while (count<n)//利用L、R反转m~n节点
    {
        ListNode* tmp=R->next;
        R->next=L;
        L=R;
        R=tmp;
        count++;
    }
    // cout<<count<<" "<<L->val<<" "<<R->val<<endl;
    frontM->next->next=R;//衔接n+1节点
    frontM->next=L;//衔接m-1节点
    return res->next;
}
int main()
{
   return 0;
}
