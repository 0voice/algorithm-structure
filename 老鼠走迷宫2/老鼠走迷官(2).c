/*
老鼠走迷官（二）
说明由于迷宫的设计，老鼠走迷宫的入口至出口路径可能不只一条，如何求出所有的路径呢？
解法求所有路径看起来复杂但其实更简单，只要在老鼠走至出口时显示经过的路径，然后退
回上一格重新选择下一个位置继续递回就可以了，比求出单一路径还简单，我们的程式只要作
一点修改就可以了。
*/
#include <stdio.h>
#include <stdlib.h>
void visit(int, int);
int maze[9][9] = {{2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 2, 0, 2, 2, 0, 2},
    {2, 0, 2, 0, 0, 2, 0, 0, 2},
    {2, 0, 2, 0, 2, 0, 2, 0, 2},
    {2, 0, 0, 0, 0, 0, 2, 0, 2},
    {2, 2, 0, 2, 2, 0, 2, 2, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2}};
int startI = 1, startJ = 1; // 入口
int endI = 7, endJ = 7; // 出口
int main(void) {
    int i, j;
    printf("显示迷宫：\n");
    for(i = 0; i < 7; i++) {
        for(j = 0; j < 7; j++)
            if(maze[i][j] == 2)
                printf("█");
            else
                printf(" ");
        printf("\n");
    }
    visit(startI, startJ);
    return 0;
}
void visit(int i, int j) {
    int m, n;
    maze[i][j] = 1;
    if(i == endI && j == endJ) {
        printf("\n显示路径：\n");
        for(m = 0; m < 9; m++) {
            for(n = 0; n < 9; n++)
                if(maze[m][n] == 2)
                    printf("█");
                else if(maze[m][n] == 1)
                    printf("◇");
                else
                    printf(" ");
            printf("\n");
        }
    }
    if(maze[i][j+1] == 0) visit(i, j+1);
    if(maze[i+1][j] == 0) visit(i+1, j);
    if(maze[i][j-1] == 0) visit(i, j-1);
    if(maze[i-1][j] == 0) visit(i-1, j);
    maze[i][j] = 0;
}