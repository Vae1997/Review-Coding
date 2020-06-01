//https://leetcode-cn.com/problems/find-common-characters/
//查找常用字符
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
vector<string> commonChars(vector<string>& A) {
    int L=A.size();
    int j;
    string c,s;
    char cc;
    vector<string> ss;
    while (A[0].length()>0)//用A[0]中的字符判断
    {
        c=A[0][0];//当前字符
        for (j = 1; j < L; j++)//挨个find
        {
            if(A[j].length()==0)return ss;
            s=A[j];//当前串
            size_t p=s.find(c);
            if(p==string::npos)break;//当前串没有c，直接break
            else A[j].erase(A[j].begin()+p);//有c，删除字符c，避免多个重复字符
        }
        if(j==L)
        {
            ss.push_back(c);//说明所有s都有c，将c存入结果
            A[0].erase(A[0].begin());
        }
        //否则，则删除A[0]中所有的c字符，避免重复判断
        else
        {
            cc=A[0][0];
            A[0].erase(remove(A[0].begin(),A[0].end(),cc),A[0].end());
        }
    }
    return ss;
}
//参考解法：
/*
建立一个二维数组，行数是输入单词的个数（最大100），列数是26个英文字母。
记下来每个单词中每个字母出现的次数，然后直接在这个二维数组上进行比较，
保证第一行是该字母在所有单词中出现的最小次数。
最后输出即可

作者：lvmingzhe
链接：https://leetcode-cn.com/problems/find-common-characters/solution/cjian-dan-zhi-guan-jie-fa-yong-shi-ji-bai-96-kong-/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
vector<string> commonChars(vector<string>& A) {
    vector<string> s;
    int num[100][26]={0};                  
    for(int i =0;i<A.size() ;i++)
        for(int j=0;j<A[i].size();j++)
            num[i][(A[i][j]-'a')]++;//字符-'a'转换为对应下标
    
    for(int j=0;j<26;j++)                  
        for(int i=1;i<A.size();i++)//将最小的字母数放在第0行
            num[0][j] = min (num[0][j],num[i][j]);
                
    string c;                          
    for(int i=0;i<26;i++){
        while(num[0][i]--)
        {
            c=(char)('a'+i);//下标+'a'转换为对应字母
            s.push_back(c);
        }
    }
    return s;
}
int main()
{
    return 0;
}
