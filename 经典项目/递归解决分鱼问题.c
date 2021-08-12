/** 
A、B、C、D、E这5个人合伙夜间捕鱼，凌晨时都已经疲惫不堪，于是各自在河边的树丛中找地方睡着了。
第二天日上三竿时，A第一个醒来，他将鱼平分为5份，把多余的一条扔回河中，然后拿着自己的一份回家去了；
B第二个醒来，但不知道A已经拿走了一份鱼，于是他将剩下的鱼平分为5份，扔掉多余的一条，然后只拿走了自
己的一份；接着C、D、E依次醒来，也都按同样的办法分鱼。问这5人至少合伙捕到多少条鱼？每个人醒来后所看
到的鱼是多少条？ 
*/

#include<stdio.h>
/*分鱼递归函数*/
int fish(int n, int x)
{
    if((x-1)%5 == 0)
    {
        if(n==1)
            return 1;  /*递归出口*/
        else
            return fish(n-1, (x-1)/5*4);  /*递归调用*/
    }
    return 0;  /*x不是符合题意的解，返回0*/
}
int main()
{
    int fish[6], i;
    fish[5]=6;
    while(1)
    {
        for(i=4; i>0; i--)
        {
            if(fish[i+1]%4!=0)
                break;
            fish[i]=fish[i+1]*5/4+1;
            if(fish[i]%5!=1)
                break;
        }
        if(i == 0)
            break;
        fish[5]+=5;
    }
    for(i=1; i<=5; i++)
        printf("fish[%d]=%d\n", i, fish[i]);
    return 0;
}

//运行结果

//fish[1]=3121
//fish[2]=2496
//fish[3]=1996
//fish[4]=1596
//fish[5]=1276
