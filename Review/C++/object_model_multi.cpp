//C++对象模型(单继承)
//https://cloud.tencent.com/developer/article/1155155
#include<iostream>
using namespace std;
class Base
{
public: 
    Base(int i,int j) :baseI(i),baseII(j){};
    virtual ~Base(){ cout << "Base::~Base"; }
    virtual void print(void){ cout << "Base::print()"; } 
    virtual void print2(void){ cout << "Base::print2()"; } 
private: 
    int baseI;
    int baseII;
};
class Base_2
{
public:
    Base_2(int i) :base2I(i){};
    virtual ~Base_2(){ cout << "Base_2::~Base_2"; }
    virtual void print(void){ cout << "Base_2::print()"; } 
    virtual void print2(void){ cout << "Base_2::print2()"; } 
private: 
    int base2I;
};
class Drive_multyBase :public Base, public Base_2
{
public:
    Drive_multyBase(int d) :Base(1000,1001), Base_2(2000) ,Drive_multyBaseI(d){};
    virtual void print(void){ cout << "Drive_multyBase::print" ; } 
    virtual void Drive_print(){ cout << "Drive_multyBase::Drive_print" ; }
    virtual ~Drive_multyBase(){ cout << "Drive_multyBase::~Drive_multyBase" ;};
private:
    int Drive_multyBaseI;
};
typedef void(*Fun)(void);
int main()
{
    Drive_multyBase d(3000);
    //[0]
    cout << "[0]Base::vptr";
    cout << "\t地址：" << (int *)(&d) << endl;
    //略过基类虚析构函数
    cout << "  [0]此处为基类虚析构函数Base::~Base"<<endl;
    //vprt[1]
    cout << "  [1]";
    Fun fun1 = (Fun)*((int *)*((int *)(&d))+4);
    fun1();//Drive_multyBase::print 覆盖
    cout << "\t地址:\t" << *((int *)*((int *)(&d))+4) << endl;
    //vprt[2]
    cout << "  [2]";
    Fun fun2 = (Fun)*((int *)*((int *)(&d)) + 6);
    fun2();//Base::print2() 子类未覆盖的方法
    cout << "\t地址:\t" << *((int *)*((int *)(&d)) + 6) << endl;
    //vprt[3]
    cout << "  [3]";
    Fun fun3 = (Fun)*((int *)*((int *)(&d)) + 8);
    fun3();//Drive_multyBase::Drive_print，在首个基类虚表后面添加新的虚函数
    cout << "\t地址:\t" << *((int *)*((int *)(&d)) + 8) << endl;
    //[1]基类1成员
    cout << "[1]Base::baseI=" << *(int*)((int *)(&d) + 2);
    cout << "\t地址：" << (int *)(&d) + 2;
    cout << endl; 
    cout << "[2]Base::baseII=" << *(int*)((int *)(&d) + 3);
    cout << "\t地址：" << (int *)(&d) + 3;
    cout << endl; 
    //[3]
    cout << "[3]Base_::vptr";
    cout << "\t地址：" << (int *)(&d)+4 << endl;//注意对象指针的偏移（虚指针占2+2个成员）
    //略过基类虚析构函数
    cout << "  [0]此处为基类虚析构函数Base_2::~Base_2"<<endl; 
    //vprt[1]
    cout << "  [1]";
    Fun fun11 = (Fun)*((int *)*((int *)(&d)+4)+4);//隔了虚析构函数+4
    fun11();//Drive_multyBase::print 覆盖
    cout << "\t地址:\t" << *((int *)*((int *)(&d)+4)+4) << endl;
    //vprt[2]
    cout << "  [2]";
    Fun fun22 = (Fun)*((int *)*((int *)(&d)+4)+6);//一般+2
    fun22();//Base_2::print2() 子类未覆盖的方法
    cout << "\t地址:\t" << *((int *)*((int *)(&d)+4)+6) << endl;
    //到此结束，子类新的虚函数不会加入非首个基类的虚表中
    //[4]基类2成员
    cout << "[4]Base_2::base2I=" << *(int*)((int *)(&d) + 6);
    cout << "\t地址：" << (int *)(&d) + 6;
    cout << endl; 
    //[5]子类成员
    cout << "[5]Drive_multyBase::Drive_multyBaseI=" << *(int*)((int *)(&d) + 7);
    cout << "\t地址：" << (int *)(&d) + 7;
    cout << endl;
    return 0;
}
