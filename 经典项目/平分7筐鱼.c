/**
甲、乙、丙三位渔夫出海打鱼，他们随船带了21只箩筐。当晚返航时，他们发现有7筐装满了鱼，还有7筐装了半筐鱼，
另外7筐则是空的，由于他们没有秤，只好通过目测认为7个满筐鱼的重量是相等的，7个半筐鱼的重量是相等的。在不
将鱼倒出来的前提下,怎样将鱼平分为3份？
*/

#include<stdio.h>
int a[3][3], count;
int main()
{
    int i, j, k, m, n, flag;
    printf("It exists possible distribtion plans:\n");
    for(i=0; i<=3; i++)  /*试探第一个人满筐a[0][0]的值，满筐数不能>3*/
    {
        a[0][0]=i;
        for(j=i; j<=7-i&&j<=3; j++)  /*试探第二个人满筐a[1][0]的值，满筐数不能>3*/
        {
            a[1][0]=j;
            if((a[2][0]=7-j-a[0][0])>3)
                continue;  /*第三个人满筐数不能>3*/
            if(a[2][0]<a[1][0])
                break;  /*要求后一个人分的满筐数大于等于前一个人，以排除重复情况*/
            for(k=1; k<=5; k+=2)  /*试探半筐a[0][1]的值，半筐数为奇数*/
            {
                a[0][1]=k;
                for(m=1; m<7-k; m+=2)  /*试探半筐a[1][1]的值，半筐数为奇数*/
                {
                    a[1][1]=m;
                    a[2][1]=7-k-m;
                    /*判断每个人分到的鱼是 3.5筐，flag为满足题意的标记变量*/
                    for(flag=1,n=0; flag&&n<3; n++)
                        if(a[n][0]+a[n][1]<7&&a[n][0]*2+a[n][1] == 7)
                            a[n][2]=7-a[n][0]-a[n][1];  /*计算应得到的空筐数量*/
                        else
                            flag=0;  /*不符合题意则置标记为0*/
                    if(flag)
                    {
                        ++count;
                        printf("No.%d Full basket Semi-basket Empty\n", count);
                        for(n=0; n<3; n++)
                            printf(" fisher %c: %d %d %d\n",'A'+n, a[n][0], a[n][1], a[n][2]);
                    }
                }
            }
        }
    }
    return 0;
}

//运行结果：

//It exists possible distribtion plans:
//No.1 Full basket Semi-basket Empty
//fisher A: 1 5 1
//fisher B: 3 1 3
//fisher C: 3 1 3
//No.2 Full basket Semi-basket Empty
//fisher A: 2 3 2
//fisher B: 2 3 2
//fisher C: 3 1 3
