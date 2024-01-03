#define  _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int DataType; //这里改链表的数据类型

typedef struct Node
{
	DataType val;
	struct Node* next;
	struct Node* prev;
}Node;


Node* InitNode(Node* phead);//初始化
void PushFront(Node* phead, DataType x);//头插
void PushBack(Node* phead, DataType x);//尾插
void PopFront(Node* phead);//头删
void PopBack(Node* phead);//尾删
void DestroyList(Node* phead);//删除链表

int FindNode(Node* phead, DataType x);//找到第一个值为x的节点，返回其下标,规定哨兵位为0，往后依次加一,所以找不到就返回0
void InsertNode(Node* phead, DataType x, int pos);//使新插入的节点下标为 pos
void EraseNode(Node* phead, int pos);//删除下标为pos的节点


Node* InitNode(Node* phead)
{
	//创建哨兵位
	Node* ret = (Node*)malloc(sizeof(Node));
	//ret->val  //哨兵位的值不作处理
	ret->next = ret;
	ret->prev = ret;
	ret->val = INT_MAX;
}

Node* BuyNode(DataType x)
{
	Node* ret = (Node*)malloc(sizeof(Node));
	ret->val = x;
	ret->next = NULL;
	ret->prev = NULL;
}

void PushFront(Node* phead, DataType x)
{
	assert(phead);
	Node* newNode = BuyNode(x);
	Node* next = phead->next;

	next->prev = newNode;
	newNode->next = next;
	newNode->prev = phead;
	phead->next = newNode;
}

void PushBack(Node* phead, DataType x)
{
	assert(phead);
	Node* newNode = BuyNode(x);
	Node* tail = phead->prev;

	phead->prev = newNode;
	newNode->next = phead;
	tail->next = newNode;
	newNode->prev = tail;

}

void PopFront(Node* phead)
{
	assert(phead);
	Node* front = phead->next;
	assert(front != phead);
	phead->next = front->next;
	front->prev = phead;

	free(front);
}

void PopBack(Node* phead)
{
	assert(phead);
	Node* tail = phead->prev;

	assert(tail != phead);

	tail->prev->next = phead;
	phead->prev = tail->prev;

	free(tail);
}

void DestroyList(Node* phead)
{
	assert(phead);
	Node* cur = phead->next;
	while (cur != phead)
	{
		Node* next = cur->next;
		free(cur);
		cur = next;
	}
	free(phead);
}

int FindNode(Node* phead, DataType x)
{
	assert(phead);
	int cnt = 0;
	Node* cur = phead->next;
	while (cur != phead)
	{
		cnt++;
		if (cur->val == x)
		{
			return cnt;
		}
		else
		{
			cur = cur->next;
		}
	}

	return 0;
}

void InsertNode(Node* phead, DataType x, int pos)
{
	assert(pos > 0);
	assert(phead);
	Node* nNode = BuyNode(x);
	Node* cur = phead;
	while (pos-1)
	{
		cur = cur->next;
		if (cur == phead)
		{
			printf("插入失败，请检查程序\n");
			return;
		}
		pos--;
	}

	Node* next = cur->next;
	cur->next = nNode;
	nNode->prev = cur;
	nNode->next = next;
	next->prev = nNode;
}

void EraseNode(Node* phead, int pos)
{
	assert(pos > 0);
	assert(phead->next != phead);
	Node* cur = phead;
	while (pos - 1)
	{
		cur = cur->next;
		if (cur == phead)
		{
			printf("插入失败，请检查程序\n");
			return;
		}
		pos--;
	}

	Node* next = cur->next;
	cur->next = next->next;
	next->next->prev = cur;

	free(next);
}

void PrintList_int(Node* phead)//打印整型链表
{
	assert(phead);
	Node* cur = phead->next;
	while (cur != phead)
	{
		printf("%d->", cur->val);
		cur = cur->next;
	}
	printf("NULL\n");
}

int main()
{
	Node* phead = NULL;
	phead = InitNode(phead);//使用前记得初始化

	//******以下为测试********
	PushFront(phead, 1);
	PushFront(phead, 2);

	int pos = FindNode(phead, 1);
	InsertNode(phead, 233, pos);

	PrintList_int(phead);

	PushBack(phead, 3);
	PushBack(phead, 4);

	EraseNode(phead, 2);

	PrintList_int(phead);

	PopBack(phead);

	PrintList_int(phead);

	PopFront(phead);

	PrintList_int(phead);

	DestroyList(phead);
	phead = NULL;

	return 0;
}