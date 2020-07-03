/*
 八皇后
 */
#include <stdio.h>
#include <stdlib.h>
#define N 8
int column[N+1]; // 同栏是否有皇后，1表示有
int rup[2*N+1]; // 右上至左下是否有皇后
int lup[2*N+1]; // 左上至右下是否有皇后
int queen[N+1] = {0};
int num; // 解答编号
void backtrack(int); // 递回求解
int main(void) {
    int i;
    num = 0;
    for(i = 1; i <= N; i++)
        column[i] = 1;
    for(i = 1; i <= 2*N; i++)
        rup[i] = lup[i] = 1;
    backtrack(1);
    return 0;
}
void showAnswer() {
    int x, y;
    printf("\n解答%d\n", ++num);
    for(y = 1; y <= N; y++) {
        for(x = 1; x <= N; x++) {
            if(queen[y] == x) {
                printf(" Q");
            }
            else {
                printf(" .");
            }
        }
        printf("\n");
    }
}
void backtrack(int i) {
    int j;
    if(i > N) {
        showAnswer();
    }
    else {
        for(j = 1; j <= N; j++) {
            if(column[j] == 1 &&
               rup[i+j] == 1 && lup[i-j+N] == 1) {
                queen[i] = j;
                column[j] = rup[i+j] = lup[i-j+N] = 0;
                backtrack(i+1);
                column[j] = rup[i+j] = lup[i-j+N] = 1;
            }
        }
    }
}
