//面试题8：二叉树的下一个结点
/*
给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。
注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
*/
#include<iostream>
using namespace std;
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {}
};
TreeLinkNode* GetNext(TreeLinkNode* pNode)
{
    if(pNode==nullptr)return nullptr;//空指针
    if(pNode->right!=nullptr)//存在右节点
    {
        pNode=pNode->right;
        while (pNode->left!=nullptr)//返回右节点的最左节点
            pNode=pNode->left;
        return pNode;     
    }
    while(pNode->next!=nullptr)//不存在右节点，但存在父节点
    {
        //是父节点的左孩子，则后继就是父节点
        if(pNode->next->left==pNode)return pNode->next;
        pNode=pNode->next;//是父节点的右孩子，继续往上
    }
    return nullptr;//遍历到根节点，还是右孩子，则无后继
}
int main()
{
    return 0;
}
