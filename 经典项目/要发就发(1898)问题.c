/**
“1898—要发就发”。请将不超过1993的所有素数从小到大排成第一行，第二行上的每个数都等于它上面相邻两个素数之差。
编程求出：第二行数中是否存在若干个连续的整数，它们的和恰好为1898？假如存在的话，又有几种这样的情况？

两行数据分别如下：
第一行：2  3  5  7  11  13  17......1979  1987  1993
第二行：1  2  2  4   2   4......8  6
*/


#include<stdio.h>
#include<math.h>

#define NUM 320

int number[NUM];  /*存放不超过1993的全部素数*/
int fun(int i);

int main()
{
    int i, j, count=0;
    printf("列出第一行中差值为1989的所有素数组合:\n");
    for(j=0, i=3; i<=1993; i+=2)  /*求出不超过1993的全部素数*/
        if( fun(i) )
            number[j++]=i;
    for(j--; number[j]>1898; j--)  /*从最大的素数开始向1898搜索*/
    {
        for(i=0; number[j]-number[i]>1898; i++);  /*循环查找满足条件的素数*/
        if(number[j]-number[i] == 1898)  /*若两个素数的差为1898，则输出*/
            printf("(%d).%3d,%d\n", ++count, number[i], number[j]);
    }
   
    return 0;
}

int fun(int i)
{
    int j;
    if( i<=1 )
        return 0;  /*判断是否为素数，为1是素数，为0不是素数*/
    if( i==2 )
        return 1;
    if( !(i%2) )
        return 0;  /*if no, return 0*/
    for(j=3; j<=(int)(sqrt((double)i)+1); j+=2)
        if( !(i%j) ) return 0;
    return 1;
}


//运行结果：

//列出第一行中差值为1989的所有素数组合:
//(1). 89,1987
//(2). 53,1951
(3).  3,1901
