//现输入一个真分数，请将该分数分解为埃及分数。

#include<stdio.h>
int main()
{
    long int a, b, c;
    printf("Please enter a optional fraction(a/b):");
    scanf("%ld/%ld", &a, &b);  /*输入分子a和分母b*/
    printf("It can be decomposed to:");
    while(1)
    {
        if(b%a)  /*若分子不能整除分母，则分解出一个分母为b/a+1的埃及分数*/
            c = b/a + 1;
        else  /*否则，输出化简后的真分数(埃及分数)*/
        {
            c = b / a;
            a = 1;
        }
        if(a==1)
        {
            printf("1/%ld\n", c);
            break;  /*a为1标志结束*/
        }
        else
            printf("1/%ld + ", c);
        a = a * c - b;  /*求出余数的分子*/
        b = b * c;  /*求出余数的分母*/
        if(a==3 && b%2==0)  /*若余数分子为3，分母为偶数，输出最后两个埃及分数*/
        {
            printf("1/%ld + 1/%ld\n", b/2, b); 
            break;
        }
    }
   
    return 0;
}

//运行结果：

//Please enter a optional fraction(a/b):8/11
//It can be decomposed to:1/2 + 1/5 + 1/55 + 1/110
