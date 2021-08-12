//求给定范围start〜end之间的所有素数。

#include<stdio.h>
#include<math.h>
int main()
{
    int start, end, i, k, m, flag=1, h=0;
    do
    {
        printf("Input START and END:");
        scanf("%d%d", &start, &end);
    }while(!(start>0 && start<end));
    printf("......... prime table(%d-%d).........\n", start, end);
    for(m=start; m<=end; m++)
    {
        k=sqrt(m);
        for(i=2; i<=k; i++)
            if(m%i==0)
            {
                flag=0;
                break;
            }
        if(flag)
        {
            printf("%-4d",m);
            h++;
            if(h%10==0)
                printf("\n");
        }
        flag=1; 
    }
    printf("\nThe total is %d", h);
    return 0;
}


//运行结果：

//Input START and END:1 100
//......... prime table(1-100).........
//1   2   3   5   7   11  13  17  19  23 
//29  31  37  41  43  47  53  59  61  67 
//71  73  79  83  89  97
  
