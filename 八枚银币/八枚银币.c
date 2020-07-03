/*
 八枚银币
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void compare(int[], int, int, int);
void eightcoins(int[]);
int main(void) {
    int coins[8] = {0};
    int i;
    srand(time(NULL));
    for(i = 0; i < 8; i++)
        coins[i] = 10;
    printf("\n输入假币重量(比10大或小)：");
    scanf("%d", &i);
    coins[rand() % 8] = i;
    eightcoins(coins);
    printf("\n\n列出所有钱币重量：");
    for(i = 0; i < 8; i++)
        printf("%d ", coins[i]);
    printf("\n");
    return 0;
}
void compare(int coins[], int i, int j, int k) {
    if(coins[i] > coins[k])
        printf("\n假币%d 较重", i+1);
    else
        printf("\n假币%d 较轻", j+1);
}
void eightcoins(int coins[]) {
    if(coins[0]+coins[1]+coins[2] ==
       coins[3]+coins[4]+coins[5]) {
        if(coins[6] > coins[7])
            compare(coins, 6, 7, 0);
        else
            compare(coins, 7, 6, 0);
    }
    else if(coins[0]+coins[1]+coins[2] >
            coins[3]+coins[4]+coins[5]) {
        if(coins[0]+coins[3] == coins[1]+coins[4])
            compare(coins, 2, 5, 0);
        else if(coins[0]+coins[3] > coins[1]+coins[4])
            compare(coins, 0, 4, 1);
        if(coins[0]+coins[3] < coins[1]+coins[4])
            compare(coins, 1, 3, 0);
    }
    else if(coins[0]+coins[1]+coins[2] <
            coins[3]+coins[4]+coins[5]) {
        if(coins[0]+coins[3] == coins[1]+coins[4])
            compare(coins, 5, 2, 0);
        else if(coins[0]+coins[3] > coins[1]+coins[4])
            compare(coins, 3, 1, 0);
        if(coins[0]+coins[3] < coins[1]+coins[4])
            compare(coins, 4, 0, 1);
    }
}
