//自守数的定义，求解本题的关键是知道当前所求自然数的位数，以及该数平方的尾数与被乘数、乘数之间的关系。

//自守数是指一个数的平方的尾数等于该数自身的自然数。例如：
//  52 = 25    252 = 625    762 = 5776    93762 = 87909376
//求100000以内的自守数。


#include<stdio.h>
int main()
{
    long mul, number, k, a, b;
    printf("It exists following automorphic nmbers small than 100000:\n");
    for( number=0; number<100000; number++ )
    {
        for( mul=number, k=1; (mul/=10)>0; k*=10 );
        /*由number的位数确定截取数字进行乘法时的系数k*/
        a = k * 10;  /*a为截取部分积时的系数*/
        mul = 0;  /*积的最后n位*/
        b = 10;  /*b为截取乘数相应位时的系数*/
        while(k>0)
        {
            mul=( mul + ( number%(k*10) )*( number%b - number%(b/10) ) )%a;
            /*(部分积+截取被乘数的后N位*截取乘数的第M位)，%a再截取部分积*/
            k /= 10;  /*k为截取被乘数时的系数*/
            b *= 10;
        }
        if(number == mul)  /*判定若为自守数则输出*/
            printf("%ld   ", number);
    }
    printf("\n");
   
    return 0;
}

//运行结果：

//It exists following automorphic nmbers small than 100000:
//0   1   5   6   25   76   376   625   9376   90625
