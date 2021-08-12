//2000以内的不小于4的正偶数都能够分解为两个素数之和（即验证歌德巴赫猜想对2000以内的正偶数成立）。

#include<math.h>
#include<stdio.h>
int fun(int n)
{
    int i;
    if(n==2)
        return 1;  /*n是2，返回1*/
    if(n%2==0)
        return 0;  /*n是偶数，不是素数，返回0*/
    for(i=3; i<=sqrt(n); i+=2)
        if(n%i==0)
            return 0;  /*n是奇数，不是素数，返回0*/
    return 1;  /*n是除2以外的素数返回1*/
}
int main()
{
    int n, i, ok;
    while(scanf("%d",&n)!=EOF)
    {
        ok=0;  /*进入循环前先置标志位*/
        for(i=2; i<=n/2; i++)
        {
            if( fun(i) )
                if( fun(n-i) )
                {
                    printf("%d %d\n", i, n-i);  /*i和n-i都是素数，则打印*/
                    ok=1;
                }
            if(i!=2)
                i++;
            if(ok)
                break;  /*已打印出所需要的输出结果，跳出循环*/
        }
    }
    return 0;
}

//运行结果：

//20↙︎
//3 17
