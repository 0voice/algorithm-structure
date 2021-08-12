//使用数组精确计算M/N(0<M<N<=100)的值。假如M/N是无限循环小数，则计算并输出它的第一循环节，同时要求输出循环节的起止位置（小数位的序号）。

#include<stdio.h>
int main()
{
    int m, n, i, j;
    int remainder[101]={0}, quotient[101]={0};
    /*remainder:存放除法的余数； quotient:依次存放商的每一位*/
    printf("Please input a fraction(m/n)(<0<m<n<=100):");
    scanf("%d/%d", &m, &n);  /*输入被除数和除数*/
    printf("%d/%d it's accuracy value is:0.", m, n);
    for(i=1; i<=100; i++)  /*i: 商的位数*/
    {
        remainder[m]=i;  /*m:得到的余数 remainder[m]:该余数对应的商的位数*/
        m*=10;  /*余数扩大10倍*/
        quotient[i]=m/n;  /*商*/
        m=m%n;  /*求余数*/
        if(m == 0)  /*余数为0 则表示是有限小数*/
        {
            for(j=1; j<=i; j++)
                printf("%d", quotient[j]);  /*输出商*/
            break;  /*退出循环*/
        }
        if(remainder[m]!=0)  /*若该余数对应的位在前面已经出现过*/
        {
            for(j=1; j<=i; j++)
                printf("%d", quotient[j]);  /*则输出循环小数*/
            printf("\n\tand it is a infinite cyclic fraction from %d\n", remainder[m]);
            printf("\tdigit to %d digit after decimal point.\n", i);  /*输出循环节的位置*/
            break;  /*退出循环*/
        }
    }
   
    return 0;
}


//运行结果：

//Please input a fraction(m/n)(<0<m<n<=100):1/6
//1/6 it's accuracy value is:0.16
//    and it is a infinite cyclic fraction from 2
//    digit to 2 digit after decimal point.
