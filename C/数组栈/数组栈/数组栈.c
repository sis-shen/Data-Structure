#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_CAPACITY 4 //初始容量
#define MAX -1 // MAX<=0表示没有容量上限

typedef int DataType;//这里设置栈的数据类型

typedef struct Stack
{
	DataType* arr;
	int size;
	size_t capacity;
}Stack;

Stack* STInit(Stack* pst);
void STPush(Stack* pst, DataType x);//数据入栈/压栈
void STPop(Stack* pst);//数据出栈

int isEmpty(Stack* pst);//判空


Stack* STInit(Stack* pst)//注意这边的形参其实没啥用，不写也没关系，写了只是和别的接口统一形式罢了
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
		//进入if说明此栈有上限
		if (pst->size == MAX)
		{
			printf("栈上溢!\n");//这块怎么操作，自己改代码去
			exit(-1);//终止程序
		}
	}
	if (pst->size == pst->capacity)//二倍扩容
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
	assert(!isEmpty(pst));//不能为空
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
	pst = STInit(pst);//创建栈

	//****测试代码*********

	STPush(pst, 6);
	STPush(pst, 5);
	STPush(pst, 4);
	STPush(pst, 3);
	STPush(pst, 2);
	STPush(pst, 1);

	while (!isEmpty(pst))
	{
		printf("%d ", STTop(pst));//针对整型栈
		STPop(pst);
	}
	printf("\n");
	printf("capacity: %d", pst->capacity);
	return 0;
}