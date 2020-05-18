//N叉树层序遍历
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
//递归,通过deep参数，确保每次递归结束回到之前的deep
vector<vector<int>> v;//v的size即为深度
void traverseNode(Node* root, int deep) {
    if(v.size()<=deep)//如果有递归，则还有子节点，需要创建新的一层vector
        v.push_back(vector<int>());
    v[deep].push_back(root->val);//在当前deep存放当前节点
    //当前节点有孩子，则递归每个孩子，deep++，创建新vector
    for (int i = 0; i < root->children.size(); i++)
        traverseNode(root->children[i],deep+1);
}
vector<vector<int>> levelOrder(Node* root) {
    if(root)traverseNode(root,0);//从第0层开始
    return v;
}
//迭代，当前队列所有节点出队，并挨个将子节点入队
vector<vector<int>> levelOrder(Node* root) {
    vector<vector<int>> v;
    if(!root)return v;
    queue<Node*> nodes;
    nodes.push(root);
    while(!nodes.empty())
    {
        vector<int> tv;//存储每一层节点的值 
        int count=nodes.size();//当前队列长度
        for (int i = 0; i < count; i++)//当前队列中所有节点的孩子入队
        {
            Node* n=nodes.front();
            nodes.pop();
            tv.push_back(n->val);
            for (int i = 0; i < n->children.size(); i++)
                nodes.push(n->children[i]); 
        }//迭代结束，新队列是上一层节点所有的孩子
        v.push_back(tv);//将每一层值加入结果
    }
    return v;
}
int main()
{
   return 0;
}
