//奇偶链表
#include<iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode* oddEvenList(ListNode* head) {
    if(head == nullptr || head->next == nullptr || head->next->next == nullptr)
        return head;
    ListNode* L=head;
    ListNode* R=head->next;
    ListNode* save=head->next;
    int count=2;
    while (R->next != nullptr)
    {
        L->next=R->next;
        L=R;
        R=R->next;
        count++;
    }
    if(count%2==0)//偶数个节点
        L->next=save;
    else//奇数个节点
    {
        L->next=R->next;
        R->next=save;
    }
    return head;
}
int main()
{
   return 0;
}
