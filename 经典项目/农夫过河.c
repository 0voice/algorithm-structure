//一个农夫在河边带了一只狼、一只羊和一颗白菜，他需要把这三样东西用船带到河的对岸。然而，这艘船只能容下农夫本人和另外一样东西。
//如果农夫不在场的话，狼会吃掉羊，羊也会吃掉白菜。请编程为农夫解决这个过河问题。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 15
int a[N][4];
int b[N];
char *name[]=
{
    "        ",
    "and wolf",
    "and goat",
    "and cabbage"
};

int search(int Step)
{
    int i;
    /*若该种步骤能使各值均为1，则输出结果，进入回归步骤*/
    if(a[Step][0]+a[Step][1]+a[Step][2]+a[Step][3] == 4)
    {
       
        for(i=0; i<=Step; i++)  /*能够依次输出不同的方案*/
        {
            printf("east: ");
            if(a[i][0] == 0)
                printf("wolf  ");
            if(a[i][1] == 0)
                printf("goat  ");
            if(a[i][2] == 0)
                printf("cabbage  ");
            if(a[i][3] == 0)
                printf("farmer  ");
            if(a[i][0] && a[i][1] && a[i][2] && a[i][3])
                printf("none");
            printf("             ");
            printf("west: ");
            if(a[i][0] == 1)
                printf("wolf  ");
            if(a[i][1] == 1)
                printf("goat  ");
            if(a[i][2] == 1)
                printf("cabbage  ");
            if(a[i][3] == 1)
                printf("farmer  ");
            if(!(a[i][0] || a[i][1] || a[i][2] || a[i][3]))
                printf("none");
            printf("\n\n\n");
            if(i<Step)
                printf("                       the %d time\n",i+1);
            if(i>0 && i<Step)
            {
                if(a[i][3] == 0)  /*农夫在本岸*/
                {
                    printf("                  ----->  farmer ");
                    printf("%s\n", name[b[i] + 1]);
                }
                else      /*农夫在对岸*/
                {
                    printf("                  <-----  farmer ");
                    printf("%s\n", name[b[i] + 1]);
                }
            }
        }
        printf("\n\n\n\n");
        return 0;
    }
    for(i=0; i<Step; i++)
    {
        if(memcmp(a[i],a[Step],16) == 0)  /*若该步与以前步骤相同，取消操作*/
        {
            return 0;
        }
    }
    /*若羊和农夫不在一块而狼和羊或者羊和白菜在一块，则取消操作*/
    if(a[Step][1]!=a[Step][3] && (a[Step][2] == a[Step][1] || a[Step][0] == a[Step][1]))
    {
        return 0;
    }
    /*递归，从带第一种动物开始依次向下循环，同时限定递归的界限*/
    for(i=-1; i<=2; i++)
    {
        b[Step]=i;
        memcpy(a[Step+1], a[Step], 16);  /*复制上一步状态，进行下一步移动*/
        a[Step+1][3]=1-a[Step+1][3];  /*农夫过去或者回来*/
        if(i == -1)
        {
            search(Step+1);  /*进行第一步*/
        }
        else
            if(a[Step][i] == a[Step][3])  /*若该物与农夫同岸，带回*/
            {
                a[Step+1][i]=a[Step+1][3];  /*带回该物*/
                search(Step+1);  /*进行下一步*/
            }
    }
    return 0;
}

int main()
{
    printf("\n\n             农夫过河问题，解决方案如下：\n\n\n");
    search(0);
    return 0;
}


//运行结果：

/**
             农夫过河问题，解决方案如下：


east: wolf  goat  cabbage  farmer               west: none


                       the 1 time
east: wolf  cabbage               west: goat  farmer 


                       the 2 time
                  <-----  farmer        
east: wolf  cabbage  farmer               west: goat 


                       the 3 time
                  ----->  farmer and wolf
east: cabbage               west: wolf  goat  farmer 


                       the 4 time
                  <-----  farmer and goat
east: goat  cabbage  farmer               west: wolf 


                       the 5 time
                  ----->  farmer and cabbage
east: goat               west: wolf  cabbage  farmer 


                       the 6 time
                  <-----  farmer        
east: goat  farmer               west: wolf  cabbage 


                       the 7 time
                  ----->  farmer and goat
east: none             west: wolf  goat  cabbage  farmer 






east: wolf  goat  cabbage  farmer               west: none


                       the 1 time
east: wolf  cabbage               west: goat  farmer 


                       the 2 time
                  <-----  farmer        
east: wolf  cabbage  farmer               west: goat 


                       the 3 time
                  ----->  farmer and cabbage
east: wolf               west: goat  cabbage  farmer 


                       the 4 time
                  <-----  farmer and goat
east: wolf  goat  farmer               west: cabbage 


                       the 5 time
                  ----->  farmer and wolf
east: goat               west: wolf  cabbage  farmer 


                       the 6 time
                  <-----  farmer        
east: goat  farmer               west: wolf  cabbage 


                       the 7 time
                  ----->  farmer and goat
east: none             west: wolf  goat  cabbage  farmer 
*/
