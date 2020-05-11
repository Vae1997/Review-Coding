//面试题6：从尾到头打印链表
/*
输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

输入：head = [1,3,2]
输出：[2,3,1]

限制：0 <= 链表长度 <= 10000
*/
#include<iostream>
#include<vector>
using namespace std;
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
//借助另一个vector反向存储
vector<int> reversePrint2(ListNode* head) {
    vector<int> v;
    if(head==nullptr)return v;
    while(head->next!=nullptr)
    {
        v.push_back(head->val);
        head=head->next;
    }
    v.push_back(head->val);//存放最后一个节点
    //直接反转
    //reverse(v.begin(),v.end());
    //return v;
    vector<int> res;
    while(!v.empty())
    {
        res.push_back(v.back());
        v.pop_back();
    }
    return res;
}
//递归
vector<int> v;
void Recursively(ListNode* head)
{
    if(head!=nullptr)
    {
        if(head->next!=nullptr)
        {
            Recursively(head->next); //递归，直到最后一个节点           
        }
        v.push_back(head->val);  //从最后一个节点挨个push      
    }
}
vector<int> reversePrint3(ListNode* head) {   
    Recursively(head);
    return v;
}
//递归简写
vector<int> reversePrint(ListNode* head) {   
    if(!head)return {};
    vector<int> v=reversePrint(head->next);
    v.push_back(head->val);
    return v;
}
int main()
{
   return 0;
}
