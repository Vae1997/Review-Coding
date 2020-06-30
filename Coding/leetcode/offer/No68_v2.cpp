//二叉树的最近公共祖先
#include<iostream>
#include<vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//先找到p和q两个节点的路径
//参数path为引用传递，确保返回修改的path
bool findPathFromRoot(TreeNode* root, TreeNode* target, vector<TreeNode*>& path)
{
    // cout<<"cur node:"<<root->val<<endl;
    path.push_back(root);//必须先将目标节点加入路径中，避免两个节点在同一路径的情况
    if(root==target)//然后如果找到再返回
        return true;
    bool find=false;
    if(root->left!=nullptr)
        find=findPathFromRoot(root->left,target,path);
    if(!find&&root->right!=nullptr)
        find=findPathFromRoot(root->right,target,path);
    if(!find)
        path.pop_back();//没找到，则需要弹出
    return find;
}
//将两条路径视为链表遍历寻找公共节点
//参数为const引用，确保不会修改path，避免拷贝开销
TreeNode* getLastCommonNode(const vector<TreeNode*>& path1, const vector<TreeNode*>& path2)
{
    TreeNode* res=nullptr;
    // int L1=path1.size();
    // int L2=path2.size();
    // int i,j;i=j=0;
    // while (i<L1 && j<L2)//path从root-tar，找到最后一个相等的节点即为结果
    // {
    //     if(path1[i]==path2[j])
    //         res=path1[i];
    //     i++;
    //     j++;
    // }
    //迭代器遍历
    vector<TreeNode*>::const_iterator i=path1.begin();
    vector<TreeNode*>::const_iterator j=path2.begin();
    while (i!=path1.end() && j!=path2.end())
    {
        if(*i==*j)
            res=*i;
        i++;j++;
    }
    return res;
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root==nullptr || p==nullptr || q==nullptr)
        return nullptr;
    vector<TreeNode*> path1,path2;
    findPathFromRoot(root,p,path1);
    // for(int i=0;i<path1.size();i++)
    //     cout<<path1[i]->val<<" ";
    // cout<<endl;
    findPathFromRoot(root,q,path2);
    // for(int i=0;i<path2.size();i++)
    //     cout<<path2[i]->val<<" ";
    // cout<<endl;
    return getLastCommonNode(path1,path2);
}
int main()
{
   
   return 0;
}
