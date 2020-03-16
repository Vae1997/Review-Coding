#include <iostream>
#include <string>
using namespace std;

#define MAXSIZE 20		//最大容量
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;		//返回状态码
typedef int ElemType;	//存储的数据类型
//线性表顺序存储结构
typedef struct SqList
{
	ElemType data[MAXSIZE];
	int length;			//线性表长度
};
//输出线性表
Status displayList(SqList * list)
{
	if (list->length < 0 || list->length > MAXSIZE) 
	{
		cout << "输出失败：list->length < 0 || list->length > MAXSIZE" << endl;
		return ERROR;
	}
	for (int i = 0; i < list->length; i++)
	{
		cout << "data：" << list->data[i] << ",address：" << &list->data[i] << endl;
	}
	return OK;
}
//初始化线性表
SqList * initList()
{
	//malloc返回的是void*类型
	SqList * list = (SqList *)malloc(sizeof(SqList));	
	//初始化为0
	for (int i = 0; i < MAXSIZE; i++)
	{
		list->data[i] = 0;
	}
	list->length = MAXSIZE;
	return list;
}
//线性表是否为空
Status isEmpty(SqList * list)
{
	return list->length == 0 ? TRUE : FALSE;
}
//清空线性表
Status clearList(SqList * list)
{
	if (list->length == 0)
	{
		cout << "线性表为空，不需要清空......" << endl;
		return OK;
	}
	else {
		list->length = 0;
		cout << "线性表长度已经置为0......" << endl;
		return OK;
	}
}
//在线性表的第i个位置插入元素e
Status insertList(SqList * list, int i, ElemType e)
{
	//插入位置无效
	if (i<1 || i>MAXSIZE)
	{
		cout << "插入失败：i<1 || i>MAXSIZE" << endl;
		return ERROR;
	}
	//无法插入
	if (list->length == MAXSIZE) {
		cout << "插入失败：list->length == MAXSIZE" << endl;
		return ERROR;
	}
	cout << "在第" << i << "个位置插入元素：" << e << endl;
	//从第i个位置后移
	for (int index = list->length - 1; index >= i-1; index--)
	{
		list->data[index + 1] = list->data[index];
	}
	//赋值
	list->data[i - 1] = e;
	//表长+1
	list->length++;
	return OK;
}
//删除第i个位置的元素
Status delList(SqList * list, int i)
{
	//删除位置无效
	if (i<1 || i>MAXSIZE)
	{
		cout << "删除失败：i<1 || i>MAXSIZE" << endl;
		return ERROR;
	}
	//无法删除
	if (list->length == 0) {
		cout << "删除失败：list->length == 0" << endl;
		return ERROR;
	}
	cout << "删除第" << i << "个位置的元素：" << list->data[i - 1] << endl;
	//后继元素前移
	for (int index = i; index < list->length; index++)
	{
		list->data[index - 1] = list->data[index];
	}
	list->length--;
	return OK;
}
//返回第i个位置的元素值
ElemType getElem(SqList * list, int i)
{
	//查询位置无效
	if (i<1 || i>MAXSIZE)
	{
		cout << "查询失败：i<1 || i>MAXSIZE" << endl;
		return ERROR;
	}
	//无法查询
	if (list->length == 0) {
		cout << "查询失败：list->length == 0" << endl;
		return ERROR;
	}
	cout << "第" << i << "个位置的元素为：" << list->data[i - 1] << endl;
	return list->data[i - 1];
}
//查找元素e，返回下标
Status findElem(SqList * list, ElemType e)
{
	for (int i = 0; i < list->length; i++)
	{
		if (list->data[i] == e)
		{
			cout << "元素" << e << "在线性表第" << i + 1 << "个位置" << endl;
			return i;
		}
	}
	cout << "元素" << e << "不存在...." << endl;
	return ERROR;
}
void main() {
	cout << "初始化SqList......" << endl;
	cout << "sizeof(ElemType):" << sizeof(ElemType) << endl;
	cout << "sizeof(SqList):" << sizeof(SqList) << endl;
	SqList * list = initList();
	cout << "初始化完成,结果如下：" << endl;
	cout << "sizeof(list->data):" << sizeof(list->data) << endl;
	cout << "list->length:" << list->length << endl;
	displayList(list);
	cout << "清空线性表......" << endl;
	clearList(list);
	cout << "IsEmpty:" << isEmpty(list) << endl;
	cout << "插入......" << endl;
	for (int i = 0; i < 10; i++)
	{
		insertList(list, 1 + i, i + 1);
	}
	cout << "插入结果：" << displayList(list) << endl;
	for (int i = 0; i < 10; i++)
	{
		findElem(list, i + 1);
	}
	for (int i = 0; i < 10; i++)
	{
		getElem(list, i + 1);
	}
	cout << "删除......" << endl;
	for (int i = 10; i > 1; i--)
	{
		delList(list, i);
	}
	cout << "删除结果：" << displayList(list) << endl;
	cout << "清空线性表......" << endl;
	clearList(list);
	cout << "IsEmpty:" << isEmpty(list) << endl;
}
