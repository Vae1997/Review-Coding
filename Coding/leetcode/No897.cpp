//https://leetcode-cn.com/problems/increasing-order-search-tree/
#include<iostream>
#include<stack>
#include<vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
vector<int> v;
//递归
vector<int> inorderTraversal(TreeNode* root) {
    if(root)
    {
        inorderTraversal(root->left);
        v.push_back(root->val);
        inorderTraversal(root->right);
    }
    return v;
}
//中序遍历完成后，构建新树存入
TreeNode* increasingBST(TreeNode* root) {
    inorderTraversal(root);
    TreeNode *res = new TreeNode(0);
    TreeNode *t=res;
    for (int i = 0; i < v.size(); i++)
    {
        t->val=v[i];
        if(i!=v.size()-1)
        {
            t->right=new TreeNode(0);
            t=t->right;
        }
    }
    return res;
}
TreeNode* later;//上一个节点
//递归
void inorderTraversal2(TreeNode* root) {
    if(root)
    {
        inorderTraversal2(root->left);
        root->left=nullptr;//置空当前节点的left
        later->right=root;//上一个节点的右节点为当前节点
        later=root;//上一个节点更新为当前节点
        inorderTraversal2(root->right);
    }
}
//中序遍历在遍历的时候修改
TreeNode* increasingBST(TreeNode* root) {
    TreeNode *res=new TreeNode(0);
    later=res;
    inorderTraversal2(root);
    return res->right;
}
int main()
{
   
   return 0;
}
