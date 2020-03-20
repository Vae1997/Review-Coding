#include <iostream>
#include <string>
using namespace std;

#define MAXSIZE 3
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;
//循环链表节点Node
typedef struct Node
{
	ElemType data;	//节点数据
	Node *next;	//下一个节点地址
};

//初始化链表(头节点存储节点数)
Node* initLinkList()
{
	Node *list = (Node *)malloc(sizeof(Node));
	list->data = MAXSIZE;//头节点存放链表长度
	list->next = list;	//循环链表
	for (int i = MAXSIZE; i >= 1; i--)
	{
		Node *newNode = (Node *)malloc(sizeof(Node));//头插法，初始化	
		//新节点指向头节点的下一个节点（第一个节点）
		newNode->next = list->next;
		newNode->data = i;
		//头节点指向新节点
		list->next = newNode;
	}
	return list;
}
//遍历
Status printLinkList(Node *list)
{
	int count = 0;
	Node *p = list;
	if (p->next == list)
	{
		cout << "链表为空:data = " << p->data << ",next = " << p->next << endl;
		return ERROR;
	}
	do
	{
		cout << "第" << count << "个节点的值为：" << p->data << "，其地址为：" << &p->data << endl;
		cout << "下一个节点的地址为：" << p->next << endl;
		//指针节点后移
		p = p->next;
		count++;
		//输出最后一个节点
		if (p->next == list)
		{
			cout << "第" << count << "个节点的值为：" << p->data << "，其地址为：" << &p->data << endl;
			cout << "下一个节点的地址为头节点"<<p->next<<",结束......" << endl;
			break;
		}
	} while (true);
	return OK;
}
//获取第i个节点的信息(data+next),包括第0个，头节点信息
Node* getNode(Node *list, int i)
{
	Node *node = (Node *)malloc(sizeof(Node));
	if (i < 0 || i > list->data)
	{
		cout << "获取第" << i << "个节点信息失败，i取值范围：1 ≤ i ≤ " << list->data << endl;
		return node;
	}
	if (list->next == list)
	{
		cout << "单链表为空，获取节点信息失败,返回空节点" << endl;
		return node;
	}
	int count = -1;
	Node *p = (Node *)malloc(sizeof(Node));
	p->next = list;
	while (count != i)
	{
		//赋值
		node->next = p->next;
		node->data = p->next->data;
		//指针节点后移
		p = p->next;
		count++;
	}
	node = p;
	cout << "查询第" << i << "个节点成功：data = " << node->data << ",&data = " << &node->data << endl;
	cout << "后继节点node.next = " << node->next << endl;		
	return node;
}
//在链表第i个节点前插入节点e
Status insertLinkList(Node *list, int i, Node *e)
{
	cout << "在链表第" << i << "个节点前插入节点" << e->data << endl;
	if (i < 1)
	{
		cout << "插入节点失败：i < 1" << endl;
		return ERROR;
	}
	if (list->next == list)
	{
		cout << "链表为空，初始化有" << MAXSIZE << "个节点的单链表......" << endl;
		list = initLinkList();
	}
	if (i > list->data)
	{
		cout << "第" << i << "个节点不存在,默认插入链表尾部......" << endl;
		i = list->data;
		Node * last_node = getNode(list, i);	//尾插法
		e->next = last_node->next;
		last_node->next = e;
		list->data++;	//链表长度++
		return OK;
	}
	Node * front_node = getNode(list, i - 1);	//头插法
	e->next = front_node->next;
	front_node->next = e;
	list->data++;	//链表长度++
	cout << "插入完毕......" << endl;
	return OK;
}
//删除第i个节点
Status delLinkList(Node *list, int i)
{
	if (i<1 || i > list->data)
	{
		cout << "删除的节点不存在" << endl;
		return ERROR;
	}
	Node *front_node = getNode(list, i - 1);
	//Node *back_node = getNode(list, i + 1);
	//第i个节点
	Node *node = front_node->next;
	//i-1节点指向i+1
	front_node->next = node->next;
	//释放第i个节点
	free(node);
	//节点个数--
	list->data--;
	return OK;
}
//清除链表
Status clearList(Node *list)
{
	int count = list->data;
	for (int i = 1; i <= count; i++)
	{
		//每次删除首个节点即可
		delLinkList(list, 1);
	}
	return OK;
}
//初始化具有尾指针的循环链表
Node* initLinkListWithRear(Node *rear)
{
	Node *list = (Node *)malloc(sizeof(Node));
	list->data = MAXSIZE;//头节点存放链表长度
	list->next = list;	//循环链表
	for (int i = MAXSIZE; i >= 1; i--)
	{
		Node *newNode = (Node *)malloc(sizeof(Node));//头插法，初始化	
		//新节点指向头节点的下一个节点（第一个节点）
		newNode->next = list->next;
		newNode->data = i;
		//头节点指向新节点
		list->next = newNode;
		if (i == MAXSIZE)
		{
			//尾指针指向最后一个元素
			rear->next = newNode;
		}
	}	
	return list;
}
//将B链表接入A
Status appendList(Node *rearA, Node *rearB)
{
	//A首（保存，用于B尾的连接）
	Node *A = rearA->next->next;
	//B首（保存，用于释放）
	Node *b = rearB->next->next;
	//获取B的长度,加入A
	rearA->next->next->data += rearB->next->next->data;
	//A尾->B头
	rearA->next->next = rearB->next->next->next;
	//B尾->A首
	rearB->next->next = A;	
	//释放B首
	free(b);
	return OK;
}
void main()
{
	Node *list = initLinkList();
	printLinkList(list);
	for (int i = 0; i <= list->data; i++)
	{
		getNode(list, i);
	}
	getNode(list, list->data + 1);
	for (int i = 1; i <= MAXSIZE; i++)
	{
		Node *e = (Node *)malloc(sizeof(Node));
		e->data = i;
		insertLinkList(list, i, e);
	}
	printLinkList(list);
	Node *e = (Node *)malloc(sizeof(Node));
	e->data = 888;
	insertLinkList(list, list->data + 1, e);
	printLinkList(list);
	cout << "删除节点" << endl;
	for (int i = 1; i < list->data; i++)
	{
		delLinkList(list, i);
	}
	cout << "打印：" << endl;
	printLinkList(list);
	cout << "清空链表......" << endl;
	clearList(list);
	cout << "打印：" << endl;
	printLinkList(list);
	cout << "---------------------------------------------------------" << endl;
	cout << "另一个初始化方法，初始化完成后尾指针指向链表最后一个元素......" << endl;
	Node *rearA = (Node *)malloc(sizeof(Node));
	Node *listA = initLinkListWithRear(rearA);
	printLinkList(listA);
	cout << "A尾指针指向链表尾部：" << rearA->next <<"，其值为："<< rearA->next->data<< endl;
	cout << "A链表首部地址：" << rearA->next->next << "，节点个数：" << rearA->next->next->data << endl;
	Node *rearB = (Node *)malloc(sizeof(Node));
	Node *listB = initLinkListWithRear(rearB);
	printLinkList(listB);
	cout << "B尾指针指向链表尾部：" << rearB->next << "，其值为：" << rearB->next->data << endl;
	cout << "B链表首部地址：" << rearB->next->next << "，节点个数：" << rearB->next->next->data << endl;
	cout << "A+B：" << endl;
	appendList(rearA, rearB);
	printLinkList(listA);
}
