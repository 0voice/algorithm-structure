/* 这里实现的是最小堆 */

#include "binheap.h"
#include "fatal.h"
#include <stdlib.h>

#define MinPQSize (10) // 堆最小的尺寸
#define MinData (-32767)

// 堆的结构
struct HeapStruct
{
    int Capacity; // 代表最大值
    int Size; // 当前的堆大小
    ElementType *Elements; // 数组
};

/* START: fig6_0.txt */
/**
 * 初始化堆
 * @param MaxElements 最大的容量
 * @return 指向最大堆的指针
 */
PriorityQueue
Initialize( int MaxElements )
{
            PriorityQueue H;

/* 1*/      if( MaxElements < MinPQSize )
/* 2*/          Error( "Priority queue size is too small" );

/* 3*/      H = malloc( sizeof( struct HeapStruct ) );
/* 4*/      if( H ==NULL )
/* 5*/          FatalError( "Out of space!!!" );

    /* Allocate the array plus one extra for sentinel */
/* 6*/      H->Elements = malloc( ( MaxElements + 1 )
                                  * sizeof( ElementType ) ); // 给数组分配空间
/* 7*/      if( H->Elements == NULL )
/* 8*/          FatalError( "Out of space!!!" );

/* 9*/      H->Capacity = MaxElements; // H 的容量
/*10*/      H->Size = 0; // 当前的堆大小
/*11*/      H->Elements[ 0 ] = MinData;

/*12*/      return H;
}
/* END */

void
MakeEmpty( PriorityQueue H )
{
    H->Size = 0;
}

/* START: fig6_8.txt */
/* H->Element[ 0 ] is a sentinel */
/**
 * 插入操作
 * @param X 待插入的元素
 * @param H 要插入的目标堆
 */
void
Insert( ElementType X, PriorityQueue H )
{
    int i;

    if( IsFull( H ) )
    {
        Error( "Priority queue is full" );
        return;
    }

    // 上滤(percolate up)，如果父节点比 X 大，就将其给滤下来
    for( i = ++H->Size; H->Elements[ i / 2 ] > X; i /= 2 )
        H->Elements[ i ] = H->Elements[ i / 2 ];
    H->Elements[ i ] = X; // 最后剩下的位置就是 X 应该插入的位置
}
/* END */


/* START: fig6_12.txt */
/**
 * 删除最小元
 * @param H
 * @return 返回最小元
 */
ElementType
DeleteMin( PriorityQueue H )
{
            int i, Child;
            ElementType MinElement, LastElement;

/* 1*/      if( IsEmpty( H ) )
            {
/* 2*/          Error( "Priority queue is empty" );
/* 3*/          return H->Elements[ 0 ];
            }
/* 4*/      MinElement = H->Elements[ 1 ]; // 根节点即最小元
/* 5*/      LastElement = H->Elements[ H->Size-- ]; // 取出最后一个元素，用于插入到删除最小元之后的根节点处，然后下滤

/* 6*/      for( i = 1; i * 2 <= H->Size; i = Child )
            {
                /* Find smaller child */
/* 7*/          Child = i * 2;
/* 8*/          if( Child != H->Size && H->Elements[ Child + 1 ]
/* 9*/                                < H->Elements[ Child ] )
/*10*/              Child++;

                /* Percolate one level 下滤操作 */
/*11*/          if( LastElement > H->Elements[ Child ] )
/*12*/              H->Elements[ i ] = H->Elements[ Child ];
                else
/*13*/              break;
            }
/*14*/      H->Elements[ i ] = LastElement;
/*15*/      return MinElement;
}
/* END */

/**
 * 查找最小元，即取出根节点存储的元素
 * @param H
 * @return
 */
ElementType
FindMin( PriorityQueue H )
{
    if( !IsEmpty( H ) )
        return H->Elements[ 1 ];
    Error( "Priority Queue is Empty" );
    return H->Elements[ 0 ];
}

/**
 * 判断堆是否为空
 * @param H
 * @return
 */
int
IsEmpty( PriorityQueue H )
{
    return H->Size == 0;
}

/**
 * 判断堆是否已满
 * @param H
 * @return
 */
int
IsFull( PriorityQueue H )
{
    return H->Size == H->Capacity;
}

/**
 * 销毁堆
 * @param H
 */
void
Destroy( PriorityQueue H )
{
    free( H->Elements );
    free( H );
}

#if 0
/* START: fig6_14.txt */
        for( i = N / 2; i > 0; i-- )
            PercolateDown( i );
/* END */
#endif
