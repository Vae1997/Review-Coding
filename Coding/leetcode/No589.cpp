//N叉树的前序遍历
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
//递归
vector<int> v;
vector<int> preorder(Node* root) {   
    if(root==nullptr)return v;
    v.push_back(root->val);
    if(!root->children.empty())
    {
        //如果有孩子，挨个作为新的root节点进行递归返回vector
        for (int i = 0; i < root->children.size(); i++)
            preorder(root->children[i]);
        return v;
    }
    else return v;   
}
//迭代
vector<int> preorder(Node* root) {   
    if(root==nullptr)return v;
    stack<Node*> node; 
    node.push(root);//压入根节点
    while(!node.empty())
    {
        v.push_back(node.top()->val);//栈顶为前序遍历的当前节点
        if(node.top()->children.empty())node.pop();//没孩子，直接弹出
        else
        {
            Node* n=node.top();//注意保存之前的栈顶，用于逆序迭代
            node.pop();//栈顶元素已经前序遍历了，需弹出
            //栈顶元素有孩子，则逆序将孩子压栈
            for (int i = n->children.size()-1; i >=0 ; i--)
                node.push(n->children[i]);
            //迭代结束，当前新栈顶即为前序遍历下一个节点
        }        
    }
    return v;
}
int main()
{
   return 0;
}
