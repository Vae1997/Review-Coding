#include<iostream>
#include<string>
using namespace std;
//将n进制字符串转换为十进制数
//n，base，r均参与运算，因此为long long类型
long long toDec(long long n, string s)
{
    long long r;
    long long base=n;
    int len=s.length();
    for (int i = len-1; i >= 0; i--)
    {
        long long num;
        if(s[i] >= 'A' && s[i] <= 'F')
        {
            num=s[i]-'A'+10;//A-F转为10-15
        }else{
            num=s[i]-'0';//数字字符转数字
        }
        if(i==len-1){
             r=num;//个位数字为零次，直接赋值
        }else{
            r+=num*n;//每一位数字*比例
            n*=base;//比例增加
        }
    }  
    return r;
}
long long identifyNum(int x, int y, string s)
{
    int len=s.length();
    //左右下标
    int i,j;
    i=0;j=len-1;
    //左右字符串
    string left,right;
    left+=s[i];
    right+=s[j];
    while(i<=j)
    {
        cout<<"i="<<i<<"j="<<j<<"left="<<left<<"right="<<right<<endl;
        long long l=toDec(x,left);
        long long r=toDec(y,right); 
        cout<<"l="<<l<<"r="<<r<<endl;       
        if(l==r && i+1==j){//检索结束
            return l;
        }else if(l!=r && i+1!=j){
            if(l<r){//左边值小，左边字串加一位
                i++;left+=s[i];
            }else{//右边值小，先保存当前字串，将新的一位赋值，再附加保存的（直接加会得到字串的逆序）
                j--;
                string tmp=right;
                right=s[j];
                right+=tmp;
            }
        }else if(l==r && i+1!=j){//虽然相等，但是检索未结束
            i++;j--;
            left+=s[i];
            string tmp=right;
            right=s[j];
            right+=tmp;
        }else{
            cout<<"字符串错误！"<<endl;
            return -1;
        }
    } 
}
int main()
{
    int X,Y;
    string Z;
    //X=2;Y=16;Z="1111\1111\1111\1111\1111\1111\1111\1111\FFFF\FFFF";
    X=2;Y=16;Z="11111111111111111111111111111111FFFFFFFF";
    cout << identifyNum(X, Y, Z) << endl;
    return 0;
}
