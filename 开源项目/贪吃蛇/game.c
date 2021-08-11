//▇ ：用于组成蛇身的符号

# include <stdio.h>
# include <stdlib.h>
# include <windows.h>
# include <time.h>
# include <conio.h>


# define INIT_LENGTH 4		//蛇初始化的长度
# define DEBUG 0


char direction = 'd';		//纪录蛇移动的方向，a——左，w——上，d——右，s——下
int length = 0;		//纪录蛇的长度

/* 用于表示组成蛇身的点的结构体 */
typedef struct body
{
	int x;
	int y;
}body_t, * pBody_t;

body_t snake[300];		//用于储存蛇身的数组
body_t randPoint = { 0, 0 };		//储存随机出现的点


void init_game(void);
void print_snake(void); 
void gotoxy(int x, int y);
void rand_point(void);
void move_snake(void);


int main(void)
{
	int speed = 0;
	char tmpDirection = 0;
	body_t tmpBody = { 0, 0 };

	
	system("mode con cols=40 lines=20");
	while (1)
	{
		printf("请选择游戏级别（1~9,9的难度最高）：");
		scanf("%d", &speed);
		if (speed <= 9 && speed >= 1)
			break;
	}
	
	speed = 1000 - speed * 100;

	init_game();	//初始化游戏

	/* 游戏的主要部分 */
	while (1)
	{

		/* 用作调试时显示随机点的坐标 */
#if DEBUG
		gotoxy(1, 1);
		printf("%d,%d", randPoint.x, randPoint.y);
#endif

		Sleep(speed);		//用于控制蛇移动的速度

		/* 键盘操控方向 */
		if (kbhit())
		{
		
			tmpDirection = getch();

			/* 条件判断是否按键为w，a，s，d，且蛇不会回头 */
			if (('w' == tmpDirection || 's' == tmpDirection || 'a' == tmpDirection || 'd' == tmpDirection) && 'w' + 's' != tmpDirection + direction && 'a' + 'd' != tmpDirection + direction)
			{
				direction = tmpDirection;
			}

		}


		/* 蛇头与随机点重合 */
		if (randPoint.x == snake[1].x && randPoint.y == snake[1].y)
		{
			tmpBody = snake[length];
			system("cls");
			move_snake();

			snake[length + 1] = tmpBody;
			gotoxy(snake[length + 1].x, snake[length + 1].y);
			printf("▇");
			length++;

			rand_point();
		}
		else
		{
			system("cls");
			move_snake();
		}

	}
	
	
	getchar();
	return 0;
}



void init_game(void)
{
	int i = 0;
	
	/* 生成一条长度为4的小蛇 */
	for(i = 1; i <= 4; i++)
	{
		snake[i].x = 21 - i * 2;
		snake[i].y = 10;
	}
	length = INIT_LENGTH;
	print_snake();
	
	/* 随机生成一个点 */ 
	rand_point();
}

/* 利用gotoxy函数打印出蛇 */
void print_snake(void)
{
	int i = 0;
	
	for(i = 1; i <= length; i++)
	{
		gotoxy(snake[i].x, snake[i].y);
		printf("▇");
	}
}

/* 直接从别人那儿拿来用了，看不懂~~~~(>_<)~~~~ */
void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


/* 生成随机点， 随机种子为 当前时间 x 189 */
void rand_point(void)
{
	int i = 0;

	srand((int)time(0) * 182);

	/* 判断随机生成的点是否与蛇身重合，若重合，则重新生成 */
	while (1)
	{
		randPoint.x = (int)(20 * rand() / RAND_MAX) * 2 + 1;
		randPoint.y = (int)(20 * rand() / RAND_MAX) + 1;

		for (i = 1; i <= length; i++)
		{
			if (snake[i].x == randPoint.x && snake[i].y == randPoint.y)
				break;
		}

		if (i > length)
			break;
	}

	gotoxy(randPoint.x, randPoint.y);
	printf("▇");

}

/* 移动，程序中最重要的部分 */
void move_snake(void)
{
	int i = 0;

	/* 将蛇身上每个点的值赋给下一个点 */
	for (i = length; i >= 2; i--)
	{
		snake[i] = snake[i - 1];
	}

	/* 蛇头向当前方向移动一格 */
	switch (direction)
	{
	case 'w':snake[1].y -= 1; break;		//上
	case 's':snake[1].y += 1; break;	//下
	case 'a':snake[1].x -= 2; break;		//左
	case 'd':snake[1].x += 2; break;	//右
	}

	/* 判断是否撞到墙 */
	if (-1 == snake[1].x || 41 == snake[1].x || 0 == snake[1].y || 21 == snake[1].y)
	{
		system("cls");
		gotoxy(15, 10);
		printf("GAME OVER!\n");
		getch();
		getch();
		exit(-1);
	}

	/* 判断是否咬到自己 */
	for (i = 5; i <= length; i++)
	{
		if (snake[i].x == snake[1].x && snake[i].y == snake[1].y)
		{
			system("cls");
			gotoxy(15, 10);
			printf("GAME OVER!\n");
			getchar();
			exit(-1);
		}
	}

	print_snake();
	gotoxy(randPoint.x, randPoint.y);
	printf("▇");
}
