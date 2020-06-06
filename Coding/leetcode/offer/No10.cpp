//斐波那契数列
#include<iostream>
using namespace std;
//经典递归，当N较大时，极易出现递归栈溢出
int fib(int N) {
    if(N==0)return 0;
    if(N==1)return 1;
    return fib(N-1)+fib(N-2);//包含大量的重复计算
    //或者一行（求余防止溢出）
    return N>1?N:(fib(N-1)+fib(N-2))%1000000007;
}
//直接生成或得到数字存入数组，返回N下标对应值
int fib(int N) {
    if(N==0)return 0;
    if(N==1)return 1;
    int *fibs=new int[N+1];//这里可以直接初始化斐波那契数
    fibs[0]=0;fibs[1]=1;
    for (int i = 2; i <= N; i++)
        fibs[i]=(fibs[i-1]+fibs[i-2])%1000000007;
    return fibs[N];
}
//在上述基础上，避免空间O(n)
int fib(int N) {
    if(N==0)return 0;
    if(N==1)return 1;
    int front=0;
    int back=1;
    int fibN;
    for (int i = 2; i <= N; i++)
    {
        fibN=(front+back)%1000000007;
        front=back;
        back=fibN;
    }
    return fibN;
}
//官方矩阵相乘法，但还会溢出
//https://github.com/zhedahht/CodingInterviewChinese2/blob/master/10_Fibonacci/Fibonacci.cpp
//记忆化递归
//将经典递归大量重复值存入mem数组
int mem[101]={0};
int fib(int N) {
    if(N==0)return 0;
    if(N==1)return 1;
    if(mem[N]==0)mem[N]=(fib(N-1)+fib(N-2))%1000000007;
    return mem[N];
}
int main()
{
   
   return 0;
}
