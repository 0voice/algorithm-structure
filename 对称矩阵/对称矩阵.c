/*
对称矩阵
*/

#include <stdio.h>
#include <stdlib.h>
#define N 5
int main(void) {
    int arr1[N][N] = {
        {1, 2, 3, 4, 5},
        {0, 6, 7, 8, 9},
        {0, 0, 10, 11, 12},
        {0, 0, 0, 13, 14},
        {0, 0, 0, 0, 15}};
    int arr2[N*(1+N)/2] = {0};
    int i, j, loc = 0;
    printf("原二维资料：\n");
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            printf("%4d", arr1[i][j]);
        }
        printf("\n");
    }
    printf("\n以列为主：");
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            if(arr1[i][j] != 0)
                arr2[loc++] = arr1[i][j];
        }
    }
    for(i = 0; i < N*(1+N)/2; i++)
        printf("%d ", arr2[i]);
    printf("\n输入索引(i, j)：");
    scanf("%d, %d", &i, &j);
    loc = N*i - i*(i+1)/2 + j;
    printf("(%d, %d) = %d", i, j, arr2[loc]);
    printf("\n");
    return 0;
}
