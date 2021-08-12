//在歌星大奖赛中，有10个评委为参赛的选手打分，分数为1〜100分。选手最后得分为：去掉一个最高分和一个最低分后其余8个分数的平均值。请编写一个程序实现。

#include<stdio.h>
int main()
{
    int m, n, temp, i;
    printf("Input m & n:");
    scanf("%d%d", &m, &n);
    if(m<n)  /*比较大小，使得m中存储大数，n中存储小数*/
    {
        temp = m;
        m = n;
        n = temp;
    }
    for(i=m; i>0; i++)  /*从大数开始寻找满足条件的自然数*/
        if(i%m==0 && i%n==0)
        {/*输出满足条件的自然数并结束循环*/
            printf("The LCW of %d and %d is: %d\n", m, n, i);
            break;
        }
   
    return 0;
}

//运行结果：

//Input m & n:6 24
//The LCW of 24 and 6 is: 24
