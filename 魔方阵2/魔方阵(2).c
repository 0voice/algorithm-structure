/*
 4N魔方阵
 说明
 与奇数魔术方阵相同，在于求各行、各列与各对角线的和相等，而这次方阵的维度是4的倍
 数。
 解法
 先来看看4X4方阵的解法：
 简单的说，就是一个从左上由1依序开始填，但遇对角线不填，另一个由左上由16开始填，但只
 填在对角线，再将两个合起来就是解答了；如果N大于2，则以4X4为单位画对角线：
 至于对角线的位置该如何判断，有两个公式，有兴趣的可以画图印证看看，如下所示：
 左上至右下：j % 4 == i % 4
 右上至左下：(j % 4 + i % 4) == 1
*/

#include <stdio.h>
#include <stdlib.h>
#define N 8
int main(void) {
    int i, j;
    int square[N+1][N+1] = {0};
    for(j = 1; j <= N; j++) {
        for(i = 1; i <= N; i++){
            if(j % 4 == i % 4 || (j % 4 + i % 4) == 1)
                square[i][j] = (N+1-i) * N -j + 1;
            else
                square[i][j] = (i - 1) * N + j;
        }
    }
    for(i = 1; i <= N; i++) {
        for(j = 1; j <= N; j++)
            printf("%2d ", square[i][j]);
        printf("\n");
    }
    return 0;
}
