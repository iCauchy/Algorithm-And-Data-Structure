#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int Status ;
typedef int ElemType  ;
typedef struct
{
	ElemType  *elem ;
	int length ;
	int listSize ;
}SqList;

Status InitList_Sq( SqList *L) ;
Status DestroyList_Sq(SqList *L) ;
Status ClearList_Sq(SqList *L) ;
Status Merge_Sq(SqList *LA,SqList *LB,SqList *LC);
Status ListEmpty_Sq(const SqList  *L) ;
int ListLength_Sq(const SqList *L) ;
Status GetElem_Sq(const SqList *L , int i , ElemType  *e );
Status compare_e0( const ElemType * e1 ,const ElemType  * e2 ) ;
int LocateElem_Sq(const SqList *L , const ElemType  *e , Status (*compare)(const ElemType  *, const ElemType  *));
Status PriorElem_Sq(const SqList *L , const ElemType   *cur_e, ElemType  *pre_e  );
Status NextElem_Sq(const SqList *L , const ElemType   *cur_e, ElemType  *next_e  );
Status ListInsert_Sq( SqList *L , int i ,const ElemType   *e) ;
Status ListDelete_Sq( SqList *L , int i , ElemType  *e) ;
Status outElem(const ElemType  *e) ;
Status ListTraverse_Sq(const SqList *L , Status (*pvisit)(const ElemType  * ) );
Status CreateList_Sq(SqList *L);
int main( int argc , char *argv[] )
{
	SqList LA;
	SqList LB;
	SqList LC;
	InitList_Sq(&LA);
	InitList_Sq(&LB);
	InitList_Sq(&LC);
	CreateList_Sq(&LA);
	CreateList_Sq(&LB);
	//CreateList_Sq(&LC);
	printf("test_value_of_length\n");
	Merge_Sq(&LA,&LB,&LC);
	//ListTraverse_Sq(&LA,outElem);
	//ListTraverse_Sq(&LB,outElem);
	ListTraverse_Sq(&LC,outElem);
	return OK ;
}
Status CreateList_Sq( SqList *L )
{   ElemType *p = NULL;
	ElemType *q = NULL; 
	ElemType k;
	InitList_Sq(L);
    printf("Input Length Of Elems:\n");
    scanf("%d",&k);
    L->length = k;
    q = L->elem + L->length;
    printf("Input The Elem ,Press ENTER When Finish An Elem:\n");
    for(p = L -> elem;p < q;p++)
    {   
		scanf("%d",p);
    }
	return OK ;
}

Status Merge_Sq(SqList *LA,SqList *LB,SqList *LC)
{
	if(LA -> length + LB -> length > LC -> listSize)
	{
		return ERROR;	
	}
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < LA ->length && j < LB -> length)
	{
		if (LA -> elem[i] <= LB -> elem[j])
		{
			LC ->elem[k++] = LA -> elem[i++];
		}
		
		else
		{
			LC -> elem[k++] = LB -> elem[j++];
		}
		
	}
	
	while(i < LA -> length)
	{
		LC -> elem[k++] = LA -> elem[i++];
		
	}
	while(j <LB -> length)
	{
		LC -> elem[k++] = LB -> elem[j++];

	}
	
	//printf("i = %d,j = %d,k = %d\n",i,j,k);
	LC ->length = k;
	
	return OK;
}
Status InitList_Sq(SqList *L)
{
	L->elem = (ElemType *) malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L->elem)
	{
		exit( OVERFLOW );
	}
	memset( L->elem , 0x00,  LIST_INIT_SIZE*sizeof(ElemType ) ) ;
	L->length = 0 ;
	L->listSize = LIST_INIT_SIZE ;

	return OK;
}

Status DestroyList_Sq(SqList *L)
{
	if( L->elem )
		{
			free(L->elem);
			L->listSize = 0 ;
			L->length   = 0 ;
		}
	else
		{
			return ERROR;
		}

	return OK;
}

Status ClearList_Sq(SqList *L) 
{
	if(L->elem)
		{
			memset(L->elem,0x00,L->listSize);
			L->length = 0;  
		}
	else
		{
			return ERROR;
		}

	return OK;
}

Status ListEmpty_Sq(const SqList  *L)
{
	if( L->length == 0 )
		{
			return TRUE ;
		}
	else
		{
			return FALSE;
		}
}

