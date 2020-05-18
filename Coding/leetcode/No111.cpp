//二叉树的最小深度
#include<iostream>
#include<queue>
#include<stack>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//递归，DFS
int minDepth(TreeNode* root) {
    //空节点为0
    if(!root)return 0;
    //当前节点有两个孩子，则取小
    if(root->left&&root->right)return min(minDepth(root->left),minDepth(root->right))+1;
    //有一个孩子或没有孩子
    return minDepth(root->left)+minDepth(root->right)+1;
}
//迭代，DFS
struct NodeWithDeep
{
    TreeNode* node;
    int deep;
    NodeWithDeep(TreeNode* node, int deep) : node(node), deep(deep) {}
};
int minDepth(TreeNode* root) {
    if(!root)return 0;
    stack<NodeWithDeep> nodes;
    nodes.emplace(root,1);//根节点深度1
    int minDeep=INT_MAX;
    while (!nodes.empty())
    {
        NodeWithDeep n=nodes.top();
        nodes.pop();
        //有孩子，则孩子深度+1并入栈
        if(n.node->left)nodes.emplace(n.node->left,n.deep+1);
        if(n.node->right)nodes.emplace(n.node->right,n.deep+1);
        //叶节点，对比当前节点深度和最小深度
        if(!n.node->left&&!n.node->right)
            minDeep=min(minDeep,n.deep);
    }
    return minDeep;
}
//迭代，BFS
int minDepth(TreeNode* root) {
    if(root)
    {
        queue<TreeNode*>nodes;
        nodes.push(root);
        int minDeep=1;
        while (!nodes.empty())//队列长度为当前层节点数
        {
            int count=nodes.size();
            for (int i = 0; i < count; i++)
            {
                TreeNode* n=nodes.front();
                nodes.pop();
                if(!n->left&&!n->right)return minDeep;//当前层发现叶节点，直接返回
                if(n->left)nodes.push(n->left);
                if(n->right)nodes.push(n->right);
            }
            minDeep++;//遍历完一层，深度++
        }
    }
    return 0;
}
int main()
{
   return 0;
}
