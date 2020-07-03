/*
 循序搜寻法（使用卫兵）
 说明
 搜寻的目的，是在「已排序的资料」中寻找指定的资料，而当中循序搜寻是最基本的搜寻法，
 只要从资料开头寻找到最后，看看是否找到资料即可。
 解法
 初学者看到循序搜寻，多数都会使用以下的方式来进行搜寻：
 while(i < MAX) {
 if(number[i] == k) {
 printf("找到指定值");
 break;
 }
 i++;
 }
 这个方法基本上没有错，但是可以加以改善，可以利用设定卫兵的方式，省去if判断式，卫兵通
 常设定在数列最后或是最前方，假设设定在列前方好了（索引0的位置），我们从数列后方向前
 找，如果找到指定的资料时，其索引值不是0，表示在数列走访完之前就找到了，在程式的撰写
 上，只要使用一个while回圈就可以了。
 下面的程式为了配合卫兵的设置，自行使用快速排序法先将产生的数列排序，然后才进行搜寻，
 若只是数字的话，通常您可以使用程式语言函式库所提供的搜寻函式。
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10
#define SWAP(x,y) {int t; t = x; x = y; y = t;}
int search(int[]);
int partition(int[], int, int);
void quicksort(int[], int, int);
int main(void) {
    int number[MAX+1] = {0};
    int i, find;
    srand(time(NULL));
    for(i = 1; i <= MAX; i++)
        number[i] = rand() % 100;
    quicksort(number, 1, MAX);
    printf("数列：");
    for(i = 1; i <= MAX; i++)
        printf("%d ", number[i]);
    printf("\n输入搜寻值：");
    scanf("%d", &number[0]);
    if(find = search(number))
        printf("\n找到数值于索引%d ", find);
    else
        printf("\n找不到数值");
    printf("\n");
    return 0;
}
int search(int number[]) {
    int i, k;
    k = number[0];
    i = MAX;
    while(number[i] != k)
        i--;
    return i;
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
