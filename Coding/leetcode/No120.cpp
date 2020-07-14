//三角形最小路径和
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//递归
int row;
int minimumTotal(vector<vector<int>>& triangle) {
    row=triangle.size();
    return dfs(0,0,triangle);//传入行列
}
int dfs(int level,int col,vector<vector<int>>& triangle)
{
    if(level==row-1)//最后一行，返回当前行列值
    {
        return triangle[level][col];
    }
    int left=dfs(level+1,col,triangle);//下一层，同下标
    int right=dfs(level+1,col+1,triangle);//下一层，下标+1
    return min(left,right)+triangle[level][col];//下一层小的+当前值
}
//记忆递归
int row;
int minimumTotal(vector<vector<int>>& triangle) {
    row=triangle.size();
    vector<vector<int>> mem(row,vector<int>(row,0));
    return dfs(0,0,triangle,mem);
} 
int dfs(int level,int col,vector<vector<int>>& triangle,vector<vector<int>>& mem)
{
    if(level==row-1)//最后一行，返回当前行列值
    {
        return triangle[level][col];
    }
    if(mem[level][col]!=0)//已有记录，直接返回
    {
        return mem[level][col];
    }
    int left=dfs(level+1,col,triangle,mem);//下一层，同下标
    int right=dfs(level+1,col+1,triangle,mem);//下一层，下标+1
    mem[level][col]=min(left,right)+triangle[level][col];//下一层小的+当前值
    return mem[level][col];
}
//DP
int minimumTotal(vector<vector<int>>& triangle) {
    row=triangle.size();
    vector<vector<int>> dp(row,vector<int>(row,0));
    //初始化row-1
    for (int i = 0; i < row; i++)
    {
        dp[row-1][i]=triangle[row-1][i];
    }
    for (int i = row-2; i >= 0; i--)//row-2行开始
    {
        for (int j = 0; j <= i; j++)//第i行有i个值
        {
            dp[i][j]=min(dp[i+1][j],dp[i+1][j+1])+triangle[i][j];
        }
    }
    return dp[0][0];
}
//DP空间优化
int minimumTotal(vector<vector<int>>& triangle) {
    row=triangle.size();
    vector<int> dp(row+1,0);//初始化row+1
    for (int i = row-1; i >= 0; i--)//row-1行开始
    {
        for (int j = 0; j <= i; j++)//第i行有i个值
        {
            dp[j]=min(dp[j],dp[j+1])+triangle[i][j];
        }
    }
    return dp[0];
}
//原地DP
int minimumTotal(vector<vector<int>>& triangle) {
    row=triangle.size();
    for (int i = row-2; i >= 0; i--)//row-1行开始
    {
        for (int j = 0; j <= i; j++)//第i行有i个值
        {
            triangle[i][j]+=min(triangle[i+1][j],triangle[i+1][j+1]);
        }
    }
    return triangle[0][0];
}
int main()
{
   return 0;
}
