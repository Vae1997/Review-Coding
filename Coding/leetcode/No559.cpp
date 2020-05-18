//N叉树最大深度
/*
说明:

树的深度不会超过 1000。
树的节点总数不会超过 5000。
*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Node {
public:
    int val;
    vector<Node*> children;
    Node() {}
    Node(int _val) {val = _val;}
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
//递归，参考N叉树层序遍历
vector<int> v;//每次发现子节点，递归时v的size++
void traverseNode(Node* root, int level) {
    if(v.size()<=level)v.push_back(level);
    for (int i = 0; i < root->children.size(); i++)
        traverseNode(root->children[i],level+1);   
}
int maxDepth(Node* root) {
    if(!root)return 0;
    if(root->children.empty())return 1;
    traverseNode(root,0);//从第0层开始
    return v.size();
}
//迭代，参考N叉树层序遍历
int maxDepth(Node* root) {
    if(!root)return 0;
    if(root->children.empty())return 1;
    queue<Node*> nodes;
    nodes.push(root);
    int deep=0;
    while(!nodes.empty())
    {
        int s=nodes.size();
        for (int i = 0; i < s; i++)
        {
            Node* n=nodes.front();
            nodes.pop();
            for (int i = 0; i < n->children.size(); i++)
                nodes.push(n->children[i]);    
        }
        deep++;
    }
    return deep;
}
int main()
{
   return 0;
}
