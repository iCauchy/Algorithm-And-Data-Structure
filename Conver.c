#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<malloc.h>
#include<errno.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0
#define STACK_INIT_SIZE 100//内存空间初始分配量
#define STACKINCREMENT 10
typedef int ElemType;
typedef int Status;

typedef struct 
{		
	ElemType *base;
	ElemType *top;
	int stacksize;//当前已经分配的储存
}SqStack;

Status InitStack(SqStack *s);
Status GetTop(SqStack *S,ElemType *e);
Status Push(SqStack *S,ElemType e); 
Status Pop(SqStack *S,ElemType *e);
Status StackEmpty(SqStack *s);
Status Conversion10_2(int Dec);
Status Conversion2_8(int Bin);
Status Conversion2_16(int Bin);

Status InitStack (SqStack *S)
{
	S -> base = (ElemType *)malloc(STACK_INIT_SIZE *sizeof (ElemType));
	if(!S -> base)
	{
		return OVERFLOW;
	}
	S -> top = S -> base;
	S -> stacksize = STACK_INIT_SIZE;
	return OK;

}

Status GetTop(SqStack *S,ElemType *e)
{
	if (S -> top == S -> base)
	{
		return ERROR;//空栈情况
	}
	*e = *(S -> top - 1);
	return OK;
}

Status Push(SqStack *S,ElemType e)
{
	if(S->top - S->base >= S->stacksize)
	{
		S -> base = (ElemType *) realloc(S -> base,(S -> stacksize + STACKINCREMENT)*sizeof (ElemType));
		if(!S -> base)
		{
			return OVERFLOW;
		}
		S -> top = S -> base + S -> stacksize;
		S -> stacksize += STACKINCREMENT;
	}
	*S -> top++ = e;
	return OK;
}

Status Pop(SqStack *S,ElemType *e)
{
	if(S -> top == S -> base)
	{
		return ERROR;
	}
	S->top -= 1;
    *e = *(S->top);
    return OK;
}

Status StackEmpty(SqStack *S)
{
	if(S -> top == S ->base)
	{
		return 0;
	}
	return OK;
}

Status Conversion10_2(int Dec)
{
	long long m = 0;
	SqStack S;
	ElemType e;
	InitStack(&S);
	while (Dec)
	{
		Push(&S,(Dec % 2));
		//printf("H");
		Dec = Dec/2;
	}
	while (StackEmpty(&S))
	{
		Pop(&S,&e);
		//printf("%d",e);
		m = m*10 + e;
	}
	return m;
}

Status Conversion2_8(int Bin)
{
	SqStack S;
	ElemType e;
	InitStack(&S);
	while(Bin)
	{
		Push(&S,(Bin % 1000));
		Bin = Bin /1000;
	}
	printf("Otc is: ");
	while (StackEmpty(&S))
	{
		Pop(&S,&e);
		switch (e)
		{
			case 0 : printf("0");break;
			case 1 : printf("1");break;
			case 10 : printf("2");break;
			case 11 : printf("3");break;
			case 100 : printf("4");break;
			case 101 : printf("5");break;
			case 110 : printf("6");break;
			case 111 : printf("7");break;
		}
	}
	printf("\n");
}

Status Conversion2_16(int Bin)
{
	SqStack S;
	ElemType e;
	InitStack(&S);
	while(Bin)
	{
		Push(&S,(Bin % 10000));
		Bin = Bin /10000;
	}
	printf("Hex is: ");
	while (StackEmpty(&S))
	{
		Pop(&S,&e);
		switch (e)
		{
			case 0 : printf("0");break;
			case 1 : printf("1");break;
			case 10 : printf("2");break;
			case 11 : printf("3");break;
			case 100 : printf("4");break;
			case 101 : printf("5");break;
			case 110 : printf("6");break;
			case 111 : printf("7");break;
			case 1000: printf("8");break;
			case 1001: printf("9");break;
			case 1010: printf("A");break;
			case 1011 : printf("B");break;
			case 1100 : printf("C");break;
			case 1101 : printf("D");break;
			case 1110 : printf("E");break;
			case 1111 : printf("F");break;
		}
	}
	printf("\n");
}

int main()
{
	long long Bin = 0;
	int Dec = 10;
	printf("Please input a decimal number:\n");
	scanf("%d",& Dec);
 	Bin = Conversion10_2(Dec);
 	printf("Dec to Bin is:");
 	printf("%lld\n",Bin);
 	Conversion2_8(Bin);
 	Conversion2_16(Bin);
}
