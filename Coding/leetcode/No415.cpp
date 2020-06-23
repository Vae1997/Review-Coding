//字符串相加
#include<iostream>
#include<string>
using namespace std;
//常规解法
string addStrings(string num1, string num2) {
    int l1=num1.size();
    int l2=num2.size();
    int i=l1-1;
    int j=l2-1;
    int add=0;
    string res="";
    while (i!=-1&&j!=-1)//和-1比较，确保0号位数字也已经相加，此时加法结束
    {
        int tmp = (num1[i]-'0')+(num2[j]-'0')+add;
        cout<<tmp<<endl;
        if(tmp>=10)
        {
            add=1;
            res+=to_string(tmp-10);
            cout<<res<<endl;
        }
        else
        {
            add=0;
            res+=to_string(tmp);
        }
        i--;j--;
        cout<<i<<" "<<j<<endl;
    }
    cout<<"res:"<<res<<endl;
    string ts=(i!=-1)?num1:num2;//确定剩余的字符串
    int index=(i!=-1)?i:j;//确定下标
    //有进位则继续相加
    while(add&&index!=-1)
    {
        int tmp=ts[index]-'0'+add;
        if(tmp>=10)
        {
            add=1;
            res+=to_string(tmp-10);
        }
        else
        {
            add=0;
            res+=to_string(tmp);
        }
        index--;
    }
    reverse(res.begin(),res.end());//反转
    //无进位则直接截取剩余字符串到当前字符串
    if(index!=-1)
    {
        ts=ts.substr(0,index+1);
        res=ts+res;//res已经反转，因此可以直接加ts
    }
    else if(add)res="1"+res;//最后一位还有进位，直接+1
    return res;
}
//短的数字字符串补0
string addStrings(string num1, string num2) {
    int l1=num1.size();
    int l2=num2.size();
    int l=0;//0的个数
    string cs="";//补0的字符串
    if(l1!=l2)//长度不等，短的补零
    {
        l=l1>l2?l1-l2:l2-l1;
        cs=l1>l2?num2:num1;
        while(l)
        {
            cs='0'+cs;
            l--;
        }
        if(l1>l2)num2=cs;
        else num1=cs;
    }
    cout<<num1<<" "<<num2<<endl;
    l1=num1.size();
    l2=num2.size();
    int i=l1-1;
    int j=l2-1;
    int add=0;
    string res="";
    //正常循环计算
    while (i>=0&&j>=0)
    {
        int tmp = (num1[i]-'0')+(num2[j]-'0')+add;
        cout<<tmp<<endl;
        if(tmp>=10)
        {
            add=1;
            res+=to_string(tmp-10);
            cout<<res<<endl;
        }
        else
        {
            add=0;
            res+=to_string(tmp);
        }
        i--;j--;
        cout<<i<<" "<<j<<endl;
    }
    if(add)res+="1";
    reverse(res.begin(),res.end());
    return res;
}
//直接在每次计算时再加零
//参考：https://leetcode-cn.com/problems/add-strings/solution/add-strings-shuang-zhi-zhen-fa-by-jyd/
//评论中的C++
string addStrings(string num1, string num2) {
    string ans="";
    int Fir_len = num1.size()-1,Sec_len = num2.size()-1,carry=0;
    while(Fir_len>=0 || Sec_len>=0){
        int n = Fir_len>=0 ? num1[Fir_len--]-'0' : 0;//每次循环进行判断
        int m = Sec_len>=0 ? num2[Sec_len--]-'0' : 0;
        int tmp = n+m+carry;
        carry = tmp/10;//除10判断进位
        ans+=to_string(tmp%10);//求余确定当前位
    }
    if(carry==1){//最后一位发生进位
        ans+="1";
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
//负数情况参考：http://blog.lsd365.com/cplusplus/w/16463.html
int main()
{
   return 0;
}
