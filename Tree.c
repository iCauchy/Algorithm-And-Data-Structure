/*By Cauchy
PreOrderTravese
InOrderTravese
PostOrderTravese
LevelTravese
of Tree
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<malloc.h>
#include<errno.h>
#define TURE 1
#define FALSE 0
#define OVERFLOW -1
#define OK 1
#define ERROR 0 
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status;
typedef char ElemType;

typedef struct TreeNode
{
	ElemType data;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
}TreeNode,*BiTree;

typedef BiTree SElemType;

typedef struct 
{		
	SElemType *base;
	SElemType *top;
	int stacksize;//当前已经分配的储存
}SqStack;
int TreeDepth(BiTree T);
Status Print(ElemType e);
Status CreatBiTree(BiTree *T);
Status InitStack (SqStack *S);
Status GetTop(SqStack *S,SElemType *e);
Status Push(SqStack *S,SElemType e);
Status Pop(SqStack *S,SElemType *e);
Status StackEmpty(SqStack *S);
Status PreOrderTraverse(BiTree *T,Status (*Visit)(ElemType e));
Status InOrderTraverse(BiTree T,Status(*Visit)(ElemType e));
Status PostOrderTraverse(BiTree *T,Status (*Visit)(ElemType e));
Status LevelTraverse(BiTree T,int depth);
Status PrintTreeLevel(BiTree T,int level);
int main()
{
	int depth = 0;//树的深
	BiTree Tree = NULL;
	printf("Input some chars ,End with #:\n");
	CreatBiTree(&Tree);
	depth = TreeDepth(Tree);
	printf("The PreOrder is :\n");
	PreOrderTraverse(&Tree,Print);
	printf("\nThe InOrder is :\n");
	InOrderTraverse(Tree,Print);
	printf("\nThe PostOrder is :\n");
	PostOrderTraverse(&Tree,Print);
	printf("\nLevel Traverse is : \n");
	LevelTraverse(Tree,depth);
	printf("\n");
}

Status InitStack (SqStack *S)
{
	S -> base = (SElemType *)malloc(STACK_INIT_SIZE *sizeof (SElemType));
	if(!S -> base)
	{
		return OVERFLOW;
	}
	S -> top = S -> base;
	S -> stacksize = STACK_INIT_SIZE;
	return OK;

}

Status GetTop(SqStack *S,SElemType *e)
{
	if (S -> top == S -> base)
	{
		return ERROR;//空栈情况
	}
	*e = *(S -> top - 1);
	return OK;
}

Status Push(SqStack *S,SElemType e)
{
	if(S->top - S->base >= S->stacksize)
	{
		S -> base = (SElemType *) realloc(S -> base,(S -> stacksize + STACKINCREMENT)*sizeof (SElemType));
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

Status Pop(SqStack *S,SElemType *e)
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


Status CreatBiTree(BiTree *T)
{
	ElemType ch;
	scanf("%c",&ch);
	getchar();
	if(ch == '#')
	{
		*T = NULL;
		//printf("NULL\n");
	}
		else
		{
			if(!(*T = (TreeNode *)malloc(sizeof (TreeNode))))
			{
				exit(OVERFLOW);
			}
			(*T) -> data = ch;
			//printf("%c\n",(*T) -> data);
			CreatBiTree(&((*T) -> lchild));
			CreatBiTree(&((*T) -> rchild));
		}
	return OK;
}

Status PreOrderTraverse(BiTree *T,Status (*Visit)(ElemType e))
{
	if(*T)
	{
		if(Visit((*T) -> data))
		{
			if(PreOrderTraverse(&((*T) -> lchild),Print))
			{
				if(PreOrderTraverse(&((*T) -> rchild),Print))
				{
					return OK;
				}
				return ERROR;
			}
		}
	}
	else
	{
		return OK;
	}
}
/*
Status InOrderTraverse(BiTree T,Status(*Visit)(ElemType e))
{
   SqStack S;
   InitStack(&S);
   BiTree p = T;
   Push(&S,T);
   while(StackEmpty(&S))
   {
       while(GetTop(&S,&p)&&p)
       {
           p = p -> lchild;
           Push(&S,p);
       }
       Pop(&S,&p);
       if(StackEmpty(&S))
       {
           Pop(&S,&p);
           if(!Visit(p -> data))
            return ERROR;
           Push(&S,p -> rchild);
       }

   }
   return OK;
}*/
//另外一种实现方式//
Status InOrderTraverse(BiTree T,Status (*Visit)(ElemType e))
{
	SqStack S;
	InitStack(&S);
	BiTree p = T;
	while(p||StackEmpty(&S))
	{
		if(p)
		{
			Push(&S,p);
			p = p -> lchild;
		}
		
		else
		{
			Pop(&S,&p);
			if(!Visit(p -> data))
			return ERROR;
			p = p -> rchild;
		}
	}
	return OK;
	
}

Status Print(ElemType e)
{
	printf("%c",e);
	return OK;
}
Status PostOrderTraverse(BiTree *T,Status (*Visit)(ElemType e))
{
	if(*T)
	{
		if(PostOrderTraverse(&((*T) -> lchild),Print))
		{
			if(PostOrderTraverse(&((*T) -> rchild),Print))
			{
				if(Visit((*T) -> data))
				{
					return OK;
				}
				return ERROR;
			}
		}
	}
	else
	{
		return OK;
	}
}
int TreeDepth(BiTree T)
{
	int lchilddep,rchilddep;
	if (T == NULL) 
	{
		return(0);
	}                            
	else
	{    
		lchilddep = TreeDepth(T -> lchild);   
		rchilddep = TreeDepth(T -> rchild); 
		return (lchilddep>rchilddep)? (lchilddep+1):(rchilddep+1);
	}
}

Status PrintTreeLevel(BiTree T,int level)
{
	if(T == NULL||level < 1)
	{
		return 0;
	}
	if(level == 1) 
	{
		Print(T -> data);
		return OK;
	}
	PrintTreeLevel(T -> lchild,level -1);
	PrintTreeLevel(T -> rchild,level -1);
}

Status LevelTraverse(BiTree T,int depth)
{
	//printf("%d",depth); 
	int i = 0;//控制循环
	if(T == NULL)
	{
		//printf("ERROR");
		return ERROR;
	}
	for(i = 1;i <= depth;i++)
	{
		//printf("Test in Lev_Trave");
		PrintTreeLevel(T,i);
	}
	return OK;
}

