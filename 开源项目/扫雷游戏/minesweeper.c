#include "game.h"

//初始化棋盘
void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	memset(board, set, rows*cols*sizeof(board[0][0]));
}

//打印棋盘
void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("   ");
	for (i = 0; i < row; i++)
	{
		printf("  %d ", i + 1);
	}
	printf("\n");
	for (j = 0; j < col + 1; j++)
	{
		printf("---|");
	}
	printf("\n");
	for (i = 0; i < row; i++)
	{
		printf(" %d |", i + 1);
		for (j = 0; j < col; j++)
		{
			printf(" %c |", board[i][j]);
		}
		printf("\n");
		printf("   |", i + 1);
		for (j = 0; j < col; j++)
		{
			printf("---|");
		}
		printf("\n");
	}
	printf("\n");
}

//布置雷
void ScMinc(char board[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int count = EASY_COUNT;
	while (count)
	{
		x = rand() % 9 + 1;
		y = rand() % 9 + 1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}

//统计周围雷的个数
static int GetMineCount(char mine[ROWS][COLS], int x, int y)
{
	return mine[x - 1][y] +
		mine[x - 1][y - 1] +
		mine[x][y - 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] +
		mine[x][y + 1] +
		mine[x - 1][y + 1] - 8 * '0';
}

//用递归排除周围没有雷的区域
static void NoMine(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	int ret = GetMineCount(mine, x, y);
	if (ret == 0)
	{
		show[x][y] = ' ';
		if ((x - 1)>0 && (y - 1)>0 && (show[x - 1][y - 1] == '*'))
			NoMine(mine, show, x - 1, y - 1);
		if ((x - 1)>0 && (y)>0 && (show[x - 1][y] == '*'))
			NoMine(mine, show, x - 1, y);
		if ((x - 1)>0 && (y + 1)>0 && (show[x - 1][y + 1] == '*'))
			NoMine(mine, show, x - 1, y + 1);
		if ((x)>0 && (y - 1)>0 && (show[x][y - 1] == '*'))
			NoMine(mine, show, x, y - 1);
		if ((x)>0 && (y + 1)>0 && (show[x][y + 1] == '*'))
			NoMine(mine, show, x, y + 1);
		if ((x + 1)>0 && (y - 1)>0 && (show[x + 1][y - 1] == '*'))
			NoMine(mine, show, x + 1, y - 1);
		if ((x + 1)>0 && (y)>0 && (show[x + 1][y] == '*'))
			NoMine(mine, show, x + 1, y);
		if ((x + 1)>0 && (y + 1)>0 && (show[x + 1][y + 1] == '*'))
			NoMine(mine, show, x + 1, y + 1);
	}
	else
		show[x][y] = ret + '0';
}


//排雷
void FindMind(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int win = 0;  //统计不是雷的坐标数
	int ret = 0;  //统计周围雷的个数
	while (win < ROW*COL - EASY_COUNT)
	{
		int select = 0;
		system("CLS"); //清屏，优化界面
		DisplayBoard(show, ROW, COL);
		printf("----- 1.扫雷 --- 2.标记雷 -----\n");
		printf("请选择:>");
		scanf("%d", &select);
		if (select == 1)
		{
			printf("请输入要排查的坐标：>");
			scanf("%d %d", &x, &y);
			if (x >= 1 && x <= row && y >= 1 && y <= col)
			{
				if (mine[x - 1][y - 1] == '1' && show[x - 1][y - 1] == '*'&& win == 0)
				{
					InitBoard(mine, ROWS, COLS, '0');
					ScMinc(mine, ROW, COL);
					win++;
				}
				if (mine[x - 1][y - 1] == '0' && show[x - 1][y - 1] == '*')
				{
					NoMine(mine, show, x - 1, y - 1);
					DisplayBoard(show, ROW, COL);
					win = win + 8;
				}
				if (mine[x - 1][y - 1] == '1' && show[x - 1][y - 1] == '*' && win != 0)
				{
					show[x - 1][y - 1] = 'S';
					DisplayBoard(show, ROW, COL);
					printf("很遗憾，你被炸死了\n\n");
					DisplayBoard(mine, row, col);
					break;
				}
			}
			else
			{
				printf("坐标非法\n");
			}
		}

		if (select == 2)
		{
			printf("请输入要标记雷的坐标：>");
			scanf("%d %d", &x, &y);
			if (show[x - 1][y - 1] == '*')
			{
				show[x - 1][y - 1] = '@'; //用于玩家标记已经确定的雷
				DisplayBoard(show, ROW, COL);
			}
			else
			{
				printf("坐标非法\n");
			}
		}
	}
	if (win > ROW*COL - EASY_COUNT)
	{
		printf("恭喜你，排雷成功！\n");
		DisplayBoard(mine, row, col);
	}
}
