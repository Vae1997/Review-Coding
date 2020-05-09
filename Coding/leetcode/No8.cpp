//字符串转整数
#include <iostream>
#include <string>
using namespace std;
int myAtoi(string str) 
{    
    if(str.empty())return 0;//排除空串
    long int number=0;//注意为long，否则runtime error:signed integer overflow: 2147483640 + 8 cannot be represented in type 'int'   
    char sign=' ';//符号   
    int tag=0;//溢出标记
    for (int i = 0; i < str.length(); i++)
    {
        char c=str[i];
        if(c==' ' && tag==0 && sign==' ')continue;//空格忽略
        if((c=='+'||c=='-') && tag==0 && sign==' ')sign=c;//标记符号
        else if(c>='0' && c <='9')//数字
        {
            number=number*10+(c-'0');//计算
            if(INT_MAX-number<0){tag=888;break;}//溢出标记
            tag=1;//标记数字               
        }else break;//其他字符直接return    
    }    
    if(tag==888)return sign=='-'?INT_MIN:INT_MAX;//溢出返回   
    return sign=='-'?(-number):number;//正常返回
    /*别人4行代码解决
    stringstream line(s);
    int num = 0;
    line>>num;//以整数方式去读取
    return num;
    */
}
int main()
{
    string s;
    cin>>s;
    cout<<myAtoi(s)<<endl;
    return 0;
}
