//测试验证拷贝构造函数
//不写复制构造函数，编译器就会自动生成复制构造函数。
//作用是实现从源对象到目标对象逐个字节的复制，即使得目标对象的每个成员变量都变得和源对象相等。
//编译器自动生成的复制构造函数称为“默认复制构造函数”。

//注意，默认构造函数（即无参构造函数）不一定存在，但是复制构造函数总是会存在。
#include <iostream>
using namespace std;
//类中拷贝构造函数参数为非const引用
class T1
{
public:
    double real, imag;
    //构造函数
    T1(double r,double i)
    {
        real = r; imag = i;
    }
    //拷贝，参数为非const引用
    T1(T1 & t)
    {
        real = t.real; imag = t.imag;
        cout<<"T1 Copy Constructor called"<<endl ;
    }
};
//类中拷贝构造函数参数为const引用
class T2
{
public:
    double real, imag;
    //构造函数
    T2(double r,double i)
    {
        real = r; imag = i;
    }
    //构造函数不能以本类的对象作为唯一参数，以免和复制构造函数相混淆。
    // T2(T2 t)
    // {
    //     cout<<"Constructor called"<<endl ;
    // }
    //合法的构造函数
    T2(T2 t,double r,double i)
    {
        real = r; imag = i;
        cout<<"Constructor called"<<endl ;
    }
    //拷贝，参数一般为const引用（初始化后不能修改值但可以改变对象）
    T2(const T2 & t)
    {
        real = t.real; imag = t.imag;
        cout<<"T2 Copy Constructor called"<<endl ;
    }
};
//两种拷贝构造函数
class T3
{
public:
    double real, imag;
    //构造函数
    T3(double r,double i)
    {
        real = r; imag = i;
    }
    //拷贝，参数为非const引用
    T3(T3 & t)
    {
        real = t.real+1; imag = t.imag+1;
        cout<<"T3 Copy Constructor called with none const"<<endl ;
    }
    //拷贝，参数一般为const引用（初始化后不能修改值但可以改变对象）
    T3(const T3 & t)
    {
        real = t.real; imag = t.imag;
        cout<<"T3 Copy Constructor called with const"<<endl ;
    }
    //T3成员函数
    void set(double r,double i)
    {
        real = r; imag = i;
    }
};
void Func(T3 t)
{
    cout<<"Func is called:"<<t.real<<" "<<t.imag<<endl;
    t.imag-=2;
    t.real-=2;
    cout<<"Func is over:"<<t.real<<" "<<t.imag<<endl;
}
void Func2(T3 &t)
{
    cout<<"Func2 is called:"<<t.real<<" "<<t.imag<<endl;
    t.imag-=3;
    t.real-=3;
    cout<<"Func2 is over:"<<t.real<<" "<<t.imag<<endl;
}
void Func3(const T3 t)
{
    cout<<"Func3 is called:"<<t.real<<" "<<t.imag<<endl;
    // t.imag-=3;
    // t.real-=3;不可修改
}
//const确保实参的值不会改变
//&避免复制构造函数带来的开销
//将形参声明为对象的 const 引用
void Func4(const T3 &t)
{
    //t.set(1,1);非法，无法调用成员函数
    cout<<"Func4 is called:"<<t.real<<" "<<t.imag<<endl;
}
T3 Func11()
{
    T3 *t = new T3(8,8);
    return *t;//调用非const拷贝构造后+1
}
T3 & Func22()
{
    T3 *t = new T3(4,4);
    return *t;//返回引用，不会调用拷贝构造函数
}
T3 Func33()
{
    const T3 *t = new T3(3,3);
    return *t;//调用const拷贝构造函数
}
const T3 & Func44()
{
    const T3 *t = new T3(7,7);
    return *t;//返回引用，不会调用拷贝构造函数
}
// 防止按值传递
class CExample 
{
private:
	int a;
public:
	//构造函数
	CExample(int b)
	{ 
		a = b;
		cout<<"creat: "<<a<<endl;
	}
private:
	//拷贝构造，只是声明
	CExample(const CExample& C);
};

//全局函数
void g_Fun(CExample C)
{
	cout<<"test"<<endl;
}
CExample g_Fun()
{
	CExample *C = new CExample(2);
    //return *C; 不可访问
}
int main()
{
    T1 t1(1,2);
    T1 t11(t1);//非const对象作为参数，合法
    cout<<t11.real<<" "<<t11.imag<<endl;
    const T1 constT1(3,4);//const对象
    //T1 t111(constT1);无法初始化
    const T2 constT2(3,4);
    T2 t2(constT2);//T2的拷贝构造函数参数为const引用，合法
    cout<<t2.real<<" "<<t2.imag<<endl;
    T2 t22(t2);//也可以使用非const对象初始化，合法
    cout<<t22.real<<" "<<t22.imag<<endl;
    //T2 t222(constT2,1,1);//合法
    //T2 t2222(t2,2,2);//合法
    cout<<"-------------------"<<endl;
    //复制构造函数调用时机
    const T3 constT3(8,8);//初始化
    T3 t3 = constT3;//初始化同类对象，调用，等价于T3 t3(constT3)
    cout<<t3.real<<" "<<t3.imag<<endl;
    T3 t33(t3);//初始化,注意，T3包含非const拷贝构造函数，成员+1
    cout<<t33.real<<" "<<t33.imag<<endl;
    t3=t33;//t3已经初始化，该句为赋值，不会调用
    cout<<t3.real<<" "<<t3.imag<<endl;
    cout<<"-------作为形参的对象，是用复制构造函数初始化------------"<<endl;
    Func(constT3);//作为形参的对象，是用复制构造函数初始化
    cout<<constT3.real<<" "<<constT3.imag<<endl;
    Func(t3);//T3的非const拷贝成员+1，方法里面-2，但是不影响实参
    cout<<t3.real<<" "<<t3.imag<<endl;
    cout<<"-------------------"<<endl;
    //Func2(constT3);形参非const，非法
    Func2(t3);//T3的非const拷贝成员+1，方法里面-3，引用传递影响实参
    //同时注意，此时的引用传递，并未调用拷贝构造函数
    cout<<t3.real<<" "<<t3.imag<<endl;
    cout<<"-------------------"<<endl;
    Func3(constT3);//合法，调用拷贝
    cout<<constT3.real<<" "<<constT3.imag<<endl;
    Func3(t3);//合法，调用拷贝+1,不影响实参
    cout<<t3.real<<" "<<t3.imag<<endl;
    cout<<"-------------------"<<endl;
    Func4(constT3);//合法，引用参数不调用拷贝,const不会修改实参
    cout<<constT3.real<<" "<<constT3.imag<<endl;
    Func4(t3);//合法，引用参数不调用拷贝,const不会修改实参
    cout<<t3.real<<" "<<t3.imag<<endl;
    cout<<"作为函数返回值的对象是用复制构造函数初始化的"<<endl;
    t3=Func11();//调用非const，成员+1
    cout<<t3.real<<" "<<t3.imag<<endl;
    t3=Func22();//引用，不会调用
    cout<<t3.real<<" "<<t3.imag<<endl;
    t3=Func33();
    cout<<t3.real<<" "<<t3.imag<<endl;
    t3=Func44();
    cout<<t3.real<<" "<<t3.imag<<endl;
    cout<<"---------------"<<endl;
    CExample test(1);
	//g_Fun(test); //按值传递将出错	
    return 0;
}
