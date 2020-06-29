/*
小Q想要给他的朋友发送一个神秘字符串，但是他发现字符串的过于长了，
于是小Q发明了一种压缩算法对字符串中重复的部分进行了压缩，
对于字符串中连续的m个相同字符串S将会压缩为[m|S](m为一个整数且1<=m<=100)，
例如字符串ABCABCABC将会被压缩为[3|ABC]，
现在小Q的同学收到了小Q发送过来的字符串，你能帮助他进行解压缩么？

输入描述:
输入第一行包含一个字符串s，代表压缩后的字符串。
S的长度<=1000;
S仅包含大写字母、[、]、|;
解压后的字符串长度不超过100000;
压缩递归层数不超过10层;

输出描述:
输出一个字符串，代表解压后的字符串。

示例1
输入
HG[3|B[2|CA]]F
输出
HGBCACABCACABCACAF
说明
HG[3|B[2|CA]]F−>HG[3|BCACA]F−>HGBCACABCACABCACAF
*/

#include <iostream>
#include <string>
using namespace std;
int main()
{
	string S;
	cin >> S;
	//S中已经没有]，说明已经解压完毕
	while (S.find_first_of(']') != -1)
	{
		//找到S中第一次出现]的位置
		int first_right_index = S.find_first_of(']');
		//截取第一个]之前的字符串
		string tmp_s = S.substr(0, first_right_index);
		//找到截取字符串的最后一个[和|的位置
		int last_left_index = tmp_s.find_last_of('[');
		int last_mid_index = tmp_s.find_last_of('|');
		//通过[和|的位置确定拷贝次数
		int copy_count = atoi(tmp_s.substr(last_left_index + 1, last_mid_index - (last_left_index + 1)).c_str());
		//通过|和]的位置确定要拷贝的字符串
		string copy_str = tmp_s.substr(last_mid_index + 1, first_right_index - (last_mid_index + 1));
		//循环得到将要替换的字符串
		string replace_str = "";
		for (int j = 0; j < copy_count; j++)
			replace_str += copy_str;
		//通过[和]的位置确定将要替换的范围
		int replace_count = first_right_index + 1 - last_left_index;
		//替换掉S中的字符串
		S = S.replace(last_left_index, replace_count, replace_str);
	}
	cout << S << endl;
	return 0;
}
