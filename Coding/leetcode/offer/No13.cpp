//https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/
#include<iostream>
#include <cstring>
using namespace std;
int getIndexSum(int row,int col)
{
    int sum=0;
    if(row==100)sum+=1;
    else if(row>=1&&row<=9)sum+=row;
    else sum+=row/10+row%10;
    if(col==100)sum+=1;
    else if(col>=1&&col<=9)sum+=col;
    else sum+=col/10+col%10;
    return sum;
}
int countOfsmallerK(int row,int col,int m,int n,int k,bool *visited)
{
    int count=0;
    //下标在有效范围内,且没有访问过
    if(row>=0&&row<m&&col>=0&&col<n&&!visited[row*n+row])
    {
        visited[row*n+row]=true;//标记已经访问
        //计算下标和,满足条件则递归搜索周围的下标
        if(getIndexSum(row,col)<=k)
        {
            count = countOfsmallerK(row-1,col,m,n,k,visited)+
                    countOfsmallerK(row+1,col,m,n,k,visited)+
                    countOfsmallerK(row,col-1,m,n,k,visited)+
                    countOfsmallerK(row,col+1,m,n,k,visited)+ 1;
        }
    }
    return count;
}
int movingCount(int m, int n, int k) {
    int count=0;
    bool *visited=new bool[m*n];
    memset(visited,0,m*n);
    count=countOfsmallerK(0,0,m,n,k,visited);
    delete[] visited;
    return count;
}
int main()
{
    return 0;
}
