/**
假设有张王李三家，每家都有3个孩子。某一天，这三家的9个孩子一起比赛短跑，规定不考虑年龄大小，第1名得9分，第2名得8分，
第3名得7分，依次类推。比赛结束后统计分数发现三家孩子的总分是相同的，同时限定这9个孩子的名次不存在并列的情况，且同一
家的孩子不会获得相连的名次。现已知获得第1名的是李家的孩子，获得第2名的是王家的孩子，要求编程求出获得最后一名的是哪家
的孩子。
*/


#include <stdio.h>
int main()
{
    int score[4][4];
    int zhang, wang, li, last, i, j;
    score[1][1]=7;  /*score[1]存放张家三个孩子的分数*/
    score[2][1]=8;  /*score[2]存放王家三个孩子的分数*/
    score[3][1]=9;  /*score[3]存放李家三个孩子的分数*/
    for(zhang=4; zhang<6; zhang++)  /*张家孩子在4到6分段可能取值的分数为4,5，不能取6*/
        for(wang=4; wang<7; wang++)  /*王家孩子在4到6分段可能取值的分数为4,5,6*/
            for(li=4; li<7; li++)  /*李家孩子在4到6分段可能取值的分数为4,5,6*/
                if(zhang!=wang && li!=zhang && li!=wang
                   && 15-zhang-score[1][1]!=15-wang-score[2][1]  /*9个孩子名次不存在并列的情况*/
                   && 15-zhang-score[1][1]!=15-li-score[3][1]
                   && 15-wang-score[2][1]!=15-li-score[3][1])
                {
                    score[1][2]=zhang;  /*将结果存入对应的数组元素*/
                    score[1][3]=15-zhang-7;
                    score[2][2]=wang;
                    score[2][3]=15-wang-8;
                    score[3][2]=li;
                    score[3][3]=15-li-9;
                }
   
    printf("array score:\n");  /*打印二维数组score，输出各家孩子的分数*/
    for(last=0, i=1; i<=3; i++)
        for(j=1; j<=3; j++)
        {
            printf("%d", score[i][j]);
            printf(" ");
            if(j == 3)
                printf("\n");  /*每输入三个值换行*/
            if(score[i][j] == 1)
                last=i;  /*记录最后一名孩子所来自的家庭*/
        }
    /*输出最后一名孩子来自的家庭*/
    if(last == 1)
        printf("The last one reached the end is a child from family Zhang.\n");
    else if(last == 2)
        printf("The last one reached the end is a child from family Wang.\n");
    else
        printf("The last one reached the end is a child from family Li.\n");
   
    return 0;
}


//运行结果：

//array score:
//7 5 3
//8 6 1
//9 4 2
//The last one reached the end is a child from family Wang.
