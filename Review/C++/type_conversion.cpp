//c++类型转换4个关键字
//c任意类型转换没有限制，且转换的位置不容易查找，不利于排错
//http://c.biancheng.net/cpp/biancheng/view/3297.html
#include<iostream>
using namespace std;
class Base
{
public:
    virtual void thing(){cout<<"Base"<<endl;}
};
class Son1:public Base
{
public:
    void thing(){cout<<"Son1"<<endl;}
};
class Son2:public Base
{
public:
    void thing(){cout<<"Son2"<<endl;}
};
struct A{int a;};
class Book{};
int main()
{
    double PI=3.1415926;
    int n1=(int)PI;//c，强制转换
    int n2=PI;//隐式转换
    //static_cast<Type> (name),静态转换，最多
    //编译期即可转换,可以进行一部分检查
    //主要用于C++中内置的基本数据类型之间的转换，但是没有运行时类型的检测来保证转换的安全性
    int n3=static_cast<int> (PI);
    cout<<n1<<" "<<n2<<" "<<n3<<endl;
    cout<<"--------"<<endl;
    //dynamic_cast<Type> (name),用于多态中的父子类之间的强制转化
    Base *b=NULL;
    b=new Son1();//b为Son1类型
    b->thing();//Son1
    Son2 *s2=dynamic_cast<Son2 *> (b);//Son1转换Son2失败返回NULL
    if(s2==NULL)cout<<"转换失败！"<<endl;
    Son1 *s1=dynamic_cast<Son1 *> (b);//转换成功
    if(s1!=NULL)s1->thing();   
    Base *bb=new Base();
    bb->thing();
    Son1 *s11=dynamic_cast<Son1 *> (bb);//Base转Son1同样会失败
    if(s11==NULL)cout<<"转换失败！"<<endl;
    cout<<"--------"<<endl;
    //const_cast<Type> (name), 去掉const属性转换
    //目标类类型只能是指针或引用。
    const A a={100};
    cout<<a.a<<" "<<&a.a<<endl;
    // A a1=const_cast<A> (a);非法
    A *a1=const_cast<A *> (&a);
    cout<<a1->a<<" "<<&a1->a<<endl;
    a1->a=200;
    cout<<a.a<<" "<<a1->a<<endl;
    A &a2=const_cast<A &> (a);
    cout<<a2.a<<" "<<&a2.a<<endl;
    a2.a=300;
    cout<<a.a<<" "<<a2.a<<endl;//a、a1、a2同一个地址
    const int x=1;//x在编译期间就确定为1
    cout<<x<<" "<<&x<<endl;
    int *x1=const_cast<int *> (&x);
    cout<<*x1<<" "<<x1<<endl;
    *x1=2;
    cout<<x<<" "<<*x1<<endl;
    int &x2=const_cast<int &> (x);
    cout<<x2<<" "<<&x2<<endl;
    x2=3;
    cout<<x<<" "<<x2<<endl;//因此x值不变
    cout<<"--------"<<endl;
    Base *base=NULL;
    //Son1 *s1=base;父类直接赋值子类非法，需转换
    Son1 *s1=static_cast<Son1 *> (base);
    Base *base1=s1;//子类可以直接赋值为父类
    //static_cast无法在无关的类之间进行转换
    //Book *book=static_cast<Book *> (base);
    //reinterpret_cast可以强制类型转换
    Book *book=reinterpret_cast<Book *> (base);
    return 0;
}
