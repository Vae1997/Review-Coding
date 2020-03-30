#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s;
	//cin >> s;
	s="XYZABCDMMMGHIJKLRSTUVADEFG";
	//s="x";
	int len = s.length();
	if(len==1){
		cout<<s;
		return 0;
	}
	//记录连续字符数
	int count=1;
	//记录连续字符串末尾下标
	int end=0;
	//结果字符串
	string r="";
	int i;
	for (i = 0; i < len; i++)
	{
		if(i!=len-1)
		{
			cout<<"当前字符："<<s[i]<<" 与下一个字符："<<s[i+1];
			//当前字符连续			
			if(int(s[i+1])==int(s[i])+1)
			{
				count++;
				end=i+1;
				cout<<" 连续！数量："<<count<<",结尾下标："<<end<<endl;
			}else{
				cout<<" 不连续！count = "<<count<<endl;
				int start=i-count+1;
				cout<<"start:"<<start<<",end:"<<end<<endl;
				if(count<4){//不满足缩写要求，直接挨个输出
					for (int index = start; index <= end; index++)
					{
						r+=s[index];
					}
				}else//满足要求，简化输出
				{
					cout<<"count:"<<count<<endl;
					r+=s[start];
					r+="-";
					r+=s[end];
					cout<<"r:"<<r<<endl;
				}
				count=1;
				end=i+1;
			}
			//最后一次
			if(i+1==len-1)
			{
				int start=end-count+1;
				if(count<4)
				{
					for (int index = start; index <= end; index++)
					{
						r+=s[index];
					}
				}else{
					cout<<"count:"<<count<<endl;
					r+=s[start];
					r+="-";
					r+=s[end];
					cout<<"r:"<<r<<endl;
				}
				break;
			}
		}
	}
	cout<<r;
	return 0;
}
