#include <iostream>
#include <string>
using namespace std;

#define MAXSIZE 10		//最大容量
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;		//返回状态码
typedef char ElemType;	//存储的数据类型
//静态链表节点Component
typedef struct Component
{
	ElemType data;
	int cur;			//下一节点的下标
};
//初始化(创建备用链表)
Status initStaticLinkList(Component *list)
{
	//list[MAXSIZE - 1].cur指向链表第一个元素的下标，为0表示空链表
	//list[0].cur指向剩余空间（备用链表）的第一个下标，为0表示链表满
	list[MAXSIZE - 1].cur = 0;
	for (int i = 0; i < MAXSIZE - 1; i++)
	{
		//初始化的静态链表类似顺序表，可用空间是连续的，当前位置指向紧接着的下一个位置
		list[i].cur = i + 1;	
	}
	list[0].data = 'X';
	list[MAXSIZE - 1].data = 'X';
	return OK;
}
//获取链表有效元素个数
int getLength(Component *list)
{
	if (list[MAXSIZE - 1].cur == 0)
	{
		//cout << "链表为空，获取链表有效元素个数: 0" << endl;
		return 0;
	}
	else {
		int count = 0;
		//链表首个元素
		int i = list[MAXSIZE - 1].cur;
		//cur为0表示链表尾部元素
		while (i)
		{
			//下一个元素
			i = list[i].cur;
			count++;
		}
		return count;
	}
}
//遍历
Status printList(Component *list)
{
	if (list[MAXSIZE - 1].cur == 0)
	{
		cout << "链表为空，遍历初始化的链表！" << endl;
		for (int i = 0; i < MAXSIZE; i++)
		{
			cout << "数组下标：" << i << "，值：" << list[i].data << ",下一个位置的下标：" << list[i].cur << endl;
		}
	}
	else {
		int index = list[MAXSIZE - 1].cur;
		int count = 1;
		while (count<=getLength(list))
		{
			cout << "链表第" << count << "个节点的下标：" << index << "，值：" << list[index].data << "，下一个节点的下标：" << list[index].cur << endl;
			index = list[index].cur;
			count++;
		}		
	}
	return OK;
}
//分配空间
int mallocSpace(Component *list)
{
	//获取备用链表的首个节点下标,list[0].cur为0表示整个数组已无可用空间，即getLength(list)==MAXIZE-2
	int index = list[0].cur;
	if (list[0].cur)
	{
		//要分配的下标的cur作为新的剩余空间（备用链表）的第一个下标
		list[0].cur = list[index].cur;
	}
	return index;
}
//获取链表第i个位置的元素，返回data+cur
Component getElem(Component *list, int i)
{	
	Component node;
	if (getLength(list) == 0)
	{
		cout << "链表为空！获取链表第" << i << "个位置的元素失败！"<< endl;
	}
	if (i > getLength(list) || i < 1)
	{
		cout << "获取链表第" << i << "个位置的元素失败！可获取的位置i范围：1 ≤ i ≤ " << getLength(list) << endl;		
	}
	else
	{
		//确定开始节点，遍历完成，顺藤摸瓜，找到链表的第i个位置的元素
		int index = list[MAXSIZE - 1].cur;
		
		//遍历i次，找到第i个节点
		for (int count = 1; count <= i; count++)
		{
			
			if (count == i)
			{
				//当前index即为第i个节点，赋值
				node.data = list[index].data;
				//遍历完毕，index即为第i个节点的cur
				node.cur = list[index].cur;
				break;
			}
			//确定下一节点的index
			index = list[index].cur;
		}		
	}
	return node;
}
//根据节点的cur得到节点在数组的位置
int locateByCur(Component *list, int cur)
{
	int i;
	for (i = 1; i <= MAXSIZE-2 ; i++)
	{
		if (list[i].cur == cur)break;
	}
	return i;
}
//在链表第i个位置插入新元素e
Status insertStaticLinkList(Component *list,int i,ElemType e)
{
	//链表已满
	if (getLength(list) == MAXSIZE - 2)
	{
		cout << "链表已满！插入元素失败！" << endl;
		list[0].cur = 0;
		return ERROR;
	}
	//链表为空,默认插入list[1]
	if (getLength(list) == 0)
	{
		cout << "链表为空！默认插入list[1]......" << endl;
		//分配list[1]
		int index = mallocSpace(list);
		list[index].data = e;	//赋值
		list[MAXSIZE - 1].cur = index;	//链表首节点下标从0改为1
		//list[1].cur初始化是2，需修改为0，表示链表尾部
		list[index].cur = 0;
		//list[0].cur在malloc内已经修改为2		
	}
	//插入的位置在链表有效长度之外,getLength(list)+1表示在链表尾部插入
	else if (i < 1 || i > getLength(list)+1)
	{
		cout << "在链表第" << i << "个位置插入元素失败！插入范围：1 ≤ i ≤ " << getLength(list) << endl;
		return ERROR;
	}
	//首位插入(单独作为一种情况，避免getElem(i-1)得到list[0])
	else if (i == 1)
	{
		//获取备用链表首个下标
		int index = mallocSpace(list);
		//新空间赋值新元素
		list[index].data = e;
		//新空间指向原先的首个元素下标
		list[index].cur = list[MAXSIZE - 1].cur;				
		//首个元素下标指向新空间
		list[MAXSIZE - 1].cur = index;
	}
	else//包括在队尾插入和在中间插入
	{	
		//得到第i-1个元素
		Component node = getElem(list, i - 1);
		int index = mallocSpace(list);
		list[index].data = e;
		//表示在链表中间插入
		if (node.cur != 0)
		{
			//指向第i-1个元素原先指向的元素
			list[index].cur = node.cur;			
		}
		else {//队尾插入
			//新节点为最后一个节点
			list[index].cur = 0;
		}
		//第i-1个元素指向新分配的下标
		//注意node只是一个临时存储节点信息的变量，所以不能直接修改node.cur
		//node.cur = index;
		//需要找到node在整个list的下标i，然后list[i].cur =index
		int i = locateByCur(list, node.cur);
		list[i].cur = index;
	}
	return OK;
}
//释放数组下标为index的空间
Status freeSpace(Component *list, int index)
{
	//删除位置指向删除之前的备用链表首位
	list[index].cur = list[0].cur;
	//修改备用链表首位为删除的位置
	list[0].cur = index;
	return OK;
}
//删除链表第i个位置的元素
Status delElem(Component *list, int i)
{
	if (getLength(list) == 0)
	{
		cout << "空链表无法删除元素！" << endl;
		return ERROR;
	}
	if (i<1 || i>getLength(list))
	{
		cout << "删除位置非法！" << endl;
		return ERROR;
	}
	//删除之前的首个元素下标
	int index = list[MAXSIZE - 1].cur;
	//i=1时不进入循环，index还是首个元素下标
	for (int count = 2; count <= i-1; count++)
	{
		//找到链表第i-1个元素的下标
		index = list[index].cur;
	}
	if (i == 1)
	{
		//删除链表头，直接将首个元素指向第二个元素
		list[MAXSIZE - 1].cur = list[index].cur;
		//根据首个元素的cur找到其下标，并释放
		int locate = locateByCur(list, list[index].cur);
		freeSpace(list, locate);
		return OK;
	}
	else if (i == getLength(list)) {
		//释放第i个的位置
		freeSpace(list, list[index].cur);
		//删除链表尾，直接将i-1指向0
		list[index].cur = 0;
		return OK;		
	}
	else {
		//将i-1的cur赋值为i-1.cur(i).cur(i+1)
		int front = list[index].cur;
		list[index].cur = list[front].cur;
		//释放i
		freeSpace(list, front);
		return OK;
	}		
}
void main()
{
	Component list[MAXSIZE];
	initStaticLinkList(list);
	printList(list);
	cout << "插入第1个元素（空插）" << endl;
	insertStaticLinkList(list, 8, 'A');
	printList(list);
	cout << "在第1个位置插入第2个元素（首插）" << endl;
	insertStaticLinkList(list, 1, 'B');
	printList(list);
	cout << "在位置2插入第3个元素（间插）" << endl;
	insertStaticLinkList(list, 2, 'C');
	printList(list);
	cout << "在位置4插入第4个元素（尾插）" << endl;
	insertStaticLinkList(list, 4, 'D');
	printList(list);
	cout << "在位置3插入第5个元素" << endl;
	insertStaticLinkList(list, 3, 'E');
	printList(list);
	cout << "删除位置1的元素（首删）" << endl;
	delElem(list, 1);
	printList(list);
	cout << "删除位置4的元素（尾删）" << endl;
	delElem(list, 4);
	printList(list);
	cout << "删除位置2的元素（间删）" << endl;
	delElem(list, 2);
	printList(list);
	int tag;
	int pos;
	char e,ok;
	int end = 1;
	while (end)
	{
		cout << "插入(0),删除(1):";
		cin >> tag;
		switch (tag)
		{
		case 0:
			cout << "输入插入位置：" << endl;
			cin >> pos;
			cout << "输入插入字符：" << endl;
			cin >> e;
			insertStaticLinkList(list, pos, e);
			printList(list);
			break;
		case 1:
			cout << "输入删除位置：" << endl;
			cin >> pos;
			delElem(list, pos);
		default:
			printList(list);			
		}
		cout << "是否继续？(y/n):" << endl;
		cin >> ok;
		if (ok != 'y')
		{
			break;
		}
	}
}
