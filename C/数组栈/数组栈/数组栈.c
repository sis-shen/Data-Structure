#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_CAPACITY 4 //��ʼ����
#define MAX -1 // MAX<=0��ʾû����������

typedef int DataType;//��������ջ����������

typedef struct Stack
{
	DataType* arr;
	int size;
	size_t capacity;
}Stack;

Stack* STInit(Stack* pst);
void STPush(Stack* pst, DataType x);//������ջ/ѹջ
void STPop(Stack* pst);//���ݳ�ջ

int isEmpty(Stack* pst);//�п�


Stack* STInit(Stack* pst)//ע����ߵ��β���ʵûɶ�ã���дҲû��ϵ��д��ֻ�Ǻͱ�Ľӿ�ͳһ��ʽ����
{

	Stack* st = (Stack*)malloc(sizeof(Stack));
	if (st == NULL)
	{
		perror("malloc failed\n");
		exit(-1);
	}
	pst = st;
	pst->size = 0;
	pst->capacity = INIT_CAPACITY;
	DataType* tmp = (DataType*)malloc(sizeof(DataType) * (pst->capacity));
	if (tmp == NULL)
	{
		perror("malloc failed\n");
		exit(-1);
	}

	pst->arr = tmp;

	return pst;
}

int isEmpty(Stack* pst)
{
	return pst->size == 0;
}

void STPush(Stack* pst, DataType x)
{
	if (MAX > 0)
	{
		//����if˵����ջ������
		if (pst->size == MAX)
		{
			printf("ջ����!\n");//�����ô�������Լ��Ĵ���ȥ
			exit(-1);//��ֹ����
		}
	}
	if (pst->size == pst->capacity)//��������
	{
		DataType* tmp = (DataType*)realloc(pst->arr,sizeof(DataType) * pst->capacity * 2);
		if (tmp == NULL)
		{
			perror("malloc failed\n");
			exit(-1);
		}
		pst->capacity *= 2;
	}

	pst->arr[pst->size] = x;
	pst->size++;
}

DataType STTop(Stack* pst)
{
	assert(!isEmpty(pst));//����Ϊ��
	return pst->arr[pst->size - 1];
}

void STPop(Stack* pst)
{
	assert(!isEmpty(pst));
	pst->size--;
}

int main()
{
	Stack* pst = NULL;
	pst = STInit(pst);//����ջ

	//****���Դ���*********

	STPush(pst, 6);
	STPush(pst, 5);
	STPush(pst, 4);
	STPush(pst, 3);
	STPush(pst, 2);
	STPush(pst, 1);

	while (!isEmpty(pst))
	{
		printf("%d ", STTop(pst));//�������ջ
		STPop(pst);
	}
	printf("\n");
	printf("capacity: %d", pst->capacity);
	return 0;
}