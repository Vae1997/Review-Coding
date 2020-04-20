#include<iostream>
using namespace std;
class A
{
private:
    int a;
public:
    A(int aa=0){a=aa;cout<<a<<" 地址："<<&a<<" Constructor Object."<<endl;}
    A(const A &obj){a=obj.a;cout<<a<<" a地址："<<&a<<" Copy Constructor."<<"拷贝对象地址是："<<&obj.a<<endl;}
    ~A(){cout<<a<<" 地址："<<&a<<" Object destroyed"<<endl;}
};
A f()
{
    A *a=new A(2);//构造
    return *a;//拷贝:A xxx=*a;
    //方法结束时销毁*a
}
void t1()
{
    f();//返回xxx对象，方法结束析构xxx
}
void t2()
{
    A a=f();//初始化操作
    //直接将返回的xxx匿名对象命名为a
    cout<<"初始化a，地址："<<&a<<endl;
    //方法结束，析构a
}
void t3()
{
    A a;
    cout<<"a初始化完成，地址："<<&a<<endl;
    a=f();//赋值操作,赋值完成，xxx对象就被析构
    cout<<"a赋值完成,地址："<<&a<<endl;//原始的a对象
    //方法结束，析构a
}
int main()
{
    t1();
    cout<<"---------"<<endl;
    t2();
    cout<<"---------"<<endl;
    t3();
    return 0;
}
