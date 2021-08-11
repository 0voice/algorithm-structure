//#ifndef __SNAKE_H__
//#define __SNAKE_H__

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

extern int W;//地图宽度
extern int H;//地图高度

extern char map[22][52];//定义地图
extern char key;//用来保存用户操作时输入的键值

extern int direct;//蛇当前的运动方向
extern int food[2];
extern int head;//记录长度

extern int snake[400][3];//蛇的所有坐标点以及蛇   身体(snake[i][0]=0)   和    蛇头(snake[i][0]=1)   从尾部向头部走

void init(char map[22][52], int snake[400][3]);//游戏开始的时候初始化
void makeMap(char map[22][52], int snake[400][3], int food[]);//根据move后的蛇和生成的food更改map里面的值---制作地图
void move(int snake[400][3], int direct);//让蛇的坐标进行移动
void makeFood(int food[]);//生成随机数制作一个食物坐标
void showView(char map[22][52]);  //绘出视图
int ifEat(int head, int food[2]); //判断食物是否被吃掉
int ifReprat(int snake[400][3], int x, int y);//判断生成的食物是否与蛇有重复
int ifBump(int head);//判断是否会相撞(撞自己或撞墙)
void getKey();//读取键值并重新设置运动方向

//#endif
