//面试题2：单例设计模式
//这里是最后的扩展问题，基本的参见：c++相关验证操作的singleton.cpp和singletonC11.cpp
//要求定义一个表示总统的类型President
//可从该类型继承出FrenchPresident和AmericanPresident等类型
//派生类只能产生一个实例，如何设计？
#include<iostream>
using namespace std;
//只是单独创建不同的子类，更方便的是要将单例基类写为模板
//子类将自身作为模板参数并将父类声明为友元类
//参考：https://www.cnblogs.com/sunchaothu/p/10353507.html
class President
{
protected://注意父类构造方法为protected，确保子类可以访问
    President(){cout<<"构造President..."<<endl;}
    ~President(){cout<<"析构President..."<<endl;}
private:
    President(const President&);
    President& operator=(const President&);
    static int callCount;
public:    
    static int getCallCount(){return callCount;}
    static President* getInstance()
    {
        static President instance;
        callCount++;
        return &instance;
    }
};
int President::callCount=0;
class FrenchPresident:public President
{
private:
    FrenchPresident(){cout<<"构造FrenchPresident..."<<endl;}
    ~FrenchPresident(){cout<<"析构FrenchPresident..."<<endl;}
    FrenchPresident(const FrenchPresident&);
    FrenchPresident& operator=(const FrenchPresident&);
    static int callCount;
public:
    static int getCallCount(){return callCount;}
    static FrenchPresident* getInstance()
    {
        static FrenchPresident instance;
        callCount++;
        return &instance;
    }
};
int FrenchPresident::callCount=0;
int main()
{
   President *p;p->getInstance();
   cout<<p->getCallCount()<<endl;
   President *p1=President::getInstance();
   cout<<p1->getCallCount()<<endl;
   cout<<(p==p1)<<endl;
   p=p1;cout<<(p==p1)<<endl;
   President *p2=President::getInstance();
   cout<<p2->getCallCount()<<endl;
   cout<<(p1==p2)<<endl;
   cout<<(p==p2)<<endl;
   cout<<"-----------------"<<endl;
   FrenchPresident *fp1=FrenchPresident::getInstance();
   cout<<fp1->getCallCount()<<endl;
   FrenchPresident *fp2=FrenchPresident::getInstance();
   cout<<fp2->getCallCount()<<endl;
   cout<<(fp1==fp2)<<endl;
  
}
