/*
 插补搜寻法

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10
#define SWAP(x,y) {int t; t = x; x = y; y = t;}
void quicksort(int[], int, int);
int intsrch(int[], int);
int main(void) {
    int number[MAX] = {0};
    int i, find;
    srand(time(NULL));
    for(i = 0; i < MAX; i++) {
        number[i] = rand() % 100;
    }
    quicksort(number, 0, MAX-1);
    printf("数列：");
    for(i = 0; i < MAX; i++)
        printf("%d ", number[i]);
    printf("\n输入寻找对象：");
    scanf("%d", &find);
    if((i = intsrch(number, find)) >= 0)
        printf("找到数字于索引%d ", i);
    else
        printf("\n找不到指定数");
    printf("\n");
    return 0;
}
int intsrch(int number[], int find) {
    int low, mid, upper;
    low = 0;
    upper = MAX - 1;
    while(low <= upper) {
        mid = (upper-low)*
        (find-number[low])/(number[upper]-number[low])
        + low;
        if(mid < low || mid > upper)
            return -1;
        if(find < number[mid])
            upper = mid - 1;
        else if(find > number[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
void quicksort(int number[], int left, int right) {
    int i, j, k, s;
    if(left < right) {
        s = number[(left+right)/2];
        i = left - 1;
        j = right + 1;
        while(1) {
            while(number[++i] < s) ; 
            while(number[--j] > s) ; 
            if(i >= j)
                break;
            SWAP(number[i], number[j]);
        }
        quicksort(number, left, i-1); 
        quicksort(number, j+1, right); 
    }
}
