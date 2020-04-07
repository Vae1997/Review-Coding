#include <iostream>
using namespace std;
class Base  
{
public:
    int i;
    Base(){cout<<"Base::Base() is called"<<endl;}
    Base(int num):i(num){cout<<"Base::Base(int num) is called"<<endl;}
    //基类虚函数表中存有Base::basef1和Base::basef2
    virtual void basef1(){cout<<"Base::basef1() is called"<<endl;}
    virtual void basef2(){cout<<"Base::basef2() is called"<<endl;}
    void basef3(){cout<<"Base::basef3() is called"<<endl;}
};
class A:public Base
{ 
public:
    int j;
    A(int num):j(num){cout<<"A::A(int num) is called"<<endl;}
    //子类重写基类虚函数,子类的虚函数表中改为：A::basef1
    void basef1(){cout<<"A::basef1() is called"<<endl;}
    //子类新增的虚函数，子类虚函数表增加：A::af1
    virtual void af1(){cout<<"A::af1() is called"<<endl;}
    //子类未重写的虚函数，子类虚函数表继承：Base::basef2
};
int main()
{
    //每一个有虚函数的类（或有虚函数的类的派生类）都有一个虚函数表
    Base b;//Base::Base() is called
    Base b1(1);//Base::Base(int num) is called
    A a1(2);//Base::Base() is called ===> A::A(int num) is called
    //a1对象中还存放了指向A类虚函数表的指针
    Base *bp=&a1;//基类对象的指针，指向子类对象（实际指向了A类的虚函数表）
    Base &bb=a1;//基类对象的引用，指向子类对象(同指针)
    bp->basef1();//子类重写，调用子类重写的方法（从虚函数表中查找basef1方法，调用：A::basef1）
    bp->basef2();//子类未重写，调用基类方法（从虚函数表中查找basef2方法，调用：Base::basef2）
    bp->basef3();//调用基类的普通方法（basef3是普通方法，不在表中）
    cout<<bp->i<<endl;//访问基类的成员变量   
    return 0;
}

