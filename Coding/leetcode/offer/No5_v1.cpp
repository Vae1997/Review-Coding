//面试题5：替换空格
/*
请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
输入：s = "We are happy."
输出："We%20are%20happy."
限制：0 <= s 的长度 <= 10000
*/
#include<iostream>
#include<string>
using namespace std;
//借助辅助字符数组
string replaceSpace(string s) {
    if(&s==nullptr)return NULL;//排除未初始化的字符串
    if(s.empty())return s;//排除空字符串“”
    int length=s.length();
    int spaces=0;//统计字符串中的空格数
    for (int i = 0; i < length; i++)
        if(s[i]==' ')spaces++;
    if(spaces==0)return s;//没有空格，直接返回源字符串
    char *c=(char*)malloc(30005*sizeof(char));//申请最大字符数组
    int j=0;//字符数组下标
    for (int i = 0; i < length; i++)
    {
        if(s[i]!=' ')//不是空格，赋值到字符数组
        {
            c[j]=s[i];j++;
        }
        else//空格所在位置赋值%20
        {
            c[j]='\%';j++;
            c[j]='2';j++;
            c[j]='0';j++;
        }
    }
    //检索字符串结束，字符数组下一位置为\0
    c[j]='\0';//避免输出字符数组中无效的字符
    string res=c;//赋值后，输出res时遇到\0则停止
    return res;
}
int main()
{
    string s = " A C ";
    cout<<replaceSpace(s)<<endl;
    s = "  A  C  ";
    cout<<replaceSpace(s)<<endl;
    s="123";
    cout<<replaceSpace(s)<<endl;
    string e;
    cout<<replaceSpace(e)<<endl;
    e="";
    cout<<replaceSpace(e)<<endl;
    e=" ";
    cout<<replaceSpace(e)<<endl;
    e="       ";
    cout<<replaceSpace(e)<<endl;
    return 0;
}
