/**
设有n座山，计算机与人作为比赛的双方，轮流搬山。规定每次搬山数不能超过k座，谁搬最后一座淮输。游戏开始时，
计算机请人输入山的总数n和每次允许搬山的最大数k，然后请人开始，等人输入了需要搬走的山的数目后，计算机马
上打印出它搬多少座山，并提示尚余多少座山。双方轮流搬山直到最后一座山搬完为止。计算机会显示谁是赢家，并
问人是否要继续比赛。如果人不想玩了，计算机便会统计出共玩了几局，双方胜负如何。
*/

#include<stdio.h>
int main()
{
    int n, k, x, y, cc, pc, g;
    printf("More Mountain Game\n");
    printf("Game Begin\n");
    pc=cc=0;
    g=1;
    for( ; ; )
    {
        printf("No.%2d game \n", g++);
        printf("-------------\n");
        printf("How many mountains are there?");
        scanf("%d", &n);  /*读入山的总数*/
        if(!n)
            break;
        printf("How many mountains are allowed to each time?");
        do
        {
            scanf("%d", &k);  /*读入允许的搬山数*/
            if(k>n || k<1)  /*判断搬山数*/
                printf("Repeat again!\n");
        }
        while(k>n || k<1);
        do
        {
            printf("How many mountains do you wish move away?");
            scanf("%d",&x);
            if(x<1 || x>k || x>n)  /*判断搬山数是否符合要求*/
            {
                printf("IIIegal,again please!\n");
                continue;
            }
            n-=x;
            printf("There are %d mountains left now.\n", n);
            if(!n)
            {
                printf("……………I win. You are failure……………\n\n");
                cc++;
            }
            else
            {
                y=(n-1)%(k+1);  /*求出最佳搬山数*/
                if(!y)
                    y=1;
                n-=y;
                printf("Copmputer move %d mountains away.\n", y);
                if(n)
                    printf(" There are %d mountains left now.\n", n);
                else
                {
                    printf("……………I am failure. You win………………\n\n");
                    pc++;
                }
            }
        }
        while(n);
    }
    /*打印结果*/
    printf("Games in total have been played %d.\n", cc+pc);
    printf("You score is win %d,lose %d.\n", pc, cc);
    printf("My score is win %d,lose %d.\n", cc, pc);
    return 0;
}


//运行结果：

/**
More Mountain Game
Game Begin
No. 1 game
-------------
How many mountains are there?10↙︎
How many mountains are allowed to each time?3↙︎
How many mountains do you wish move away?5↙︎
IIIegal,again please!
How many mountains do you wish move away?2↙︎
There are 8 mountains left now.
Copmputer move 3 mountains away.
There are 5 mountains left now.
How many mountains do you wish move away?3↙︎
There are 2 mountains left now.
Copmputer move 1 mountains away.
There are 1 mountains left now.
How many mountains do you wish move away?1↙︎
There are 0 mountains left now.
……………I win. You are failure……………
*/
