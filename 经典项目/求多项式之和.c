/**
计算下列多项式的值：

S = 1 + 1/(1*2) + 1/(1*2*3) + ... + 1/(1*2*3* ... * 50)

从键盘上输入50后，输出为1.718282。
*/

#include<stdio.h>
int main()
{
    double s=0, t;  /*s记录多项式的和、t记录每一项分式的分母*/
    int i, n, j;  /*n控制项数*/
    printf("please input the number of n:");  /*输入n的值*/
    scanf("%d", &n);
    for(i=1; i<=n; i++)  /*i控制对应项数*/
    {
        t=1;  /*每次循环之前给t赋初值*/
        for(j=1; j<=i; j++)
            t = t * j;  /*求每一项的阶乘*/
        s = s + 1/t;
    }
    printf("%f\n", s);
   
    return 0;
}


//运行结果

//please input the number of n:50
//1.718282
