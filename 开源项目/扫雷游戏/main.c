#include "game.h"

menu()
{
	printf("*******************************\n");
	printf("****   欢迎来到扫雷游戏！  ****\n");
	printf("****      1.进入游戏       ****\n");
	printf("****      0.退出游戏       ****\n");
	printf("*******************************\n");
}

void game()
{
	char mine[ROWS][COLS] = { 0 }; //置放雷的棋盘
	char show[ROWS][COLS] = { 0 }; //展示给玩家的棋盘
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	ScMinc(mine, ROW, COL);        //置雷
	//DisplayBoard(mine, ROW, COL);  
	DisplayBoard(show, ROW, COL);
	FindMind(mine, show, ROW, COL);//排雷
}

void test()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("输入错误\n");
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}
