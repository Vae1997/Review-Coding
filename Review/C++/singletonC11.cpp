//C11之后的单例设计模式
//线程安全
#include<iostream>
using namespace std;
class Singleton
{
private:
    Singleton()
    {
        callCount=0;
        cout<<"调用构造函数"<<endl;
    }
    ~Singleton(){cout<<"调用析构函数"<<endl;}
    Singleton(const Singleton& other);
    Singleton& operator=(const Singleton&);
    static int callCount;
public:
    //注意返回的是引用
    static Singleton& getInstance()
    {
        //使用函数内局部静态对象
        static Singleton instance;
        callCount++;
        return instance;
    }
    //返回指针
    static Singleton* getIns()
    {
        static Singleton ins;
        callCount++;
        return &ins;
    }
    static int getCallCount(){return callCount;}
};
int Singleton::callCount=0;
int main()
{
   cout<<Singleton::getInstance().getCallCount()<<endl;
   cout<<Singleton::getInstance().getCallCount()<<endl;
   cout<<"==========================="<<endl;
   Singleton *s1=Singleton::getIns();
   cout<<s1->getCallCount()<<endl;
   Singleton *s2=Singleton::getIns();
   cout<<s2->getCallCount()<<endl;
   cout<<"s1==s2:"<<(s1==s2)<<endl;//同样的实例
   cout<<"==========================="<<endl;
   return 0;
}
