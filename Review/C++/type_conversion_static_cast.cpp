//static_cast类型转换详细说明
//用于非多态类型的转换
//不执行运行时类型检查（转换安全性不如 dynamic_cast）
//通常用于转换数值数据类型（如 float -> int）
//可以在整个类层次结构中移动指针
//子类转化为父类安全（向上转换隐式转换）
//父类转化为子类不安全（因为子类可能有不在父类的字段或方法）
#include<iostream>
using namespace std;
class Complex{
public:
    Complex():m_real(0),m_imag(0){};  
    Complex(double r, double i):m_real(r),m_imag(i){};  
    Complex(double r):m_real(r),m_imag(0){cout<<"转换构造函数调用"<<endl;};  // 定义转换构造函数
public:
    operator double() const { cout<<"类型转换函数调用"<<endl;return m_real; }  //类型转换函数
public:
    double m_real;
    double m_imag;
    //关于转换构造和类型转换函数参考：
};//https://blog.csdn.net/qianqin_2014/article/details/51316461
class Base{};
class Son:public Base{};
int main()
{
    /*
    1.static_cast 只能用于良性转换，这样的转换风险较低，一般不会发生什么意外，例如：
    原有的自动类型转换，例如 short 转 int、int 转 double、const 转非 const、向上转型等；
    2.void 指针和具体类型指针之间的转换，例如void *转int *、char *转void *等；
    3.有转换构造函数、类型转换函数的类，与其它类型之间的转换，
    例如 double 转 Complex（调用转换构造函数）、Complex 转 double（调用类型转换函数）。
    */
    typedef unsigned char BYTE;
    char ch;
    int i = 65;
    float f = 2.5;
    double dbl;
    ch = static_cast<char>(i);   // int to char
    dbl = static_cast<double>(f);   // float to double
    i = static_cast<BYTE>(ch);
    cout<<ch<<" "<<f<<" "<<i<<" "<<dbl<<endl;
    short s=-128;
    i=static_cast<int> (s);//宽转换，无精度丢失
    char c=static_cast<char> (i);//€,窄转换，超出char范围则丢失
    cout<<s<<" "<<i<<" "<<c<<endl;
    cout<<"---------------------"<<endl;
    const int *a;
    //static_cast 无法丢掉常量或其他类型限定符（使用const_cast）
    //int *b=static_cast<int*> (a);
    int x=1;int *b=&x;
    a=static_cast<int*> (b);//非const赋值给const
    cout<<"--*a:"<<*a<<"------------------"<<endl;   
    //父类->子类（可以转换、但不安全）使用dynamic_cast
    Base *base1=NULL;
    Son *son1=static_cast<Son*> (base1);
    //子类->父类(安全、隐式转换、向上)
    Son *son2=NULL;
    Base *base2=static_cast<Base*> (son2);
    //不能转换为其他类型，使用reinterpret_cast
    //Complex *comp=static_cast<Complex*> (son2);
    cout<<"---------------------"<<endl;
    //将void指针转换为具体类型指针
    int *p1 = static_cast<int*>( malloc(10 * sizeof(int)) );
    cout<<p1<<endl;
    //将具体类型指针，转换为void指针
    void *p2 = static_cast<void*>(p1);  
    //不能在两个具体类型的指针之间进行转换
    //float *p3 = static_cast<float*>(p1);  
    //不能将整数转换为指针类型
    //float *p3 = static_cast<float*>(0X2DF9);  
    cout<<"---------------------"<<endl;
    Complex complex(12.5, 23.8);
    //调用类型转换函数 ->double
    double real= static_cast<double>(complex);  
    cout<<real<<endl;
    //调用类型转换函数 -> Complex
    Complex comp=static_cast<Complex> (real);
    cout<<comp.m_real<<" "<<comp.m_imag<<endl;
    return 0;
}
