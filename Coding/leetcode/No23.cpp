//合并K个排序链表
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
struct cmp{  
    bool operator()(ListNode *a,ListNode *b){
        return a->val > b->val;
    }
};
ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*,vector<ListNode*>,cmp> q;
    for(auto v:lists)
    {
        if(v)q.push(v);
    }
    ListNode* head = new ListNode(-1);
    ListNode* res=head;
    while (!q.empty())
    {
        ListNode* t=q.top();
        q.pop();
        head->next=t;
        head=t;
        if(t->next)q.push(t->next);
    }
    return res->next;
}
int main()
{
   return 0;
}
