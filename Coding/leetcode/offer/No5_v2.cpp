//面试题5：替换空格
/*
请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
输入：s = "We are happy."
输出："We%20are%20happy."
限制：0 <= s 的长度 <= 10000
*/
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
//在源字符串上修改
string replaceSpace(string s) {
    if(&s==nullptr)return NULL;//排除未初始化的字符串
    if(s.empty())return s;//排除空字符串“”
    int length=s.length();
    int spaces=0;//统计字符串中的空格数
    for (int i = 0; i < length; i++)
        if(s[i]==' ')spaces++;
    if(spaces==0)return s;//没有空格，直接返回源字符串
    int end=length;//源字符串包括\0的下标
    int newend=end+spaces*2;//修改后的下标
    char *c =new char[newend+1];//参数如果是字符数组，则不需要借助
    strcpy(c,s.c_str());//参数s转换为字符数组
    while (end>=0 && newend>=end)//只用字符数组进行循环操作
    {
        if(c[end]!=' ')c[newend--]=c[end];
        else
        {
            c[newend--]='0';
            c[newend--]='2';
            c[newend--]='%';
        }
        end--;
    }
    s=c;//字符数组重新赋值给s
    return s;
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
