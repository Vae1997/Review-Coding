//参考：http://c.biancheng.net/view/2251.html
//问题九：方法中返回临时变量的引用会有什么风险吗？
#include <iostream>
using namespace std;
//返回int类型,return时会创建临时量
int f_A()
{
    int A=5;
    cout<<"A:"<<A<<" &A:"<<&A<<endl;
    return A;//返回后，A虽然被销毁，但是A的值赋给了创建的临时量t
    //int t=A;
}
//返回引用类型，不会创建临时量
int &f_B()
{
    int B=1;
    cout<<"B:"<<B<<" &B:"<<&B<<endl;
    return B;//warning！B销毁后由于没有临时量，返回的引用已经销毁
}
int &f_C(int &cc)
{
    cout<<"cc:"<<cc<<" &cc:"<<&cc<<endl;
    int &C=cc;
    cout<<"C:"<<C<<" &C:"<<&C<<endl;
    //return cc;
    return C;//返回的C<引用>形参cc<引用>实参t
}
int main()
{
    int a=f_A();//相当于int a=t;
    //int &aa=f_A();//错误，对return后临时生成的量引用无效
    cout<<"a:"<<a<<" &a:"<<&a<<endl;//5
    cout<<"------"<<endl;  
    // int b=f_B();结果根据编译器而不同
    // int &b=f_B();同上
    int t=8;
    cout<<"t:"<<t<<" &t:"<<&t<<endl;
    int c=f_C(t);//c是新的变量
    cout<<"c:"<<c<<" &c:"<<&c<<endl;//8
    cout<<"------"<<endl;  
    int &cc=f_C(t);//引用cc只是t的别名
    cout<<"cc:"<<cc<<" &cc:"<<&cc<<endl;//地址一致
}
