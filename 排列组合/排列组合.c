/*
 排列组合
 说明将一组数字、字母或符号进行排列，以得到不同的组合顺序，例如1 2 3这三个数的排列
 组合有：1 2 3、1 3 2、2 1 3、2 3 1、3 1 2、3 2 1。
 解法可以使用递回将问题切割为较小的单元进行排列组合，例如1 2 3 4的排列可以分为1 [2 3
 4]、2 [1 3 4]、3 [1 2 4]、4 [1 2 3]进行排列，这边利用旋转法，先将旋转间隔设为0，将最右边的
 数字旋转至最左边，并逐步增加旋转的间隔，
*/

#include <stdio.h>
#include <stdlib.h>
#define N 4
void perm(int*, int);
int main(void) {
    int num[N+1], i;
    for(i = 1; i <= N; i++)
        num[i] = i;
    perm(num, 1);
    return 0;
}
void perm(int* num, int i) {
    int j, k, tmp;
    if(i < N) {
        for(j = i; j <= N; j++) {
            tmp = num[j];
            // 旋转该区段最右边数字至最左边
            for(k = j; k > i; k--)
                num[k] = num[k-1];
            num[i] = tmp;
            perm(num, i+1);
            // 还原
            for(k = i; k < j; k++)
                num[k] = num[k+1];
            num[j] = tmp;
        }
    }
    else { // 显示此次排列
        for(j = 1; j <= N; j++)
            printf("%d ", num[j]);
        printf("\n");
    }
}
