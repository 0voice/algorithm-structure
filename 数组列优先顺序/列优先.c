/**
* @brief C语言 数组 列优先 实现
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#define OK 1
#define ERROR -1

#define MAX_DIM 8       ///允许的最大数组维数

typedef int ElemType;

typedef struct
{
    ElemType *base;         ///数组元素基址
    int dim;                ///数组维数
    int *bounds;            ///数组维界基址
    int *constants;         ///数组映像函数常量基址
}Array;     ///数组结构

///数组方法声明
int InitArray( Array *pArr, int nDim, ... );        ///初始化数组 pArr
void DestroyArray( Array *pArr );                   ///销毁数组 pArr
int Locate( Array *pArr, int nDim, va_list ap );                     ///定位下标指向的元素在数组中的位置
int Assign( Array *pArr, ElemType *elm, ... );      ///数组赋值
int Value( Array *pArr, ElemType *elm, ... );       ///数组取值

///数组方法实现

/**
* @brief 初始化数组
*
* @param pArr 指向待初始化的数组
* @param nDim 数组的维数
* @param ... 数组各维数的长度
*
* @return 初始化成功返回OK, 否则返回ERROR
*/
int InitArray( Array *pArr, int nDim, ... )
{
    if( nDim < 1 || nDim > MAX_DIM )
        return ERROR;

    ///初始化 pArr 数组维数属性
    pArr->dim = nDim;

    ///构造数组维界基址
    pArr->bounds = (int *)malloc( nDim * sizeof(int) );
    if( !pArr->bounds )
        return ERROR;

    int i = 0, nElemCount = 1;
    va_list ap;
    va_start( ap, nDim );

    /// i = nDim - 1, 使列优先
    for( i = nDim - 1; i >= 0; --i )
    {
        pArr->bounds[i] = va_arg( ap, int );
        if( pArr->bounds[i] < 0 )
            return ERROR;

        nElemCount *= pArr->bounds[i];
    }
    va_end(ap);

    ///初始化元素基址
    pArr->base = (ElemType *)malloc( nElemCount * sizeof(ElemType) );
    if( !pArr->base )
        return ERROR;

    ///初始化函数映像常数基址
    pArr->constants = (int *)malloc( nDim * sizeof(int) );

    ///递推求常量基址, 列优先
    pArr->constants[nDim-1] = 1;
    for( i = nDim -2 ; i >= 0; --i )
    {
        pArr->constants[i] = pArr->bounds[i+1] * pArr->constants[i+1];
    }

    return OK;
}

/**
* @brief 销毁数组 pArr
*
* @param pArr 指向待销毁的数组
*/
void DestroyArray( Array *pArr )
{
    if( pArr->base )
        free( pArr->base );

    if( pArr->bounds )
        free( pArr->bounds );

    if( pArr->constants )
        free( pArr->constants );
}

/**
* @brief 定位数组下标指向的元素在数组中的位置
*
* @param 指向的数组
* @param ... 数组的下标
*
* @return 若下标合法, 返回下标在数组中的位置, 否则返回 ERROR
*/
int Locate( Array *pArr, int nDim, va_list ap )
{
    int nPos = 0, ind = 0, i = 0;

    ///列优先求地址
    for( i = pArr->dim - 1; i >= 0; --i )
    {
        ind = va_arg( ap, int );

        ///使用断言, 确保下标合法
        assert( ind >= 0 && ind < pArr->bounds[i] );

        nPos += pArr->constants[i] * ind;
    }
    va_end(ap);

    return nPos;
}

/**
* @brief 数组赋值
*
* @param pArr 指向待赋值的数组
* @param elm 指向赋值元素
* @param nDim 数组维数
* @param ... 数组下标
*
* @param 赋值成功返回 OK, 否则返回 ERROR
*/
int Assign( Array *pArr, ElemType *elm, ... )
{
    int nPos = 0;
    va_list ap;
    va_start( ap, elm );
    nPos = Locate( pArr, pArr->dim, ap );
    *(pArr->base + nPos) = *elm;

    return OK;
}

/**
* @brief 数组取值

*/
int Value( Array *pArr, ElemType *elm, ... )
{
    int nPos = 0;
    va_list ap;
    va_start( ap, elm );
    nPos = Locate( pArr, pArr->dim, ap );
    *elm = *(pArr->base + nPos);
    printf( "addr = 0x%X\n", pArr->base + nPos );

    return OK;
}

int main()
{
    Array arr;

    ///初始化一个三维数组, 大小为 2x3x5
    InitArray( &arr, 3, 2, 3, 5 );

    int a = 0;
    ///赋值测试
    int i = 0, m = 0, n = 0;
    for( i = 0; i < 2; ++i )
        for( m = 0; m < 3; ++m )
            for( n = 0; n < 5; ++n )
            {
                a = i + m + n;
                Assign( &arr, &a, i, m, n );
            }

    int b = 0;
    ///取值测试
    for( i = 0; i < 2; ++i )
        for( m = 0; m < 3; ++m )
            for( n = 0; n < 5; ++n )
            {
                 Value( &arr, &b, i, m, n );
                 printf( "[%d][%d][%d]=%d\n", i, m, n, b );
            }

    ///销毁数组
    DestroyArray( &arr );

    return 0;
}
