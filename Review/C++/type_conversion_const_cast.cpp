//const_cast类型转换详细说明
//很少用
//用于删除 const、volatile 和 __unaligned 特性（如将 const int 类型转换为 int 类型 ）
//例子额外参考：https://www.cnblogs.com/ider/archive/2011/07/22/cpp_cast_operator_part2.html
#include<iostream>
using namespace std;
void Printer (int* val)
{
	cout<<*val<<endl;
}
int main()
{
    const int n = 100;
    int *p = const_cast<int*>(&n);
    //n++;const不可修改
    cout<<&n<<" "<<p<<endl;//注意地址一样
    *p = 234;//非const，修改值
    cout<<"n = "<<n<<endl;//const n在编译期间改为100，因此依然为100
    cout<<"*p = "<<*p<<endl;
    cout<<"----------"<<endl;
    int variable = 21;//注意这里，非const
	const int* const_p = &variable;//使用const指向
	int* modifier = const_cast<int*>(const_p);//只能得到const_p指针时，使用const_cast
	*modifier = 7;//进行调整
	cout << "variable:" << variable << endl;	
	const int consatant = 20;
	//Printer(consatant);//Error: invalid conversion from 'int' to 'int*'
    //确定Printer方法不会修改参数时，才可以使用
	Printer(const_cast<int *>(&consatant));
    return 0;
}
