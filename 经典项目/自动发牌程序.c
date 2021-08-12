/**
一副扑克有52张牌，打桥牌时应将牌分给4个人。请设计一个程序完成自动发牌的工作。要求：
黑桃用S (Spaces)表示，红桃用H (Hearts)表示，方块用D (Diamonds)表示，梅花用C (Clubs)表示。
*/

#include<stdlib.h>
#include<stdio.h>
int comp(const void *j, const void *i);
void p(int b[], char n[]);
int main(void)
{
    static char n[]={'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    int a[53], b1[13], b2[13], b3[13], b4[13];
    int b11=0, b22=0, b33=0, b44=0, t=1, m, flag, i;
    while( t<=52 )  /*控制发52张牌*/
    {
        m=rand()%52;  /*产生0到51之间的随机数*/
        for(flag=1,i=1; i<=t&&flag; i++)  /*查找新产生的随机数是否已经存在*/
            if(m==a[i])
                flag=0;  /*flag=1表示产生的是新的随机数，flag=0表示新产
                          生的随机数已经存在*/
        if(flag)
        {
            a[t++]=m;  /*如果产生了新的随机数，则存入数组*/
            /*根据t的模值，判断当前的牌应存入哪个数组中*/
            if(t%4==0)
                b1[b11++]=a[t-1];
            else
                if(t%4==1)
                    b2[b22++]=a[t-1];
                else
                    if(t%4==2)
                        b3[b33++]=a[t-1];
                    else
                        if(t%4==3)
                            b4[b44++]=a[t-1];
        }
    }
    qsort(b1, 13, sizeof(int), comp);  /*将每个人的牌进行排序*/
    qsort(b2, 13, sizeof(int), comp);
    qsort(b3, 13, sizeof(int), comp);
    qsort(b4, 13, sizeof(int), comp);
    p(b1, n);  /*分别打印每个人的牌*/
    p(b2, n);
    p(b3, n);
    p(b4, n);
    return 0;
}

void p(int b[], char n[])
{
    int i;
    printf("\n\006 ");  /*打印黑桃标记*/
    for(i=0; i<13; i++)  /*将数组中的值转换为相应的花色*/
        if(b[i]/13==0)  /*找到该花色对应的牌*/
            printf("%c ", n[b[i]%13]);
    printf("\n\003 ");  /*打印红桃标记*/
    for(i=0; i<13; i++)
        if((b[i]/13)==1)
            printf("%c ", n[b[i]%13]);
    printf("\n\004 ");  /*打印方块标记*/
    for(i=0; i<13; i++)
        if(b[i]/13==2)
            printf("%c ", n[b[i]%13]);
                printf("\n\005 ");  /*打印梅花标记*/
                for(i=0; i<13; i++)
                    if(b[i]/13==3 || b[i]/13==4)
                        printf("%c ", n[b[i]%13]);
    printf("\n");
}

int comp(const void *j, const void *i)  /*qsort调用的排序函数*/
{
    return(*(int*)i-*(int*)j);
}

//运行结果：

/**
 7 6 4 3
 9 5 4 3
 A
 K Q 8 4

 Q T 2
 8
 8 7 5 4
 A T 9 7 3

 K J
 A Q J T 7
 K J 3 2
 5 2

 A 9 8 5
 K 6 2
 Q T 9 6
 J 6
*/
