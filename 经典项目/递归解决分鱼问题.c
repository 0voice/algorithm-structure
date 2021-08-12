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
