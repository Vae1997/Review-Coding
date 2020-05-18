//二叉树最大深度
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
int maxDepth(TreeNode* root) {
    if(root)return max(maxDepth(root->left),maxDepth(root->right))+1;
    return 0;
}
//迭代，DFS，需要结构体将节点深度和节点本身绑定
struct NodeWithDeep
{
    TreeNode* node;
    int deep;
    NodeWithDeep(TreeNode* node, int deep) : node(node), deep(deep) {}
};
int maxDepth(TreeNode* root) {
    if(!root)return 0;
    stack<NodeWithDeep> nodes;
    nodes.emplace(root,1);//根节点深度1
    int maxDeep=0;
    while (!nodes.empty())
    {
        NodeWithDeep n=nodes.top();
        nodes.pop();
        maxDeep=max(maxDeep,n.deep);//对比当前节点深度和最大深度
        //有孩子，则孩子深度+1并入栈
        if(n.node->left)nodes.emplace(n.node->left,n.deep+1);
        if(n.node->right)nodes.emplace(n.node->right,n.deep+1);
    }
    return maxDeep;
}
//递归，BFS
int maxDeep=0;
void traverseNode(TreeNode* root, int deep) {
    //deep表示当前递归所在层
    if(maxDeep<=deep)maxDeep++;
    //有子节点，则深度++
    if(root->left)traverseNode(root->left,deep+1);
    if(root->right)traverseNode(root->right,deep+1);
}
int maxDepth(TreeNode* root) {
    if(root)traverseNode(root,0);
    return maxDeep;
}
//迭代，BFS
int maxDepth(TreeNode* root) {
    if(!root)return 0;
    int deep=0;
    queue<TreeNode*> nodes;
    nodes.push(root);
    while(!nodes.empty())
    {       
        int count=nodes.size();
        for (int i = 0; i < count; i++)//根据队列长度，循环入队子节点
        {
            TreeNode* n=nodes.front();
            if(n->left)nodes.push(n->left);
            if(n->right)nodes.push(n->right);
            nodes.pop();
        }//迭代结束，进入下一层的队列
        deep++;
    }
    return deep;
}
int main()
{
   return 0;
}
