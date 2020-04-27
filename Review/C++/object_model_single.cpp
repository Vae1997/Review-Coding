//C++对象模型(单继承)
//https://cloud.tencent.com/developer/article/1155155
#include<iostream>
using namespace std;
class Base {     
public:
    Base(int i) :baseI(i){};
    int getI(){ return baseI; }
    static void countI(){cout<<"调用static countI()"<<endl;};  
    virtual void print(void){ cout << "调用:Base::print()"; }//位于虚表首地址占用2
    //虚析构函数，在虚表占用为4，比普通虚函数多2（略过，无法通过首地址+2调用） 
    virtual ~Base(){cout<<"调用:~Base()"<<endl;}
    virtual void setI(){cout<<"调用:Base::setI()";}//虚表首地址+6访问     
private:
    int baseI; 
    static int baseS;  
};
class Derive : public Base
{
public:
    Derive(int d) :Base(1000),      DeriveI(d){}; 
    // Derive声明的新的虚函数（添加到父类虚表之后，声明位置无关）
    virtual void Drive_print1(){ cout << "调用:Drive::Drive_print1()" ; } 
    //子类虚析构函数声明位置不影响子类虚表 
    virtual ~Derive(){cout<<"调用:~Derive()"<<endl;} 
    // Derive声明的新的虚函数（添加到父类虚表之后，声明位置无关）
    virtual void Drive_print2(){ cout << "调用:Drive::Drive_print2()" ; }     
    //overwrite父类虚函数
    //void print(void){ cout << "调用：Drive::print(),覆盖父类print" ; }//还是父类地址
    //中间隔着父类的虚析构函数（从父类继承到子类的虚表中）
    void setI(){cout<<"调用:Drive::setI()";}//覆盖开辟新地址 
    // Derive声明的新的虚函数（添加到父类虚表之后，声明位置无关）
    virtual void Drive_print3(){ cout << "调用:Drive::Drive_print3()" ; }        
private:
    int DeriveI;
};
typedef void(*Fun)(void);
int main()
{
    Base b(1000);
    cout << "基类对象的地址是：\t"<<&b << endl;
    int * vptrAdree = (int *)(&b);
    cout << "虚函数指针（vprt）的地址是：\t"<<vptrAdree << endl;
    //虚函数表，64位指针8字节
    Fun vfunc = (Fun)*( (int *)*(int*)(&b));//+0访问第1个，Base::print()
    cout << "Base::print()在虚表的地址是：" << (int *)*(int*)(&b) << endl;
    cout << "通过地址,";
    vfunc();//调用:Base::print()
    cout << "\t地址:\t" << *((int *)*(int*)(&b)) << endl;
    cout<<"=======中间隔着基类的虚析构函数============"<<endl;
    cout << "虚析构函数在虚表的起始地址是：" << (int *)*(int*)(&b)+2 << endl;
    vfunc = (Fun)*( (int *)*(int*)(&b)+6);//+6访问第3个，Base::setI()
    cout << "Base::setI()在虚表的地址是：" << (int *)*(int*)(&b)+6 << endl;
    cout << "通过地址,";
    vfunc();//调用:Base::setI()
    cout << "\t地址:\t" << *((int *)*(int*)(&b)+6) << endl;
    cout<<"==========单继承子类对象=============="<<endl;
    Derive d(2000);
    //[0]
    cout << "[0]Base::vptr";
    cout << "\t地址：" << (int *)(&d) << endl;
    //vprt[0]
    cout << "  [0]";
    Fun fun = (Fun)*((int *)*((int *)(&d)));
    fun();//调用:Base::print()
    cout << "\t地址:\t" << *((int *)*((int *)(&d))); 
    cout << "\t在虚表的地址是：" << (int *)*(int*)(&d) << endl;
    //vprt[1]
    cout << "  [1]";//此处是父类的虚析构函数
    cout << "\t父类的虚析构函数在虚表的起始地址是：" << (int *)*(int*)(&d)+2 << endl;
    //vprt[2]
    cout << "  [2]";//+6访问（隔了虚析构函数+4）
    Fun fun2 = (Fun)*((int *)*((int *)(&d)) + 6);
    fun2();//调用:Drive::setI()
    cout << "\t地址:\t" << *((int *)*((int *)(&d)) + 6);
    cout << "\t在虚表的地址是：" << (int *)*(int*)(&d)+6 << endl;
    //vprt[3]
    cout << "  [3]";//+8访问（一般虚函数+2）
    Fun fun3 = (Fun)*((int *)*((int *)(&d)) + 8);
    fun3();//调用：Drive::Drive_print()
    cout << "\t地址:\t" << *((int *)*((int *)(&d)) + 8);
    cout << "\t在虚表的地址是：" << (int *)*(int*)(&d)+8 << endl;
    //vprt[4]
    cout << "  [4]";//+10访问（一般虚函数+2）
    Fun fun4 = (Fun)*((int *)*((int *)(&d)) + 10);
    fun4();//调用：Drive::Drive_print()
    cout << "\t地址:\t" << *((int *)*((int *)(&d)) + 10);
    cout << "\t在虚表的地址是：" << (int *)*(int*)(&d)+10 << endl;
    //vprt[5]
    cout << "  [5]";//+12访问（一般虚函数+2）
    Fun fun5 = (Fun)*((int *)*((int *)(&d)) + 12);
    fun5();//调用：Drive::Drive_print()
    cout << "\t地址:\t" << *((int *)*((int *)(&d)) + 12);
    cout << "\t在虚表的地址是：" << (int *)*(int*)(&d)+12 << endl;
    //[1]基类成员
    cout << "[1]Base::baseI=" << *(int*)((int *)(&d) + 2);
    cout << "\t地址：" << (int *)(&d) + 1;
    cout << endl;
    //[2]子类成员
    cout << "[2]Derive::DeriveI=" << *(int*)((int *)(&d) + 3);
    cout << "\t地址：" << (int *)(&d) + 2;
    cout << endl;
    cout<<"虚表继承父类的，重写的虚函数新开辟空间覆盖，新增的虚函数加到虚表末尾"<<endl;
    return 0;
}
