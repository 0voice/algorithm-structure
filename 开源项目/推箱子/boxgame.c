#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 4			//地图设置为MAX*MAX大小
#define X_MAX MAX			//也可以单独设置大小
#define Y_MAX MAX

void Map_Build();			//用来随机生成Map地图
void Map_Display();			//用来显示地图
void People_Move(char driction);		//对用户的输入进行处理
void Map_Victory();			//通关界面

typedef struct{
	int x;
	int y;
}Coordinate;				//坐标结构体

char map[X_MAX][Y_MAX];
Coordinate People,Box,Destination;	//定义三个坐标结构体变量，人，箱子，目的地

int main()
{
	char Driction = 0;	//定义一个char型变量，用来接收用户输入的命令
	Map_Build();		//随机生成一个地图
	while(Box.x!=Destination.x || Box.y!=Destination.y)	//如果箱子坐标与目的地的坐标相等则跳出循环
	{
		printf("\033[2J");										//清屏代码
		Map_Display();											//显示地图
		printf("Pormpt 8:up 2:down 4:left 6:right q:quit\n");	//提示用户输入命令
		printf("input driction:");
		scanf("%c",&Driction);									//接收命令
		People_Move(Driction);									//处理命令
	}
	Map_Victory();	//显示通关界面
	return 0;
}

void Map_Build()			//随机生成地图函数
{
	srand(time(0));
		
	do{	
		People.x=rand()%X_MAX;		//随机生成人的X坐标
		People.y=rand()%Y_MAX;		//随机生成人的Y坐标

		do{							//随机生成箱子的坐标，箱子不能处在地图边缘
			Box.x=rand()%X_MAX;
		}while(Box.x==0||Box.x==X_MAX-1);
		do{
			Box.y=rand()%Y_MAX;
		}while(Box.y==0||Box.y==Y_MAX-1);
	
		Destination.x=rand()%X_MAX;	//随机生成目的地的坐标
		Destination.y=rand()%Y_MAX;
	
	}while((People.x==Box.x && People.y==Box.y) ||
			(People.x==Destination.x && People.y==Destination.y) ||
			(Box.x==Destination.x && Box.y==Destination.y));	//如果三个坐标其中有两个坐标相等的话就重新生成

	for(int i=0;i<X_MAX;i++)		//将地图的所有坐标都初始化为'*'
	{
		for(int j=0;j<Y_MAX;j++)
		{
			map[i][j]='*';
		}
	}
	map[People.x][People.y]='P';		//把对应的人的坐标改为P
	map[Box.x][Box.y]='B';				//把对应的箱子的坐标改为B
	map[Destination.x][Destination.y]='D';		//把对应的目的地的坐标改为D
}

void Map_Display()		//显示地图
{
	for(int i=0;i<X_MAX;i++)
	{
		for(int j=0;j<Y_MAX;j++)
		{
			printf("%c ",map[i][j]);
		}
		printf("\n");
	}
}

void People_Move(char driction)			//处理用户输入的命令，4：左转，5：后退，6：右转，8：前进，q：quit退出
{
	switch(driction)
	{
		case '4':
			map[People.x][People.y]='*';		//先给人移动之前的坐标改为'*'
			if(People.x!=Box.x || People.y-1!=Box.y || Box.y!=0)		//一级条件为前面是箱子并且箱子处于地图边缘
				if(People.y!=0)					//二级条件为人处在墙壁的边缘
					People.y--;					//满足条件才能进行左移移动操作
			if(People.x==Box.x && People.y==Box.y)		//如果移动后人和箱子在同一坐标则将箱子进行移动
			{
				Box.y--;						//箱子左移操作
				map[Box.x][Box.y]='B';			//给箱子新坐标改成'B'
			}
			map[Destination.x][Destination.y]='D';//给目的地重新赋值'P'，防止人经过后变'*'
			map[People.x][People.y]='P';		//给人新坐标改成'P'
			break;
		case '6':
			map[People.x][People.y]='*';
			if(People.x!=Box.x || People.y+1!=Box.y || Box.y!=Y_MAX-1)
				if(People.y!=Y_MAX-1)
					People.y++;
			if(People.x==Box.x && People.y==Box.y)
			{
				Box.y++;
				map[Box.x][Box.y]='B';
			}
			map[Destination.x][Destination.y]='D';
			map[People.x][People.y]='P';
			break;
		case '8':
			map[People.x][People.y]='*';
			if(People.y!=Box.y || People.x-1!=Box.x || Box.x!=0)
				if(People.x!=0)
					People.x--;
			if(People.x==Box.x && People.y==Box.y)
			{
				Box.x--;
				map[Box.x][Box.y]='B';
			}
			map[Destination.x][Destination.y]='D';
			map[People.x][People.y]='P';
			break;
		case '5':
			map[People.x][People.y]='*';
			if(People.y!=Box.y || People.x+1!=Box.x || Box.x!=X_MAX-1)
				if(People.x!=X_MAX-1)
					People.x++;
			if(People.x==Box.x && People.y==Box.y)
			{
				Box.x++;
				map[Box.x][Box.y]='B';
			}
			map[Destination.x][Destination.y]='D';
			map[People.x][People.y]='P';
			break;
		case 'q':exit(0);
		default:
			printf("input error!\n");
	}
}

void Map_Victory()			//通关界面
{
	printf("\033[2J");
	for(int i=0;i<5;i++)
	printf("victory!\n");
}
