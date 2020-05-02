//实现单例设计模式
//保证一个类、只有一个实例存在，同时提供能对该实例加以访问的全局访问方法。
#include<iostream>
#include<string>
using namespace std;
//单线程
class Singleton
{
public: 
    //公有的静态方法获取该实例
    static Singleton* getInstance()
    {
        if(instance==NULL)//全局初始化为NULL时，第一次调用构建
        {                   //全局初始化时已经new，则不需要再次构建，直接返回
            instance=new Singleton();
            cout<<"新建实例"<<endl;
        }
        callCount++;
        return instance;
    }
    int getCallCount(){return callCount;}
private:
    //构造方法私有，防止外界创建单例类的对象
    Singleton()
    {
        instance=NULL;callCount=0;
        cout<<"调用构造方法"<<endl;
    }
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
    static Singleton *instance;//类的私有静态指针变量指向类的唯一实例
    static int callCount;
};
//类外全局变量初始化
Singleton* Singleton::instance=NULL;//这里如果直接new，则get实例方法中直接返回即可
int Singleton::callCount=0;
int main()
{
   Singleton *s1=Singleton::getInstance();
   cout<<s1->getCallCount()<<endl;
   Singleton *s2=Singleton::getInstance();
   cout<<s2->getCallCount()<<endl;
   cout<<(s1==s2)<<endl;//同一个实例
   Singleton *s3=s1;
   cout<<(s3==s1)<<endl;//同一个实例
   s3=s2=s1;
   cout<<(s3==s1)<<endl;//同一个实例
}
