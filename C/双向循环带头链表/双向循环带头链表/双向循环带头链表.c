#define  _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int DataType; //�������������������

typedef struct Node
{
	DataType val;
	struct Node* next;
	struct Node* prev;
}Node;


Node* InitNode(Node* phead);//��ʼ��
void PushFront(Node* phead, DataType x);//ͷ��
void PushBack(Node* phead, DataType x);//β��
void PopFront(Node* phead);//ͷɾ
void PopBack(Node* phead);//βɾ
void DestroyList(Node* phead);//ɾ������

int FindNode(Node* phead, DataType x);//�ҵ���һ��ֵΪx�Ľڵ㣬�������±�,�涨�ڱ�λΪ0���������μ�һ,�����Ҳ����ͷ���0
void InsertNode(Node* phead, DataType x, int pos);//ʹ�²���Ľڵ��±�Ϊ pos
void EraseNode(Node* phead, int pos);//ɾ���±�Ϊpos�Ľڵ�


Node* InitNode(Node* phead)
{
	//�����ڱ�λ
	Node* ret = (Node*)malloc(sizeof(Node));
	//ret->val  //�ڱ�λ��ֵ��������
	ret->next = ret;
	ret->prev = ret;
	ret->val = INT_MAX;
	return ret;
}

Node* BuyNode(DataType x)
{
	Node* ret = (Node*)malloc(sizeof(Node));
	ret->val = x;
	ret->next = NULL;
	ret->prev = NULL;
	return ret;
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
			printf("����ʧ�ܣ��������\n");
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
			printf("����ʧ�ܣ��������\n");
			return;
		}
		pos--;
	}

	Node* next = cur->next;
	cur->next = next->next;
	next->next->prev = cur;

	free(next);
}

void PrintList_int(Node* phead)//��ӡ��������
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
	phead = InitNode(phead);//ʹ��ǰ�ǵó�ʼ��

	//******����Ϊ����********
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