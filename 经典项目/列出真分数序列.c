//按递增顺序依次列出所有分母为40，分子小于40的最简分数。

#include<stdio.h>
int main()
{
    int i, num1, num2, temp, n=0;  /*n记录最简分数的个数*/
    printf("The fraction serials with demominator 40 is:\n");
    for(i=1; i<40; i++)  /*穷举40以内的全部分子*/
    {
        num1 = 40;
        num2 = i;
        /*采用辗转相除法求出最大公约数*/
        while(num2 != 0)
        {
            temp = num1 % num2;
            num1 = num2;
            num2 = temp;
        }
        if(num1 == 1)  /*若最大公约数为1，则为最简真分数*/
        {
            n++;
            printf("%2d/40  ", i);
            if(n%8 == 0)  /*每行输出8个数*/
                printf("\n");
        }
    }
   
    return 0;
}

//运行结果：

//The fraction serials with demominator 40 is:
// 1/40   3/40   7/40   9/40  11/40  13/40  17/40  19/40 
//21/40  23/40  27/40  29/40  31/40  33/40  37/40  39/40 
