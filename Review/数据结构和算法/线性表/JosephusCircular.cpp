#include <iostream>
using namespace std;
typedef struct Node
{
	int id;
	Node *next;
};
Node* initList(int s)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->id = 1;
	node->next = node;//循环链表
	for (int i = s; i >= 2; i--)
	{
		Node *newnode = (Node *)malloc(sizeof(Node));
		newnode->id = i;
		newnode->next = node->next;
		node->next = newnode;
	}
	return node;
}
int getLength(Node *list)
{
	int count = 1;
	Node *p = list;
	while (p->next != list)
	{
		count++;
		p = p->next;
	}
	return count;
}
void print(Node *list)
{
	Node *p = list;	
	for (int i = 1; i < getLength(list); i++)
	{
		cout << p->id << "->";
		p = p->next;
	}
	cout << p->id << endl;
}
void printFromK(Node *list, int k)
{
	Node *p = list;
	for (int i = 1; i < getLength(list)+k-1; i++)
	{
		//从1循环到k时不输出
		if (i < k)
		{
			p = p->next;
			continue;
		}
		else {
			cout << p->id << "->";
			p = p->next;			
		}
	}
	cout << p->id << endl;
}
//如果删除首节点，则需创建新list保存返回结果
Node* delElem(Node *list, int i)
{
	Node *p = (Node *)malloc(sizeof(Node));
	p->next = list;
	bool one = false;
	if (i == 1)
	{
		//删除第一个元素，则需修改链表头节点
		i = getLength(list) + 1;
		one = true;
	}
	for (int pos = 1; pos <= i - 1; pos++)
	{
		p = p->next;
	}
	Node *q = p->next;
	p->next = p->next->next;
	if (one)
	{
		list = q->next;//修改链表头节点
	}
	cout << "删除的节点值为：" << q->id << endl;
	free(q);
	return list;
}
//链表实际地址先后顺序没变，只是交换节点存储的data即可
void exchangeLinkDataByK(Node *list, int k)
{
	Node *p = list;
	int size = k - 1;
	int *data = new int[size];
	//循环寻找具体需要的data
	for (int i = 1; i <= getLength(list) + k-1; i++)
	{
		//从1循环到k时,保存数值
		if (i < k)
		{
			data[i - 1] = p->id;
			p = p->next;
			continue;
		}
		else if(i <= getLength(list)){//从第K个元素开始赋值
			list->id = p->id;
			p = p->next;
			list = list->next;			
		}
		else {//剩余部分使用保存的数据赋值
			for (int k = 0; k < size; k++)
			{
				list->id = data[k];
				list = list->next;
			}
			break;
		}
	}
}
void main()
{
	char ok;
	while (true)
	{
		cout << "输入链表初始长度S：" << endl;
		int s;
		cin >> s;
		if (s < 1)
		{
			cout << "输入非法！" << endl;
			return;
		}
		Node *list = initList(s);
		print(list);
		cout << "输入起始节点号K，删除节点号M:" << endl;
		int k, m;
		cin >> k >> m;
		if (k < 1 || k > getLength(list) || m < 1 || m > getLength(list))
		{
			cout << "输入非法！" << endl;
			return;
		}
		if (m == 1)//第一个人就退出，则直接从K开始遍历的顺序即为退出顺序
		{
			printFromK(list, k);
		}
		else {
			//要退出的编号>当前链表长度则结束，剩余人存活
			while (m <= getLength(list))
			{
				cout << "修改之前：";
				print(list);
				//修改第K个节点为链表首节点
				exchangeLinkDataByK(list, k);
				cout << "修改完成：";
				print(list);
				//删除新链表第m个元素
				delElem(list, m);
				cout << "删除完成：";
				print(list);
				//第m+1个节点作为新链表首节点
				k = m;
			}
		}		
		cout << "是否继续？(y/n):" << endl;
		cin >> ok;
		if (ok != 'y')
		{
			break;
		}
	}	
}
