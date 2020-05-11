//面试题7：重建二叉树
/*
输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：
    3
   / \
  9  20
    /  \
   15   7
限制：0 <= 节点个数 <= 5000
*/
#include<iostream>
#include<vector>
using namespace std;
/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if(preorder.empty()||inorder.empty())return nullptr;
    int rootval=preorder[0];
    TreeNode *root=new TreeNode(rootval);//根节点的值为前序第一个值
    vector<int> Linorder,Rinorder;//左右子树的中序遍历
    int rootIndex=-1;
    for (int i = 0; i < inorder.size(); i++)
    {
        if(inorder[i]==root->val)rootIndex=i;
        else
        {
            if(rootIndex==-1)Linorder.push_back(inorder[i]);
            else Rinorder.push_back(inorder[i]);
        }
    }
    vector<int> Lpreorder,Rpreorder;//左右子树的前序遍历
    for (int i = 1; i <= rootIndex; i++)
        Lpreorder.push_back(preorder[i]);       
    for (int i = rootIndex+1; i < preorder.size(); i++)
        Rpreorder.push_back(preorder[i]);  
    //递归 
    if(!Linorder.empty())root->left=buildTree(Lpreorder,Linorder);
    if(!Rinorder.empty())root->right=buildTree(Rpreorder,Rinorder);
    return root;
}
int main()
{
    vector<int>preorder,inorder;
    preorder.push_back(3);
    preorder.push_back(9);
    preorder.push_back(20);
    preorder.push_back(15);
    preorder.push_back(7);
    inorder.push_back(9);
    inorder.push_back(3);
    inorder.push_back(15);
    inorder.push_back(20);
    inorder.push_back(7);
    TreeNode* root=buildTree(preorder, inorder);
    return 0;
}
