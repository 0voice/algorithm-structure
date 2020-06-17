/*
 背包问题（Knapsack Problem）
 */

#include <stdio.h>
#include <stdlib.h>
#define LIMIT 8 
#define N 5 
#define MIN 1 
struct body {
    char name[20];
    int size;
    int price;
};
typedef struct body object;
int main(void) {
    int item[LIMIT+1] = {0};
    int value[LIMIT+1] = {0};
    int newvalue, i, s, p;
    object a[] = {{"李子", 4, 4500},
        {"苹果", 5, 5700},
        {"橘子", 2, 2250},
        {"草莓", 1, 1100},
        {"甜瓜", 6, 6700}};
    for(i = 0; i < N; i++) {
        for(s = a[i].size; s <= LIMIT; s++) {
            p = s - a[i].size;
            newvalue = value[p] + a[i].price;
            if(newvalue > value[s]) {
                value[s] = newvalue;
                item[s] = i;
            }
        }
    }
    printf("物品\t价格\n");
    for(i = LIMIT; i >= MIN; i = i - a[item[i]].size) {
        printf("%s\t%d\n",
               a[item[i]].name, a[item[i]].price);
    }
    printf("合计\t%d\n", value[LIMIT]);
    return 0;
}
