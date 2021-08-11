#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
int main(int argc, const char * argv[]) {
    int digits = 3; //初始化打印的随机数个数
    int tries = 1;
    int delay = 1;
    time_t wait_time = 0;
    int i = 0;
    time_t seed = 0; //随机函数种子值
    int number = 0;
    char another_game = 'Y';
    do
    {
        bool correct = true;
        while(correct)
        {
            if(tries % 3 == 0 && tries != 3)
                digits++;
            
            srand((unsigned int)time(&seed));
            for ( i = 1; i <= digits; i++ )
            {
                printf("%d ",rand() % 10);//打印digits个随机数
            }
            fflush(stdout);
            wait_time = clock();
            for(;clock() - wait_time < delay*CLOCKS_PER_SEC;);//等待3秒
            printf("\r");//返回行首
            for(i = 1; i <= digits;i++)
            {
                printf("  ");//清空原有的输出数字
            }
            printf("\r");//返回行首
            
            srand((unsigned int)seed);
            for(i = 1;i <= digits;i++)
            {
                //            scanf("%*[^\n]");
                //            scanf("%*c");// 清空输入缓冲全数据
                scanf("%d",&number);
                if ( number != rand() % 10)
                {
                    correct =false;
                    break;
                }
            }
            printf("%s\n",correct ? "Correct!":"Wrong!");//返回结果
            tries++;
        }
        
        //        fflush(stdin);
        scanf("%*[^\n]");
        scanf("%*c");
        printf("Another Game?\n");
        scanf("%c",&another_game);
    }while(toupper(another_game)=='Y');
    return 0;
}
