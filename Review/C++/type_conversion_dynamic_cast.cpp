//dynamic_cast类型转换详细说明
//用于多态类型的转换
//执行运行时类型检查
//只适用于指针或引用
//对不明确的指针的转换将失败（返回 nullptr），但不引发异常
//可以在整个类层次结构中移动指针，包括向上转换、向下转换
#include<iostream>
using namespace std;
class B{};
class D:public B{};
class Base{
public:
    Base(int a = 0): m_a(a){ }
    int get_a() const{ return m_a; }
    virtual void func() const {cout<<"Base::func()"<<endl;}
protected:
    int m_a;
};
class Derived: public Base{
public:
    Derived(int a = 1, int b = 1): Base(a), m_b(b){ }
    int get_b() const { return m_b; }
    void func() const {cout<<"Derived::func()"<<endl;}
private:
    int m_b;
};
int main()
{
    //父类->子类 static_cast不做检查
    B *b=NULL;   
    D *d=static_cast<D*> (b);
    //父类->子类 dynamic_cast检查（父类需要虚函数）
    //运行时 dynamic_cast 的操作数必须包含多态类类型
    //D *d=dynamic_cast<D*> (b);
    cout<<"向上转，一定成功,同静态，不检查"<<endl;
    //情况①,正常
    Derived *pd1 = new Derived(35, 78);
    Base *pb1 = dynamic_cast<Derived*>(pd1);//子转基
    cout<<"pd1 = "<<pd1<<", pb1 = "<<pb1<<endl;
    cout<<pb1->get_a()<<endl;
    pb1->func();//多态，调用子类方法
    //情况②
    int n = 100;
    //无条件将n转为子类对象
    Derived *pd2 = reinterpret_cast<Derived*>(&n);
    //pd2->func();无法正常输出，内存错误
    cout<<"垃圾值："<<pd2->get_a()<<endl;//0 垃圾值
    //子转基,子类不是正常的，但由于是向上转，不会检查
    Base *pb2 = dynamic_cast<Base*>(pd2);
    cout<<"pd2 = "<<pd2<<", pb2 = "<<pb2<<endl;
    cout<<"垃圾值："<<pb2->get_a()<<endl;  //输出一个垃圾值 0
    //pb2->func();  //内存错误，n不是子类对象，找不到虚函数表
    cout<<"向下转，有风险，但会检查"<<endl;
    //对于指针，如果转换失败将返回 NULL
    //对于引用，如果转换失败将抛出std::bad_cast异常。
    //情况①,基类对象指向的是基类，向下转均失败
    Base *base=new Base();
    //没有错误，但转换失败返回NULL
    Derived *derived=dynamic_cast<Derived*> (base);
    if(derived == NULL){
        cout<<"Downcasting failed"<<endl;
    }
    try {  //引用，报std::bad_cast异常
        Derived &derived2=dynamic_cast<Derived&> (*base);
    }  
    catch (bad_cast b) {  
        cout << "Caught: " << b.what()<<endl;  
    }    
    cout<<"-------------------------"<<endl;
    //情况②，基类对象指向的是子类
    base = new Derived();
    derived = dynamic_cast<Derived*>(base);  //向下转型成功
    if(derived != NULL){
        cout<<"Downcasting successfully"<<endl;
        derived -> func();//子类重写了，调用子类，否则调用基类
    }
    return 0;
}
