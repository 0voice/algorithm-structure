/**
国际象棋的棋盘为8×8的方格棋盘。现将“马”放在任意指定的方格中，按照“马”走棋的规则将“马”进行移动。
要求每个方格只能进入一次，最终使得“马”走遍棋盘的64个方格。

编写一个C程序，实现马踏棋盘操作，要求用1〜64这64个数字标注马移动的路径，也就是按照求出的行走路
线，将数字1，2，……64依次填入棋盘的方格中，并输出。
*/

#include <stdio.h>
#define X 8
#define Y 8
int chess[X][Y];

int nextxy(int *x, int *y, int count)  /*找到基于x,y位置的下一个可走的位置*/
{
    switch(count)
    {
        case 0:
            if(*x+2<=X-1 && *y-1>=0 && chess[*x+2][*y-1]==0)
            {
                *x=*x+2;
                *y=*y-1;
                return 1;
            }
            break;
        case 1:
            if(*x+2<=X-1 && *y+1<=Y-1 && chess[*x+2][*y+1]==0)
            {
                *x=*x+2;
                *y=*y+1;
                return 1;
            }
            break;
        case 2:
            if(*x+1<=X-1 && *y-2>=0 && chess[*x+1][*y-2]==0)
            {
                *x=*x+1;
                *y=*y-2;
                return 1;
            }
            break;
        case 3:
            if(*x+1<=X-1 && *y+2<=Y-1 && chess[*x+1][*y+2]==0)
            {
                *x=*x+1;
                *y=*y+2;
                return 1;
            }
            break;
        case 4:
            if(*x-2>=0 && *y-1>=0 && chess[*x-2][*y-1]==0)
            {
                *x=*x-2;
                *y=*y-1;
                return 1;
            }
            break;
        case 5:
            if(*x-2>=0 && *y+1<=Y-1 && chess[*x-2][*y+1]==0)
            {
                *x=*x-2;
                *y=*y+1;
                return 1;
            }
            break;
        case 6:
            if(*x-1>=0 && *y-2>=0 && chess[*x-1][*y-2]==0)
            {
                *x=*x-1;
                *y=*y-2;
                return 1;
            }
            break;
        case 7:
            if(*x-1>=0 && *y+2<=Y-1 && chess[*x-1][*y+2]==0)
            {
                *x=*x-1;
                *y=*y+2;
                return 1;
            }
            break;
        default:
            break;
    }
    return 0;
}

int TravelChessBoard(int x, int y, int tag)  /*深度优先搜索地"马踏棋盘"*/
{
    int x1=x, y1=y, flag=0, count=0;
    chess[x][y]=tag;
    if(tag == X*Y)
    {
        return 1;
    }
    flag=nextxy(&x1, &y1, count);
    while(flag==0 && count<7)
    {
        count=count+1;
        flag=nextxy(&x1, &y1, count);
    }
    while(flag)
    {
        if(TravelChessBoard(x1, y1, tag+1))
            return 1;
        x1=x;
        y1=y;
        count=count+1;
        flag=nextxy(&x1, &y1, count);  /*寻找下一个(x,y)*/
        while(flag==0 && count<7)
        {  /*循环地寻找下一个(x,y)*/
            count=count+1;
            flag=nextxy(&x1, &y1, count);
        }
    }
    if(flag == 0)
        chess[x][y]=0;
    return 0;
}
int main()
{
    int i, j;
    for(i=0; i<X; i++)
        for(j=0; j<Y; j++)
            chess[i][j]=0;
    if(TravelChessBoard(2, 0, 1))
    {
        for(i=0; i<X; i++)
        {
            for(j=0; j<Y; j++)
                printf("%-5d", chess[i][j]);
            printf("\n");
        }
        printf("The horse has travelled the chess borad\n");
    }
    else
        printf("The horse cannot travel the chess board\n");
    return 0;
}

//运行结果

//43   50   47   38   57   52   61   32  
//48   37   44   51   46   33   58   53  
//1    42   49   56   39   60   31   62  
//36   15   40   45   34   29   54   59  
//41   2    35   16   55   24   63   30  
//14   5    12   9    22   19   28   25  
//3    10   7    20   17   26   23   64  
//6    13   4    11   8    21   18   27
