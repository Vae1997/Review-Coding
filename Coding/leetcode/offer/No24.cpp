//反转链表
#include<iostream>
#include<vector>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
//O(n)空间
ListNode* reverseList(ListNode* head) {
    if(!head)return head;
    vector<int> v; 
    while (head->next)//注意，此处退出循环时还未存入最后一个节点
    {
        v.push_back(head->val);//存入值
        head=head->next;
    }
    ListNode* res=new ListNode(head->val);//最后一个节点值构建新节点
    ListNode* p=res;
    for (int i = v.size()-1; i >= 0; i--)//这里从倒数第二个节点循环赋值
    {
        res->next=new ListNode(v[i]);
        res=res->next;
    }
    return p;
}
//O(1)空间，双指针
ListNode* reverseList(ListNode* head) {
    ListNode* pre=head;
    ListNode* cur=nullptr;
    while (pre)
    {
        ListNode* tmp=pre->next;//保存下一个节点
        pre->next=cur;//指向上一个节点
        cur=pre;//指定上一个节点
        pre=tmp;//指向下一个节点
    }
    return cur;
}
//递归
//参考帮助理解
//https://leetcode-cn.com/problems/reverse-linked-list/solution/dong-hua-yan-shi-206-fan-zhuan-lian-biao-by-user74/
ListNode* reverseList(ListNode* head) {
    if(!head || !head->next)return head;
    ListNode* last=reverseList(head->next);//注意每次回溯返回都是最后一个节点
    head->next->next=head;//head才表示当前递归层的节点
    head->next=nullptr;//断开之前的next
    return last;
}
int main()
{
   
   return 0;
}
