//面试题1：赋值运算符函数
//如下为类型CMyString的声明，为该类添加赋值运算符函数
//https://blog.csdn.net/fengyelengfeng/article/details/49863785
//https://blog.csdn.net/whz_zb/article/details/6387784
#include<iostream>
#include<cstring>
#include<string>
#define OK "OK"
#define NO "NO" 
using namespace std;
class CMyString
{
public:
    CMyString(char* pData=nullptr);//构造
    CMyString(const CMyString& str);//拷贝
    CMyString& operator=(const CMyString& str);//赋值
    ~CMyString();//析构
private:
    char* m_pData;
};
CMyString::CMyString(char* pData)
{
    cout<<"构造函数，";
    if(NULL==pData)//处理NULL
    {
        cout<<"构造参数为NULL，";
        m_pData=new char;
        *m_pData='\0';
        cout<<"构造*m_pData==\\0......"<<((*m_pData=='\0')?OK:NO)<<endl;
    }
    else
    {
        cout<<"构造参数为"<<pData<<"，";
        //函数strlen 返回的是有效字符串长度，不包含结束符‘\0’。
        m_pData=new char[strlen(pData)+1];//+1为了\0
        //函数strcpy 则连‘\0’一起复制
        strcpy(m_pData,pData);
        cout<<"构造"<<m_pData<<"......"<<((*m_pData==*pData)?OK:NO)<<endl;
    }
}
//没有重载=的拷贝构造
CMyString::CMyString(const CMyString& str)
{
    cout<<"拷贝构造函数，拷贝对象str：";
    if(*str.m_pData=='\0') cout<<"*str.m_pData==\\0";
    else cout<<str.m_pData;
    m_pData=new char[strlen(str.m_pData)+1];
    strcpy(m_pData,str.m_pData);
    cout<<"，拷贝"<<m_pData<<"......"<<((*m_pData==*str.m_pData)?OK:NO)<<endl;
}

//拷贝构造函数使用赋值运算符重载的代码。
/*
CMyString::CMyString(const CMyString& str)
{
    cout<<"拷贝构造函数，拷贝对象str：";
    if(*str.m_pData=='\0') cout<<"*str.m_pData==\\0";
    else cout<<str.m_pData;
    m_pData=NULL;
    *this=str; //调用重载后的"="
    cout<<"，拷贝"<<m_pData<<"......"<<((*m_pData==*str.m_pData)?OK:NO)<<endl;
}*/
//赋值构造
/*
    1.返回类型为：ClassName&，确保可以连续赋值
    2.参数类型为：const ClassName&，const确保不会修改实参，&避免调用拷贝构造
    3.赋值前delete自身已有内存
    4.this==&other，对自身赋值时直接return *this；避免delete自身后找不到赋值对象
*//*
CMyString& CMyString::operator=(const CMyString& str)
{
    cout<<"\n赋值构造函数，赋值对象str：";
    if(*str.m_pData=='\0') cout<<"*str.m_pData==\\0";
    else cout<<str.m_pData;
    if(this!=&str)//自身赋值直接返回*this
    {
        if(NULL!=m_pData)delete m_pData;//赋值前先delete释放
        m_pData=new char[strlen(str.m_pData)+1];
        strcpy(m_pData,str.m_pData);
        cout<<"，赋值"<<m_pData<<"......"<<((*m_pData==*str.m_pData)?OK:NO)<<endl;
    }
    else cout<<"，赋值本身，直接返回*this"<<"......"<<((this==&str)?OK:NO)<<endl;
    return *this;   
}*/
//考虑异常安全性的解法（会调用拷贝构造，因此拷贝构造只能用原始的方法）
CMyString& CMyString::operator=(const CMyString& str)
{
    cout<<"\n赋值构造函数，赋值对象str：";
    if(*str.m_pData=='\0') cout<<"*str.m_pData==\\0";
    else cout<<str.m_pData;
    if(this!=&str)
    {
        //创建临时对象（new时若内存不足，不影响原对象）
        CMyString strTemp(str);//这里调用拷贝构造
        char* pTemp=strTemp.m_pData;//保存赋值对象的值
        strTemp.m_pData=m_pData;//保存原对象的值
        m_pData=pTemp;//赋值
    }else cout<<"，赋值本身，直接返回*this"<<"......"<<((this==&str)?OK:NO)<<endl;
    return *this;//方法结束，调用析构，析构strTemp
}
CMyString::~CMyString()
{
    if(*m_pData=='\0') cout<<"析构函数，*m_pData==\\0"<<endl;
    else cout<<"析构函数，delete："<<m_pData<<endl;
    delete m_pData;
}
int main()
{
    CMyString a;
    CMyString b("xyz");
    CMyString c(a);//拷贝
    CMyString d(b);
    c=a;//赋值
    c=d;
    c=c;
    cout<<"====连续赋值示例====================="<<endl;
    c=c=b=a;
    return 0;
}
