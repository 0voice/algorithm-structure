//编写一个程序，将一个3行3列的矩阵转置。

#include<stdio.h>
int main()
{
    int n[3][3]={1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i, j, temp;
    printf("原始矩阵：\n");
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
            printf("%d  ", n[i][j]);  /*输出原始矩阵*/
        printf("\n");
    }
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
        {
            if (j>i)
            {  /*将主对角线右上方的数组元素与主对角线左下方的数组元素进行单方向交换*/
                temp=n[i][j];
                n[i][j]=n[j][i];
                n[j][i]=temp;
            }
        }
    printf("转置矩阵：\n");
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
            printf("%d  ", n[i][j]);  /*输出原始矩阵的转置矩阵*/
        printf("\n");
    }
    return 0;
}


//运行结果：

//原始矩阵：
//1  2  3 
//4  5  6 
//7  8  9 
//转置矩阵：
//1  4  7 
//2  5  8 
//3  6  9
