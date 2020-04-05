//关于const常量、const指针以及const引用
//参考：https://blog.csdn.net/mysunshinetbg/article/details/48346195
#include <iostream>
using namespace std;
int main()
{
    //常量
    //const int a;初始化时必须赋值
    const int a=0;
    //a=a+1;值不可以改变
    const int b=a;//合法
    int c=b;//合法
    const int d=c;//合法
    cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;//0
    //指针常量(type * const name)
    int * const e=&c;
    cout<<"*e:"<<*e<<" &*e:"<<&*e<<" c:"<<c<<" &c:"<<&c<<endl;
    int f=2;
    //e=&f;不可以修改指针的指向
    *e=f;//但可以修改值
    cout<<"*e:"<<*e<<" &*e:"<<&*e<<" c:"<<c<<" &c:"<<&c<<endl;
    //const指针(const int *name)
    const int *g=&f;
    cout<<"*g:"<<*g<<" &*g:"<<&*g<<" f:"<<f<<" &f:"<<&f<<endl; 
    //*g=c;不可以修改值
    int h=3;
    g=&h;//但可以修改指针的指向
    cout<<"*g:"<<*g<<" &*g:"<<&*g<<" h:"<<h<<" &h:"<<&h<<endl; 
    //const引用(const int &name)
    const int &i=h;//i与h绑定
    //i=4;错误，不能通过const引用改变h的值
    cout<<"i:"<<i<<" &i:"<<&i<<" h:"<<h<<" &h:"<<&h<<endl;
    int j=4;
    int &k=j;
    cout<<"k:"<<k<<" &k:"<<&k<<" j:"<<j<<" &j:"<<&j<<endl;
    //i=j;i=k;不可以修改绑定的对象h 
    int l=5;  
    k=l;//非const引用k，地址没变，值改为l
    cout<<"k:"<<k<<" &k:"<<&k<<" l:"<<l<<" &l:"<<&l<<endl;
    const int x=6;
    //int &y=x;非const引用不能与const对象绑定，但初始化完成后可以用常量赋值，如下
    k=x;//非const引用k，地址没变，值改为常量x，只是赋值操作，k并未绑定x
    cout<<"k:"<<k<<" &k:"<<&k<<" x:"<<x<<" &x:"<<&x<<endl;
    k=999;//非const引用k赋值为999，常量x的值并未改变
    cout<<"k:"<<k<<" &k:"<<&k<<" x:"<<x<<" &x:"<<&x<<endl;
    const int &y=x;//合法（const引用绑定const常量） 
    cout<<"y:"<<y<<" &y:"<<&y<<" x:"<<x<<" &x:"<<&x<<endl;
    return 0;
}
