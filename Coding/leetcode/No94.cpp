//二叉树的中序遍历
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//递归
vector<int> v;
vector<int> inorderTraversal(TreeNode* root) {
    if(root)
    {
        inorderTraversal(root->left);
        v.push_back(root->val);
        inorderTraversal(root->right);
    }
    return v;
}
//迭代
vector<int> inorderTraversal(TreeNode* root) {
    if(!root)return v;
    stack<TreeNode*> s;
    TreeNode* temp=root;
    while(temp||s.size())
    {        
        while(temp)//当前节点左子节点挨个入栈
        {
            s.push(temp);
            temp=temp->left;
        }
        TreeNode* n=s.top();//最左子节点存入后弹出
        v.push_back(n->val);
        s.pop();
        //有右节点，则迭代右节点入栈其左子节点
        if(n->right)temp=n->right;
        //没右节点，temp为空，直接弹出栈顶
    }
    return v;
}
//迭代，破坏树结构，或者标记一下访问过的节点，保护树结构
//中序遍历：左根右
//入栈顺序：右根左（入栈后将对应子节点置空）
//出栈顺序：左根右（置空后避免再次入栈）
vector<int> inorderTraversal(TreeNode* root) {
    if(!root)return v;
    stack<TreeNode*> s;
    s.push(root);
    while(s.size())
    {
        TreeNode* n=s.top();
        s.pop();
        if(n->right==NULL&&n->left==NULL)//左右节点原本空，或者置空
        {
            v.push_back(n->val);
            continue;
        }
        if(n->right!=NULL)//有右节点
        {
            s.push(n->right);//入栈
            n->right=NULL;//置空
        }
        s.push(n);//重新入栈当前节点
        if(n->left!=NULL)//有左节点
        {
            s.push(n->left);//入栈
            n->left=NULL;//置空
        }
    }
    return v;
}
int main()
{
   return 0;
}
