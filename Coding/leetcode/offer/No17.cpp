//1到最大n位数
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
//不考虑大数
vector<int> printNumbers1(int n) {
    int i=1;
    int max;
    while (n)
    {
        max+=i*9;
        i*=10;
        n--;
    }
    vector<int> v;
    for (int i = 1; i <= max; i++)
    {
        v.push_back(i);
    }
    return v;
}
//不考虑大数，pow解法
vector<int> printNumbers2(int n) {
    vector<int> res;
    int max= pow(10,n)-1;
    for(int i=1;i<=max;i++){
        res.push_back(i);
    }
    return res;
}
//考虑大数，char*存储数字
bool Increment(char* number)
{
    int len=strlen(number);
    bool overFlow=false;
    int add=0;//进位
    for (int i = len-1; i >= 0; i--)
    {
        int tmp=number[i]-'0'+add;//当前进行相加的数字+进位
        if(i==len-1)tmp++;//每次需将number++
        if(tmp>=10)//发生进位
        {
            if(i==0)overFlow=true;//溢出，已达最大值
            else
            {
                add=1;//进位
                number[i]=tmp-10+'0';//设置第i位
            }
        }else//没有进位
        {
            number[i]=tmp+'0';
            break;
        }
    }
    return overFlow;
}
vector<int> printNumbers(int n) {
    char* number=new char[n+1];
    memset(number,'0',n);
    number[n]='\0';
    vector<int> v;
    while (!Increment(number))//溢出，则已到最大值
    {
        v.push_back(atoi(number));//否则存入当前数字
    }
    delete[] number;
    return v;
}
//全排
vector<int> v;
void Recursively(char* number,int length,int index)
{
    if(index==length-1)//递归到个位，结束
    {
        v.push_back(atoi(number));//存入当前值
        return;
    }
    for (int i = 0; i < 10; i++)
    {
        number[index+1]=i+'0';//当前index的下一位进行0~9递归
        Recursively(number,length,index+1);
    }
}
vector<int> printNumbers(int n) {
    if(n<=0)return v;
    char* number=new char[n+1];
    memset(number,'0',n);
    number[n]='\0';
    for (int i = 0; i < 10; i++)
    {
        number[0]=i+'0';//从最高位开始，0~9遍历
        Recursively(number,n,0);//传入起始下标0
    }
    v.erase(v.begin());//去除0
    delete[] number;
    return v;
}
int main()
{
   return 0;
}
