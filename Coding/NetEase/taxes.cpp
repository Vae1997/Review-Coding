#include <iostream>
using namespace std;
#define BASE_MONEY 5000
const int level[7] = { 0, 3000, 12000, 25000, 35000, 55000, 80000 };
const float tax[7] = { 0.03, 0.1, 0.2, 0.25, 0.3, 0.35, 0.45 };
int main()
{
	char again = ' ';
	int money = 0;	
	while (true)
	{		
		cout << "输入月收入：";
		cin >> money;
		if (money <= BASE_MONEY)
		{
			cout << money << " <= " << BASE_MONEY << ",无需缴税" << endl;
		}
		else {
			cout << "除去基本工资：" << BASE_MONEY << endl;
			int partOfMoney = money - BASE_MONEY;
			cout << money << " - " << BASE_MONEY << " = " << partOfMoney << endl;
			float out = 0;
			for (int i = 1; ; i++)
			{
				//第一级或最后一级缴税
				if (partOfMoney <= level[i] || i > 6)
				{
					//cout << partOfMoney << " <= " << level[i] << endl;
					//去除之前的部分
					partOfMoney -= level[i - 1];
					cout << partOfMoney << " * " << tax[i - 1] << " = " << partOfMoney * tax[i - 1] << endl;
					//多余的部分加入缴税
					out += partOfMoney * tax[i - 1];
					break;
				}
				else {
					//中间的级别直接全额缴税
					cout << partOfMoney << " > " << level[i] << endl;
					cout << level[i] - level[i - 1] << " * " << tax[i-1] << " = " << (level[i] - level[i - 1]) * tax[i-1] << endl;
					out += (level[i] - level[i - 1]) * tax[i-1];
				}
			}		
			cout << "缴税总计：" << out << endl;
		}
		cout << "继续?(y/n):";
		cin >> again;
		if (again != 'y')break;
	}
	return 0;
}
