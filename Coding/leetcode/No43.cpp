//字符串相乘
#include<iostream>
#include<string>
#include<vector>
using namespace std;
//暴力解法，竖式
string multiply(string num1, string num2) {
    //单独排除0
    if(num1=="0"||num2=="0")return "0";
    int l1=num1.size();
    int l2=num2.size();
    int add=0;
    vector<int> res(l1+l2,0);//l1*l2结果最大l1+l2位
    for (int i = l1-1; i >= 0; i--)
    {
        for (int j = l2-1; j >= 0; j--)
        {
            int tmp=(num1[i]-'0')*(num2[j]-'0');//相乘结果
            int sum=tmp+res[i+j+1];//需加上一次的进位值res[i+j+1]
            res[i+j+1]=sum%10;
            res[i+j]+=sum/10;//新的进位值
        }
    }
    string ans;
    int i = 0;
    for (; i < res.size(); i++)
    {
        if(res[i]!=0)break;
    }
    for (; i < res.size(); i++)
    {
        ans+=to_string(res[i]);
    }
    return ans;
}
//结果相加
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
int main()
{
   
   return 0;
}
