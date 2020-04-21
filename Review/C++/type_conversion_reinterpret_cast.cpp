//reinterpret_cast类型转换
/*
    用于位的简单重新解释
    滥用 reinterpret_cast 运算符可能很容易带来风险。 
    除非所需转换本身是低级别的，否则应使用其他强制转换运算符之一。
    允许将任何指针转换为任何其他指针类型
    （如 char* 到 int* 或 One_class* 到 Unrelated_class* 之类的转换，但其本身并不安全）
    也允许将任何整数类型转换为任何指针类型以及反向转换。
    reinterpret_cast 运算符不能丢掉 const、volatile 或 __unaligned 特性。
    reinterpret_cast 的一个实际用途是在哈希函数中，
    即，通过让两个不同的值几乎不以相同的索引结尾的方式将值映射到索引。
*/
#include<iostream>
#include<cstdint>
using namespace std;
class A{
public:
    A(int a = 0, int b = 0): m_a(a), m_b(b){}
private:
    int m_a;
    int m_b;
};
// Returns a hash code based on an address
//var 定义为intptr_t，unsigned int提示精度丢失
unsigned short Hash( void *p ) {
   intptr_t val = reinterpret_cast<intptr_t>( p );
   return ( unsigned short )( val ^ (val >> 16));
}
int main()
{
    //将 char* 转换为 float*
    char str[]="https";
    float *p1 = reinterpret_cast<float*>(str);
    cout<<*p1<<endl;
    //将 int 转换为 int*
    int *p = reinterpret_cast<int*>(100);
    //cout<<*p<<endl;运行错误
    //将 A* 转换为 int*
    p = reinterpret_cast<int*>(new A(25, 96));
    cout<<*p<<endl;
    cout<<"------------"<<endl;
    int a[20];
    for ( int i = 0; i < 20; i++ )
      cout << Hash( a + i ) << endl;
    return 0;
}
