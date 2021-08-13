//编写一个计算个人所得税的程序，要求输入收入金额后，能够输出应缴的个人所得税。 个人所得税征收办法如下：
//◎ 起征点为3500元；
//◎ 不超过1500元的部分，征收3%；
//◎ 超过1500〜4500元的部分，征收10%；
//◎ 超过4500〜9000元的部分，征收20%；
//◎ 超过9000〜35000元的部分，征收25%；
//◎ 超过35000〜55000元的部分，征收30%；
//◎ 超过55000〜80000元的部分，征收35%；
//◎ 超过80000元以上的，征收45%。


#include <stdio.h>
#include <limits.h>
#define TAXBASE  2000
/*定义结构体*/
typedef struct
{
    long start;
    long end;
    double taxrate;
}TAXTABLE;

TAXTABLE TaxTable[] = {
    {0, 1500, 0.03},
    {1500, 4500, 0.10},
    {4500, 9000, 0.20},
    {9000, 35000, 0.25},
    {35000, 55000, 0.30},
    {55000, 80000, 0.35},
    {80000, LONG_MAX, 0.45}
};

double CaculateTax(long profit)
{
    int i;
    double tax = 0.0;
    profit -= TAXBASE;
    for(i=0; i<sizeof(TaxTable)/sizeof(TAXTABLE); i++)
    {
        if(profit>TaxTable[i].start)
        {
            if(profit>TaxTable[i].end)
            {
                tax += (TaxTable[i].end-TaxTable[i].start) * TaxTable[i].taxrate;
            }
            else
            {
                tax += (profit-TaxTable[i].start) * TaxTable[i].taxrate;
            }
            profit -= TaxTable[i].end;
            printf("征税范围：%6ld~%6ld  该范围内缴税金额：%6.2f  超出该范围的金额：%6ld\n",
                   TaxTable[i].start, TaxTable[i].end,tax, (profit)>0 ? profit:0);
        }
    }
    return tax;
}
int main()
{
    long profit;
    double tax;
    printf("请输入个人收入金额: ");
    scanf("%ld", &profit);
    tax = CaculateTax(profit);
    printf("您的个人所得税为: %.2f\n", tax);
   
    return 0;
}


//运行结果：

//请输入个人收入金额: 100000
//征税范围：     0~  1500  该范围内缴税金额： 45.00  超出该范围的金额： 96500
//征税范围：  1500~  4500  该范围内缴税金额：345.00  超出该范围的金额： 92000
//征税范围：  4500~  9000  该范围内缴税金额：1245.00  超出该范围的金额： 83000
//征税范围：  9000~ 35000  该范围内缴税金额：7745.00  超出该范围的金额： 48000
//征税范围： 35000~ 55000  该范围内缴税金额：11645.00  超出该范围的金额：     0
//您的个人所得税为: 11645.00
