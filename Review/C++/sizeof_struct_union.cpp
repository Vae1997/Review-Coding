//sizeof中的结构体和联合
#include<iostream>
using namespace std;
struct xx  
{  
    double _x1;  //8 0（开始）
    char _x2;  //1 8+1=9（9是1的倍数）
    int _x3;  //4 9+4=13（13不是4的倍数）+3=16
    char a[6];//1*6 16+6=22（22不是6的倍数）+2=24
    char b[4];//1*4 24+4=28（28是4的倍数，但不是最大成员double分配的8的倍数）+4=32
    static int _x5;  
};  
typedef union  
{  
    long long d;  //8
    int k[3];     //3*4=12（12不是最大元数据类型double8的倍数）+4=16
} DATE;  
struct D  
{  
    int cat;  //4补齐+4=8
    DATE cow;  //16（double8）
    char dog;  //1补齐+7=8
};//一共32
struct D2
{   
    typedef union  
    {  
        long long d;   
    } DATE;
};//按空处理
typedef union  
{
    struct s
    {
        long long d;  
    };
} DATE2; //按空处理
struct xx2
{
    double d;//8
    int t[3];//3*4=12+4=16
};//24
typedef union  
{  
    long long d; 
    xx2 a; //24最大
    int k[3];     
} DATE3;
int main()
{
    cout<<sizeof(xx)<<endl;
    cout<<sizeof(DATE)<<endl;
    cout<<sizeof(D)<<endl;
    cout<<sizeof(D2)<<endl;
    cout<<sizeof(DATE2)<<endl;
    cout<<sizeof(DATE3)<<endl;
    return 0;
}
