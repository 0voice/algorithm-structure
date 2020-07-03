/*
 快速排序法（二）
 说明在快速排序法（一）中，每次将最左边的元素设为轴，而之前曾经说过，快速排序法的
 加速在于轴的选择，在这个例子中，只将轴设定为中间的元素，依这个元素作基准进行比较，
 这可以增加快速排序法的效率。
 解法在这个例子中，取中间的元素s作比较，同样的先得右找比s大的索引i，然后找比s小的
 索引j，只要两边的索引还没有交会，就交换i 与j 的元素值，这次不用再进行轴的交换了，
 因为在寻找交换的过程中，轴位置的元素也会参与交换的动作，例如：
 41 24 76 11 45 64 21 69 19 36
 首先left为0，right为9，(left+right)/2 = 4（取整数的商），所以轴为索引4的位置，比较的元素是
 45，您往右找比45大的，往左找比45小的进行交换：
 41 24 76* 11 [45] 64 21 69 19 *36
 41 24 36 11 45* 64 21 69 19* 76
 41 24 36 11 19 64* 21* 69 45 76
 [41 24 36 11 19 21] [64 69 45 76]
 完成以上之后，再初别对左边括号与右边括号的部份进行递回，如此就可以完成排序的目的。
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10
#define SWAP(x,y) {int t; t = x; x = y; y = t;}
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
void quicksort(int number[], int left, int right) {
    int i, j, s;
    if(left < right) {
        s = number[(left+right)/2];
        i = left - 1;
        j = right + 1;
        while(1) {
            while(number[++i] < s) ; // 向右找
            while(number[--j] > s) ; // 向左找
            if(i >= j)
                break;
            SWAP(number[i], number[j]);
        }
        quicksort(number, left, i-1); // 对左边进行递回
        quicksort(number, j+1, right); // 对右边进行递回
    }
}
