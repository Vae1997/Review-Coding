//不同的二叉搜索树
#include<iostream>
#include<vector>
using namespace std;
//总数=1为根的数+2为根+...+n为根
//i为根的数=i-1个总数*n-i个总数
int numTrees(int n) {
    vector<int>dp(n+1,0);
    dp[0]=dp[1]=1;
    for (int i = 2; i <= n; i++)//当前序列总数为i
    {
        for (int j = 1; j <= i; j++)//从j到i分别为根节点
        {
            dp[i]+=dp[j-1]*dp[i-j];
        }
    }
    return dp[n];
}
int main()
{
   return 0;
}
