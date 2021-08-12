/**
有21根火柴，两人依次取，每次每人只可取走1〜4根，不能多取，也不能不取，谁取到最后一根火柴谁输。
请编写一个人机对弈程序，要求人先取，计算机后取；计算机为“常胜将军”。
*/

#include <stdio.h>
int main()
{
    int computer, people, spare = 21;
    printf(" -----------------------------------------\n");
    printf(" --------  你不能战胜我,不信试试  --------\n");
    printf(" -----------------------------------------\n\n");
    printf("Game begin:\n\n");
    while(1)
    {
        printf(" ----------  目前还有火柴 %d 根 ----------\n", spare);
        printf("People:");
        scanf("%d", &people);
        if(people<1 || people>4 || people>spare)
        {
            printf("你违规了，你取的火柴数有问题!\n\n");
            continue;
        }
        spare = spare - people;
        if( spare==0 )
        {
            printf("\nComputer win! Game Over!\n");
            break;
        }
        computer = 5 - people;
        spare = spare - computer;
        printf("Computer:%d  \n", computer);
        if( spare==0 )
        {
            printf("\nPeople win! Game Over!\n");
            break;
        }
    }
    return 0;
}

//运行结果：

/**
-----------------------------------------
 --------  你不能战胜我,不信试试  --------
-----------------------------------------

Game begin:

----------  目前还有火柴 21 根 ----------
People:1
Computer:4 
----------  目前还有火柴 16 根 ----------
People:3
Computer:2 
----------  目前还有火柴 11 根 ----------
People:2
Computer:3 
----------  目前还有火柴 6 根 ----------
People:4
Computer:1 
----------  目前还有火柴 1 根 ----------
People:1

Computer win! Game Over!
*/
