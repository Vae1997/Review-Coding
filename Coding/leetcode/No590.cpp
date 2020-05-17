//N叉树的后序遍历
#include<iostream>
#include<vector>
#include<stack>
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
//递归(和前序遍历只是push顺序在递归之后)
vector<int> v;
vector<int> postorder(Node* root) {
    if(!root)return v;
    //如果有孩子，挨个作为新的root节点进行递归返回vector
    if(!root->children.empty())   
        for (int i = 0; i < root->children.size(); i++)
            postorder(root->children[i]);   
    v.push_back(root->val);//递归完毕，注意加入根节点值
    return v;
}
//迭代(从左到右压入子节点+反转)
/*
后序顺序：左->右->根
入栈顺序：左->右->根
出栈顺序：根->右->左
反转顺序：左->右->根，完成
*/
vector<int> postorder(Node* root) {
    if(!root)return v;
    stack<Node*> nodes; 
    nodes.push(root);//压入根节点
    while(!nodes.empty())
    {        
        Node* n=nodes.top();
        v.push_back(n->val);
        nodes.pop();
        if(!n->children.empty())
            for (int i = 0; i < n->children.size(); i++)
                nodes.push(n->children[i]);    
    }
    reverse(v.begin(),v.end());
    return v;
}
int main()
{
   return 0;
}
