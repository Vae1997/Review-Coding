//求1+2+…+n
//要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）
#include<iostream>
using namespace std;
//&&、||的短路效应
int sumNums1(int n) {
    n&&(n+=sumNums1(n-1));
    // !n||(n+=sumNums1(n-1));
    return n;
}
//另外可使用快速乘，参考官方题解
//借助构造方法
class Temp
{
public:
    static int N;
    static int Sum;
    Temp(){++N;Sum+=N;}//在构造方法中累加
    static void Reset(){N=0;Sum=0;}//重置
};
int Temp::N=0;
int Temp::Sum=0;
int sumNums2(int n) {
    Temp::Reset();//每次调用前先重置静态成员，否则会累加
    Temp *t=new Temp[n];
    return t->Sum;
}
//虚函数
class A
{
public:
    virtual int Sum(int n){return 0;}
};
A *Array[2];
class B:public A
{
public:
    int Sum(int n){return Array[!!n]->Sum(n-1)+n;} 
    //!!n
    //n=0时，调用Array[0]->Sum(0-1)+0，return 0
    //n=1时，调用Array[1]->Sum(1-1)+1，递归
    //n>1时，!n=0 !!n=1,因此继续递归
};
int sumNums3(int n) {
    A a; B b;
    Array[0]=&a;//0调用A中的Sum结束递归
    Array[1]=&b;//1调用B中的Sum进行递归
    return Array[1]->Sum(n);
}
//函数指针
typedef int (*fun)(int);//定义名为fun的函数指针，参数int
int End(int n){return 0;}//表示递归结束的方法
int sumNums(int);//声明
static fun f[2]={End,sumNums};//存放函数指针的数组
int sumNums(int n) {
    return n+f[!!n](n-1);//递归，每次传参n-1
}
int main()
{
    return 0;
}
