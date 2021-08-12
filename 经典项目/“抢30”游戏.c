/**
由两个人玩“抢30”游戏，游戏规则是：第一个人先说“1”或“2”，第二个人要接着往下说一个或两个数，然后又轮到第一个人，再接着
往下说一个或两个数。这样两人反复轮流，每次每个人说一个或两个数都可以，但是不可以连说三个数，谁先抢到30，谁得胜。
*/


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int input(int t);
int copu(int s);
int main()
{
    int tol=0;
    printf("\n* * * * * * * *catch thirty* * * * * * * \n");
    printf("Game Begin\n");
    rand();  /*初始化随机数发生器*/
    /*取随机数决定机器和人谁先走第一步。若为1，则表示人先走第一步*/
    if(rand()%2)
        tol=input(tol);
    while(tol!=30)  /*游戏结束条件*/
        if((tol=copu(tol)) == 30)  /*计算机取一个数，若为30则机器胜利*/
            printf("I lose! \n");
        else
            if((tol=input(tol)) == 30)  /*人取一个数，若为30则人胜利*/
                printf("I lose! \n");
    printf(" * * * * * * * *Game Over * * * * * * * *\n");
    return 0;
}

int input(int t)
{
    int a;
    do{
        printf("Please count:");
        scanf("%d", &a);
        if(a>2 || a<1 || t+a>30)
            printf("Error input,again!");
        else
            printf("You count:%d\n", t+a);
    }while(a>2 || a<1 || t+a>30);
    return t+a;  /*返回当前已经取走的数的累加和*/
}

int copu(int s)
{
    int c;
    printf("Computer count:");
    if((s+1)%3 == 0)  /*若剩余的数的模为1，则取1*/
        printf(" %d\n",++s);
    else
        if((s+2)%3 == 0)
        {
            s+=2;  /*若剩余的数的模为2，则取2*/
            printf(" %d\n",s);
        }
        else
        {
            c=rand()%2+1;  /*否则随机取1或2*/
            s+=c;
            printf(" %d\n",s);
        }
    return s;
}


//运行结果：

/**
* * * * * * * *catch thirty* * * * * * *
Game Begin
Please count:1
You count:1
Computer count: 3
Please count:4
Error input,again!Please count:2
You count:5
Computer count: 6
Please count:1
You count:7
Computer count: 9
Please count:2
You count:11
Computer count: 12
Please count:2
You count:14
Computer count: 15
Please count:2
You count:17
Computer count: 18
Please count:
2
You count:20
Computer count: 21
Please count:2
You count:23
Computer count: 24
Please count:2
You count:26
Computer count: 27
Please count:2
You count:29
Computer count: 30
I lose!
* * * * * * * *Game Over * * * * * * * *
*/