int ListLength_Sq(const SqList *L)
{
	return L->length ;
}

Status GetElem_Sq(const SqList *L , int i , ElemType  *e )
{
	if( i < 1 || i > L->length )
		{
			return ERROR;
		}

	*e = L->elem[ i - 1 ];

	return OK;
}

Status compare_e0( const ElemType * e1 ,const ElemType  * e2 )
{
	int flags = 0 ;
	if( *e1 == *e2)
		{
			flags = 0 ;
		}
	if( *e1 > *e2 )
		{
			flags = 1 ;
		}
	if( *e1 < *e2 )
		{
			flags = -1 ;
		}
	return flags ;
}

int LocateElem_Sq(const SqList *L , const ElemType  *e , Status (*compare)(const ElemType  *, const ElemType  *))
{
	int i = 0 ;
	int flags = 0 ;
	ElemType *p = NULL ;

	for( i = 0 ,p = L->elem ; i < L->length ; i++ )
		{
			if( !(*compare)(p++ , e) )
				{
					flags = 0 ;
					break;
				}
			else
				{
					flags = 1 ;
				}
		}

	if( flags == 1 )
		{
			return 0 ;
		}
	else
		{
			return i + 1 ;
		}

}

Status PriorElem_Sq(const SqList *L , const ElemType *cur_e, ElemType  *pre_e  )
{
	int i = 0 ;

	if( !L->elem )
		{
			return ERROR ;
		}

	if( ( i = LocateElem_Sq(L,cur_e,compare_e0) ) == 1 || i == 0 )
		{
			pre_e = NULL ;
			return FALSE;
		}
	else
		{
			*pre_e = L->elem[ i - 1 ] ;
			return OK;
		}
}

Status NextElem_Sq(const SqList *L , const ElemType   *cur_e, ElemType  *next_e  )
{
	int i = 0 ;

	if( !L->elem )
		{
			return ERROR ;
		}
	if( ( i = LocateElem_Sq(L,cur_e,compare_e0) ) == ListLength_Sq(L) || i == 0 )
		{
			next_e = NULL ;
			return FALSE;
		}
	else
		{
			*next_e = L->elem[ i + 1 ] ;
			return OK;
		}
}

Status ListInsert_Sq ( SqList *L , int i , const ElemType  *e)
{
	ElemType  *newbase = NULL ;
	ElemType  *p = NULL ;
	ElemType  *q = NULL ;

	if( !L->elem )
		{
			fprintf(stderr,"List is not exists!Please initialize list first!\n");
			return ERROR ;
		}

	if( i < 1 || i > L->length + 1 )
		{
			fprintf(stderr,"ERROR:Insert Failed!\t Note: No >= 1 and No < %d!\n", L->length + 1);
			return ERROR ;
		}

	if(L->length >= L->listSize )
		{
			newbase = ( ElemType  *)realloc( L->elem ,(L->listSize + LISTINCREMENT)*sizeof(ElemType ) );
			if( !newbase )
				{
					exit(OVERFLOW);
				}
			L->elem = newbase ;
			L->listSize += LISTINCREMENT ;
		}

	q = L->elem + i - 1 ;  /* q = &L->elem[i-1] */
	for( p = L->elem + L->length - 1   ; p >= q ; p-- )
		{
			*(p + 1) = *p ;
		}

	*p = *e ;
	++L->length ;

	return OK;
}

Status ListDelete_Sq( SqList *L , int i , ElemType  *e)
{
	int length = 0 ;
	ElemType *p = NULL ;
	ElemType *q = NULL ;

	if( !L->elem || !L->length)
		{
			return ERROR ;
		}

	if( i < 1 || i > L->length )
		{
			return ERROR ;
		}

	p = L->elem + i - 1 ;
	*e = *p ;

	for( q = L->elem + L->length - 1 ; p  <= q ; p++ )
		{
			*p = *( p + 1 ) ;
		}

	--L->length;

	return OK;
}

Status ListTraverse_Sq(const SqList *L , Status (*pvisit)(const ElemType  * ) )
{
	ElemType  *p = NULL ;
	ElemType  *q  = L->elem + L->length ;

	for(p = L->elem ; p < q ; p++ )
		{
			( *pvisit)( p );
		}
	return OK;
}

Status outElem(const ElemType  *e)
{
	printf("%d\n",*e);
	return OK ;
}


