/*
 快速排序法（三）
 说明
 之前说过轴的选择是快速排序法的效率关键之一，在这边的快速排序法的轴选择方式更加快了
 快速排序法的效率，它是来自演算法名书Introduction to Algorithms 之中。
 解法
 先说明这个快速排序法的概念，它以最右边的值s作比较的标准，将整个数列分为三个部份，
 一个是小于s的部份，一个是大于s的部份，一个是未处理的部份，如下所示：
 在排序的过程中，i 与j 都会不断的往右进行比较与交换，最后数列会变为以下的状态：
 然后将s的值置于中间，接下来就以相同的步骤会左右两边的数列进行排序的动作，如下所示：
 整个演算的过程，直接摘录书中的虚拟码来作说明：
 QUICKSORT(A, p, r)
 if p < r
 then q <- PARTITION(A, p, r)
 QUICKSORT(A, p, q-1)
 QUICKSORT(A, q+1, r)
 end QUICKSORT
 PARTITION(A, p, r)
 x <- A[r]
 i <- p-1
 for j <- p to r-1
 do if A[j] <= x
 then i <- i+1
 exchange A[i]<->A[j]
 exchange A[i+1]<->A[r]
 return i+1
 end PARTITION
 一个实际例子的演算如下所示：
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10
#define SWAP(x,y) {int t; t = x; x = y; y = t;}
int partition(int[], int, int);
void quicksort(int[], int, int);
int main(void) {
    int number[MAX] = {0};
    int i, num;
    srand(time(NULL));
    printf("排序前：");
    for(i = 0; i < MAX; i++) {
        number[i] = rand() % 100;
        printf("%d ", number[i]);
    }
    quicksort(number, 0, MAX-1);
    printf("\n排序后：");
    for(i = 0; i < MAX; i++)
        printf("%d ", number[i]);
    printf("\n");
    return 0;
}
int partition(int number[], int left, int right) {
    int i, j, s;
    s = number[right];
    i = left - 1;
    for(j = left; j < right; j++) {
        if(number[j] <= s) {
            i++;
            SWAP(number[i], number[j]);
        }
    }
    SWAP(number[i+1], number[right]);
    return i+1;
}
void quicksort(int number[], int left, int right) {
    int q;
    if(left < right) {
        q = partition(number, left, right);
        quicksort(number, left, q-1);
        quicksort(number, q+1, right);
    }
}
