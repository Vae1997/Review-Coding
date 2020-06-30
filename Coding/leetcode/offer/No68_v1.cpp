//二叉搜索树公共祖先
#include<iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//搜索树左小右大
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root==nullptr || p==nullptr || q==nullptr)
        return nullptr;
    if(p->val<root->val && q->val<root->val)
        return lowestCommonAncestor(root->left,p,q);
    if(p->val>root->val && q->val>root->val)
        return lowestCommonAncestor(root->right,p,q);
    return root;
}
//迭代
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* r=root;
    while (r!=nullptr)
    {
        if(r->val<p->val && r->val<q->val)
            r=r->right;
        if(r->val>p->val && r->val>q->val)
            r=r->left;
        else return r;
    }
    return nullptr;
}
int main()
{
   
   return 0;
}
