//二叉树的前序遍历
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
vector<int> v;
//递归
vector<int> preorderTraversal(TreeNode* root) {
    if(!root)return v;
    v.push_back(root->val);
    if(root->left)
        preorderTraversal(root->left);
    if(root->right)
        preorderTraversal(root->right);
    return v;
}
//迭代,从右到左压入子节点
vector<int> preorderTraversal(TreeNode* root) {
    if(!root)return v;
    stack<TreeNode*>node;
    node.push(root);
    while(!node.empty())
    {
        TreeNode* n=node.top();
        v.push_back(n->val);
        node.pop();
        if(n->right)node.push(n->right);
        if(n->left)node.push(n->left);
    }
    return v;
}
int main()
{
   return 0;
}
