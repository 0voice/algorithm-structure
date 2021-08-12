/**
骰子是一个有六个面的正方体，每个面分别印有1〜6之间的小圆点代表点数。假设这个游戏的规则是：
两个人轮流掷骰子6次，并将每次投掷的点数累加起来。点数多者获胜；点数相同则为平局。

要求编写程序模拟这个游戏的过程，并求出玩100盘之后谁是最终的获胜者。
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int d1, d2, c1, c2, i, j;
    c1 = c2 = 0;  /*初始化*/
    srand((unsigned)time(NULL));
    rand();  /*初始化随机数产生器*/
    for(i=1; i<=100; i++)
    {  /*模拟游戏过程*/
        d1 = d2 = 0;
        for(j=1; j<=6; j++)
        {  /*两个人轮流掷骰子*/
            d1 = d1+rand()+1;
            d2 = d2+rand()+1;
        }
        if(d1>d2)
            c1++;  /*累加获胜盘数*/
        else if(d1<d2)
            c2++;
    }
    if(c1>c2)  /*输出最终获胜者信息*/
        printf("\nThe first win.\n");
    else
        if (c1<c2)
            printf("\nThe second win.\n");
        else
            printf("They tie.\n");
   
    return 0;
}

//运行结果：

//The second win.
