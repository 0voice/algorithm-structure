//用1、2、3、4共4个数字能组成多少个互不相同且无重复数字的三位数？都是多少？

#include <stdio.h>

int main()
{
    int i, j, k, count=0;
    for(i=1; i<5; i++)
        for(j=1; j<5; j++)
            for(k=1; k<5; k++)
            {
                if(i!=k && i!=j && j!=k)  /*判断三个数是否互不相同*/
                {
                    count++;
                    printf("%d%d%d  ", i, j, k);
                    if(count%8 == 0)  /*每输出8个数换行*/
                        printf("\n");
                }
            }
    printf("\nThe total number is %d.\n", count);
   
    return 0;
}


//运行结果：

//123  124  132  134  142  143  213  214 
//231  234  241  243  312  314  321  324 
//341  342  412  413  421  423  431  432 
//
//The total number is 24.
