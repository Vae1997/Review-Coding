//面试题22. 链表中倒数第k个节点
//倒数第k个==>链表中的第count-k个节点
#include<iostream>
using namespace std;
#define COUNT 5
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};
ListNode* getKthFromEnd(ListNode* head, int k) {
    if(head==NULL)return NULL;//空链表
    if(head->next==NULL)return k==1?head:NULL;//单个节点的链表
    if(k<1)return NULL;//非法
    ListNode *p=head;
    int count=1;
    while(p->next!=NULL)//循环结束，p指向链表尾部节点
    {
        count++;
        p=p->next;
    }
    if(k>count)return NULL;//非法
    if(k==count)return head;//倒数第count个节点
    if(k==1)return p;//倒数第一个节点
    p=head;//p重新指向head
    for (int i = 1; i <= count-k; i++)//倒数第k个节点，返回第count-k个节点
        p=p->next;
    return p;
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
