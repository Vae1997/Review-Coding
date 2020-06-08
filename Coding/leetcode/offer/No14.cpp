//https://leetcode-cn.com/problems/jian-sheng-zi-lcof/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//https://leetcode-cn.com/problems/integer-break/solution/bao-li-sou-suo-ji-yi-hua-sou-suo-dong-tai-gui-hua-/
//暴力递归
//i*(n-i):分割点i将源数字n分为i和n-i两个数
//i*cuttingRope(n-i)：i不变，对n-i再次分割
int cuttingRope(int n) {
    if(n==2)return 1;
    int res=-1;
    for (int i = 1; i <= n; i++)
        res=max(res,max(i*(n-i),i*cuttingRope(n-i)));
    return res;
}
//记忆递归
int get(int n,vector<int>& mem)
{
    if(n==2)return 1;
    if(mem[n]!=0)return mem[n];//当前数字n已经有值，直接返回
    int res=-1;
    for (int i = 1; i <= n; i++)//否则，再对n进行分割
        res=max(res,max(i*(n-i),i*cuttingRope(n-i)));
    mem[n]=res;//存储n的值
    return res;
}
int cuttingRope(int n) {
    vector<int> mem(n+1,0);
    return get(n,mem);
}
//动态规划
int cuttingRope(int n) {
    vector<int> mem(n+1,0);
    mem[2]=1;//n==2，值为1
    for (int i = 3; i <= n; i++)//从3开始，算到n
        for (int j = 1; j <= i/2; j++)//每个数字i，从1开始分割到i/2即可
            mem[i]=max(mem[i],max(j*(i-j),j*mem[i-j]));//最大结果的分割点
    return mem[n];
}
//贪心算法
//n>=5,以3为单位截取
//n==4，截取为2*2
int cuttingRope(int n) {
    if(n<=2)return 1;
    if(n==3)return 2;
    if(n==4)return 4;
    int times=n/3;
    int res;
    while (times--)
    {
        if(n>=5)
        {
            n-=3;
            res*=3;
        }else if(n==4)
        {
            res*=4;
            break;
        }
        else if(n==3)
        {
            res*=2;
            break;
        }else if(n==2)
        {
            return res;
        }
    }
    return res;
}
int main()
{
   cout<<cuttingRope(4)<<endl;
   return 0;
}
