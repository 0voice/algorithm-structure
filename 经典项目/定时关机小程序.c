#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
    char cmd[20]="shutdown -s -t ";
    char t[5]="0";
    int c;

    system("title C语言关机程序");  //设置cmd窗口标题
    system("mode con cols=48 lines=25");  //窗口宽度高度 
    system("color f0");  //可以写成 red 调出颜色组
    system("date /T");
    system("TIME /T");

    printf("----------- C语言关机程序 -----------\n");
    printf("1.实现10分钟内的定时关闭计算机\n");
    printf("2.立即关闭计算机\n");
    printf("3.注销计算机\n");
    printf("0.退出系统\n");
    printf("-------------------------------------\n");

    scanf("%d",&c);
    switch(c) {
        case 1:
            printf("您想在多少秒后自动关闭计算机？（0~600）\n");
            scanf("%s",t);
            system(strcat(cmd,t));
            break;
        case 2:
            system("shutdown -p");
            break;
        case 3:
            system("shutdown -l");
            break;
        case 0:
            break;
        default:
            printf("Error!\n");
    }
    system("pause");
    return 0;
}
