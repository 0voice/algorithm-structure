//求任意两个正整数的最小公倍数（LCM）。

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
