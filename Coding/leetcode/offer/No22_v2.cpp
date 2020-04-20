//面试题22. 链表中倒数第k个节点
//快慢指针
#include<iostream>
using namespace std;
#define COUNT 5
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};
ListNode* getKthFromEnd(ListNode* head, int k) {
    if(head==NULL || k<1)return NULL;//空链表,非法k
    if(head->next==NULL)return k==1?head:NULL;//单个节点的链表
    ListNode *fast=head,*slow=head;
    int step=0;
    while(step!=k)
    {
        if(fast==NULL)return NULL;//fast移动完链表还未到达k，溢出
        fast=fast->next;
        step++;
    }
    while(fast!=NULL)//同时移动，fast移动完，slow为倒数k
    {
        fast=fast->next;
        slow=slow->next;
    }
    return slow;
}
int main()
{
    ListNode node1 = ListNode(1);
    ListNode node2 = ListNode(2);
    ListNode node3 = ListNode(3);   
    ListNode node4 = ListNode(4);    
    ListNode node5 = ListNode(5);
    node1.next=&node2;
    node2.next=&node3;
    node3.next=&node4;
    node4.next=&node5;
    ListNode *p=&node1;
    cout<<p->val<<" ";
    while(p->next!=NULL)
    {
        p=p->next;
        cout<<p->val<<" ";
    }
    cout<<endl;
    int k;
    cin>>k;
    ListNode *res=getKthFromEnd(&node1,k);
    if(res!=NULL)cout<<res->val<<endl;
    else cout<<"NULL"<<endl;
    return 0;
}
