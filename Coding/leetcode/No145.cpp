//二叉树的后序遍历
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
vector<int> postorderTraversal(TreeNode* root) {
    if(root)
    {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        v.push_back(root->val);
    }
    return v;
}
//迭代
//后序遍历：左->右->根
//入栈顺序：左->右->根
//出栈顺序：根->右->左
//反转顺序：左->右->根
vector<int> postorderTraversal(TreeNode* root) {
    if(!root)return v;
    stack<TreeNode*> s;
    s.push(root);
    while(s.size())
    {
        TreeNode* n=s.top();
        v.push_back(n->val);
        s.pop();
        if(n->left)s.push(n->left);
        if(n->right)s.push(n->right);
    }
    reverse(v.begin(),v.end());
    return v;
}
int main()
{
   return 0;
}
