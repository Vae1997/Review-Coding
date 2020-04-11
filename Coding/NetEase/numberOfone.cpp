/*
小A刚学了二进制，他十分激动。为了确定他的确掌握了二进制，你给他出了这样一道题目：给定N个非负整数，将这N个数字按照二进制下1的个数分类，二进制下1的个数相同的数字属于同一类。求最后一共有几类数字？


输入描述:
输入的第一行是一个正整数T（0<T<=10），表示样例个数。对于每一个样例，第一行是一个正整数N（0<N<=100），表示有多少个数字。接下来一行是N个由空格分隔的非负整数，大小不超过2^31 – 1。，

输出描述:
对于每一组样例，输出一个正整数，表示输入的数字一共有几类。

输入例子1:
1
5
8 3 5 7 2

输出例子1:
3
*/
//思路：https://blog.csdn.net/hefenglian/article/details/79073141
#include<iostream>
using namespace std;
//获取一个正整数二进制1的个数
int getCountOfone(int n)
{
    int c=0;
    while(n!=0)//非零整数至少1个1
    {
        c++;
        //将n和n-1进行&操作
        //&操作结果是消除二进制n中最右端的1，直至为0
        //则&操作的次数即为1的个数
        n&=(n-1);
    }
    return c;
}
int main()
{
    int T,N,n;
    cin>>T;
    while(T)
    {
        cin>>N; 
        //二进制中1的个数范围0~32个
        //标志数组
        //如：num[16]=0表示二进制1的个数为16的数字还没出现
        int num[33]={0};
        //1的个数的类别数
        int count=0;  
        for (int i = 0; i < N; i++)
        {
            cin>>n;
            int numberOfone=getCountOfone(n);
            //当前1的个数numberOfone还没出现过
            if(num[numberOfone]==0)
            {
                count++;//类别++
                num[numberOfone]=1;//置为1，下次出现就不会count++了
            }
        }
        cout<<count<<endl;
        T--;
    }
    return 0;
}
