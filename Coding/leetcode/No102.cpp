//二叉树的层序遍历
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//深度递归
vector<vector<int>> v;
void traverseNode(TreeNode* root, int deep) {
    if(v.size()<=deep)v.push_back(vector<int>());
    v[deep].push_back(root->val);
    if(root->left)traverseNode(root->left,deep+1);
    if(root->right)traverseNode(root->right,deep+1);
}
vector<vector<int>> levelOrder(TreeNode* root) {
    if(root)traverseNode(root,0);
    return v;
}
//广度迭代
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> v;
    if(!root)return v;
    queue<TreeNode*> nodes;
    nodes.push(root);
    while (!nodes.empty())
    {
        int count=nodes.size();
        vector<int> levelv;
        for (int i = 0; i < count; i++)
        {
            TreeNode* n=nodes.front();
            levelv.push_back(n->val);
            nodes.pop();
            if(n->left)nodes.push(n->left);
            if(n->right)nodes.push(n->right);
        }
        v.push_back(levelv);
    }
    return v;
}
int main()
{
   return 0;
}
