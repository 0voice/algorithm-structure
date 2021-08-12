/**
编程求三位数中的“黑洞数”。

黑洞数又称陷阱数，任何一个数字不全相同的整数，经有限次“重排求差”操作，总会得到某一个或一些数，这些数即为黑洞数。
“重排求差”操作是将组成一个数的各位数字重排得到的最大数减去最小数，
例如207，“重排求差”操作序列是720-027=693，963-369=594，954-459=495，再做下去就不变了，再用208算一次，也停止到495，
所以495是三位黑洞数。
*/


#include <stdio.h>
int maxof3(int, int, int);
int minof3(int, int, int);
int main()
{
    int i, k;
    int hun, oct, data, max, min, j, h;
    printf("请输入一个三位数：");
    scanf("%d", &i);
    hun=i/100;
    oct=i%100/10;
    data=i%10;
    max=maxof3(hun, oct, data);
    min=minof3(hun, oct, data);
    j=max-min;
    for(k=0; ; k++)  /*k控制循环次数*/
    {
        h=j;  /*h记录上一次最大值与最小值的差*/
        hun=j/100;
        oct=j%100/10;
        data=j%10;
        max=maxof3(hun, oct, data);
        min=minof3(hun, oct, data);
        j=max-min;
        if(j==h)  /*最后两次差相等时，差即为所求黑洞数*/
        {
            printf("%d\n", j);
            break;  /*跳出循环*/
        }
    }
    return 0;
}
/*求三位数重排后的最大数*/
int maxof3(int a,int b,int c)
{
    int t;
    if(a<b)  /*如果a<b，将变量a、b的值互换*/
    {
        t=a;
        a=b;
        b=t;
    }
    if(a<c)
    {
        t=a;
        a=c;
        c=t;
    }
    if(b<c)
    {
        t=b;
        b=c;
        c=t;
    }
    return(a*100+b*10+c);
}
/*求三位数重排后的最小数*/
int minof3(int a, int b, int c)
{
    int t;
    if(a<b)
    {
        t=a;
        a=b;
        b=t;
    }
    if(a<c)
    {
        t=a;
        a=c;
        c=t;
    }
    if(b<c)
    {
        t=b;
        b=c;
        c=t;
    }
    return(c*100+b*10+a);
}


//运行结果：

//请输入一个三位数：207
//495
