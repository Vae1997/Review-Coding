//删除链表的节点
#include<iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
//常规思路
ListNode* deleteNode(ListNode* head, int val) {
    if(head->val==val)return head->next;//删除头节点
    ListNode* p=head;
    ListNode* front=p;
    while (p)
    {
        if(p->val==val)
        {
            if(p->next==nullptr)//删除尾节点
            {
                front->next=nullptr;
            }
            else//删除中间节点
            {
                p->val=p->next->val;//当前节点赋值为后一个节点
                p->next=p->next->next;//当前节点的下一个为后一个节点的下一个，即略过后一个节点
                //也可直接借助front
                // front->next=p->next;
            }
            break;
        }
        front=p;//每次保存上一个节点
        p=p->next;
    }//没找到，还是返回原head即可
    return head;
}
//单指针解决
ListNode* deleteNode(ListNode* head, int val) {
    struct ListNode** indirect = &head;//头节点地址
    //struct ListNode* temp;
    //地址不为空，说明还有节点，每次取下一个节点地址赋值
    for(; *indirect; indirect = &((*indirect)->next)){
        if((*indirect)->val == val){//找到节点
            //temp = *indirect;
            *indirect = (*indirect)->next;
            //free(temp);
            break;
        }
    }
    return head;
}
int main()
{
   
   return 0;
}
