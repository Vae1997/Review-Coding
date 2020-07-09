//通配符匹配
#include<iostream>
using namespace std;
/*
如果s和p中字符匹配，则分别自增i和j
否则如果p中当前字符为星号，则标记iStar和jStar，同时自增j
否则如果iStar >= 0，表示之前匹配过星号，因为星号可以匹配任意字符串，所以继续递增i，同时移动j为jStar下一个字符
否则返回false

作者：guohaoding
链接：https://leetcode-cn.com/problems/wildcard-matching/solution/44-tong-pei-fu-pi-pei-shuang-zhi-zhen-by-guohaodin/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
bool isMatch(string s, string p) {
    int i,j,i_star,j_star;
    i=j=0;
    i_star=j_star=-1;
    int s_l=s.length();
    int p_l=p.length();
    while (i<s_l)
    {
        if(j<p_l && (s[i]==p[j] || p[j]=='?'))//s和p中字符匹配，则分别自增i和j
        {
            i++;
            j++;
        }
        else if(j<p_l && p[j]=='*')//p中当前字符为星号，则标记iStar和jStar，同时自增j
        {
            i_star=i;
            j_star=j;
            j++;
        }
        else if(i_star>-1)//之前匹配过星号
        {
            i_star++;
            i=i_star;
            j=j_star+1;
        }
        else return false;
    }
    while (j<p_l && p[j]=='*')
    {
        j++;
    }
    return j==p_l;
}
int main()
{
   return 0;
}
