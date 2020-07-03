/*
 奇数魔方阵
 说明
 将1到n(为奇数)的数字排列在nxn的方阵上，且各行、各列与各对角线的和必须相同，如下所
 示：
 解法
 填魔术方阵的方法以奇数最为简单，第一个数字放在第一行第一列的正中央，然后向右(左)上
 填，如果右(左)上已有数字，则向下填，如下图所示：
 一般程式语言的阵列索引多由0开始，为了计算方便，我们利用索引1到n的部份，而在计算是向
 右(左)上或向下时，我们可以将索引值除以n值，如果得到余数为1就向下，否则就往右(左)上，
 原理很简单，看看是不是已经在同一列上绕一圈就对了。
*/

#include <stdio.h>
#include <stdlib.h>
#define N 5
int main(void) {
    int i, j, key;
    int square[N+1][N+1] = {0};
    i = 0;
    j = (N+1) / 2;
    for(key = 1; key <= N*N; key++) {
        if((key % N) == 1)
            i++;
        else {
            i--;
            j++;
        }
        if(i == 0)
            i = N;
        if(j > N)
            j = 1;
        square[i][j] = key;
    }
    for(i = 1; i <= N; i++) {
        for(j = 1; j <= N; j++)
            printf("%2d ", square[i][j]);
    }
    return 0;
}
