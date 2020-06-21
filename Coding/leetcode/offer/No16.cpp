//实现pow(x,n)
#include<iostream>
using namespace std;
//n为int范围，会超时
double powCore2(double x, int n)
{
    double r=x;
    for (int i = 1; i < n; i++)
    {
        r*=x;
    }
    return r;
}
//递归实现
double powCore(double x, int n)
{
    if(n==0)return 1;
    if(n==1)return x;
    double res=powCore(x,n>>1);
    res*=res;
    if(n & 0x1 == 1)res*=x;
    return res;
}
//简化上述递归
double powCore(double x, int n)
{
    if(n==0)return 1;
    if(n==1)return x;
    double res=powCore(x,n>>1);
    return (n & 0x1 == 1)?res*res*x:res*res;
}
double myPow(double x, int n) {
    
    if(n==0)return 1;
    if(x==1)return x;
    if(x==0 && n>0)return 0;
    if(x==0 && n<0)return -1;
    double res;
    if(n<0)
    {
        if(n==-2147483648)
        {
            if(x==-1)return 1;
            else return 0;
        }
        unsigned int un=(unsigned int)(-n);
        res=1/powCore(x,un);
    }
    else if(n>0)
    {
        res=powCore(x,n);
    }
    return res;
}
//单函数递归
double myPow(double x, int n) {
    if(n==0)return 1;
    if(n==1)return x;
    if(n==-1)return 1/x;
    double half=myPow(x,n>>1);
    double rest=myPow(x,n & 0x1);
    return half*half*rest;
}
int main()
{
   
   return 0;
}
