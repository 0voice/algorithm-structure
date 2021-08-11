#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#define WIDES 30
#define COLS 25
static int speed = 0;
DWORD starttime;
DWORD START;
int flash;
typedef struct a
{
	int EmyNum;//敌军最大数量
	int EmyPos[COLS][WIDES];//敌军位置
	int AmmoPos[COLS][WIDES];//子弹位置
	int Pos[2];//我军位置X,Y
	int EmySpeed;//敌人下落速度
	int AmmoSpeed;//子弹速度
	int GenSpeed;//敌人产生速度
	int MoveSpeed;//移动速度
	int score;//分数
}setting;
typedef struct b
{
	int MapSize[COLS][WIDES];//-1代表敌人，1代表我方，0为空格，2代表炮弹 4代表击中
	int MapBefore[COLS][WIDES];
}map;
int tick(int interVal)
{
	DWORD time = GetTickCount();
	if (START - time  %  interVal==0)
		return 1;
	else
		return 0;
}
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void GenEmy(setting* dat)//生成敌人
{
	int i = 0, x = 0;
	x = rand();
	for (i = 0; i < WIDES-1; i++)
		dat->EmyPos[1][i] = 0;
	for (i = 0; i < x % (dat->EmyNum); i++)
		dat->EmyPos[1][rand() % WIDES-1] = -1;
}
void datchng(map* start, setting* dat)//数据改变
{
	int i = 0, j = 0;
	if (tick(dat->GenSpeed))//产生敌人时钟控制
		GenEmy(dat);
	if (tick(dat->EmySpeed))      // 敌人移动时钟控制
	{
		flash = 1;
		for (i = COLS - 1; i >= 0; i--)
		{
			for (j = WIDES - 1; j >= 0; j--)
			{
				//Sleep(300);
				if (i == COLS - 1)//敌机到底
				{
					if (dat->EmyPos[i][j] == -1)
					{
						dat->EmyPos[i][j] = 0;
						dat->score--;
					}
				}
				else
				{
					if (dat->EmyPos[i][j] == -1)
					{
						dat->EmyPos[i][j] = 0; dat->EmyPos[i + 1][j] = -1;
					}
				}
			}
		}
	}
	else flash = 0;
	if (tick(dat->AmmoSpeed))  //子弹时钟控制
	{
		flash = 1;
		for (i = 0; i < COLS; i++)
		{
			for (j = 0; j < WIDES; j++)
			{
				//Sleep(300);
				if (i == 0)//子弹到顶
				{
					if (dat->AmmoPos[i][j] == 2)
					{
						dat->AmmoPos[i][j] = 0;
					}
				}
				else
				{
					if (dat->AmmoPos[i][j] == 2)
					{
						dat->AmmoPos[i][j] = 0; dat->AmmoPos[i - 1][j] = 2;
					}
				}
			}
		}
	}
	else flash = 0;
	if(flash==1)
	for (i = 1; i < COLS-1; i++)   //地图叠加合成
	{
		for (j = 1; j < WIDES-1; j++)
		{
			//Sleep(300);
			//地图数据备份
			start->MapBefore[i][j] = start->MapSize[i][j];
			if (dat->EmyPos[i][j] +3 == dat->AmmoPos[i][j])
			{
				dat->score++;
				dat->AmmoPos[i][j] = 0;
				dat->EmyPos[i][j] = 0;
				start->MapSize[i][j] = 0;
				
			}
			if (start->MapSize[i][j] == -1 || start->MapSize[i][j] == 2)
				start->MapSize[i][j] = 0;
			if (dat->AmmoPos[i][j] == 2)
				start->MapSize[i][j] = 2;
			if (dat->EmyPos[i][j] == -1)
				start->MapSize[i][j] = -1;
		}
	}
}
void print(map* start, setting* dat)
{
	int i = 0, j = 0;

	for (i = 2; i < COLS-1; i++)
	{
		for (j = 1; j < WIDES-1; j++)
		{
			if (start->MapSize[i][j] != start->MapBefore[i][j])
			{
				switch (start->MapSize[i][j])
				{
				case 2:gotoxy(j, i); printf("|"); break;
				case -1:gotoxy(j, i ); printf("e"); break;
				case 1:gotoxy(j, i ); printf("$"); break;
				default:gotoxy(j, i); printf(" ");
				}
			}
		}
	} 
	gotoxy(WIDES + 1, COLS / 2-7);
	printf("X: %02d  Y: %02d", dat->Pos[1], dat->Pos[0]);
	gotoxy(WIDES + 1, COLS / 2-6);
	printf("Score:  %03d", dat->score);
}
void init(map *start, setting* dat)//初始化数据
{
	int i = 0, j = 0;
	dat->Pos[0] = COLS - 2;
	dat->Pos[1] = WIDES / 2;
	starttime = GetTickCount();
	system("mode con  cols=50 lines=25");
	for (i = 1; i < COLS-1; i++)//界面搭建
	{
		gotoxy(WIDES + 15, i);
		printf("|");
	}
	for (i = WIDES; i <WIDES + 15; i++)//界面搭建
	{
		gotoxy(i,0);
		printf("-");
		gotoxy(i,COLS-1);
		printf("-");
	}
	gotoxy(WIDES, COLS/2-2); printf("游戏状态：");
	gotoxy(WIDES + 2, COLS/2);printf("开始！");
	gotoxy(WIDES , COLS / 2 + 3); printf("操作方法：");
	gotoxy(WIDES + 1, COLS / 2 + 6); printf("方向键操作战机");
	gotoxy(WIDES + 1, COLS / 2 + 7); printf("空格开火");
	gotoxy(WIDES + 1, COLS / 2 + 8); printf("F2暂停");
	for (i = 0; i < WIDES; i++)
		for (j = 0; j < COLS; j++)
		{
			if (i == 0 || i == WIDES - 1)
			{
				gotoxy(i, j); printf("|");
			}//侧边框
			if (j == 0||j == COLS - 1)
			{
				gotoxy(i, j); printf("-");//顶边框//底边框
			}
			start->MapSize[j][i] = 0;
			start->MapBefore[j][i] = 0;
			dat->AmmoPos[j][i] = 0;
			dat->EmyPos[j][i] = 0;
		}
	start->MapSize[dat->Pos[0]][dat->Pos[1]] = 1;
	dat->EmyNum = 3;
	dat->EmySpeed =16;
	dat->AmmoSpeed = 1;
	dat->GenSpeed = 1;
	dat->MoveSpeed = 1;
	dat->score = 0;
}
void moveshoot(map *start, setting *dat)//移动
{
	//speed++;                     //时钟
	//if (speed == 1000)speed = 0;
	if (tick(dat->MoveSpeed))
	{
		start->MapSize[dat->Pos[0]][dat->Pos[1]] = 0;
		if (GetAsyncKeyState(VK_UP) && dat->Pos[0] != 1) dat->Pos[0]--;
		if (GetAsyncKeyState(VK_LEFT) && dat->Pos[1] != 1)dat->Pos[1]--;
		if (GetAsyncKeyState(VK_DOWN) && dat->Pos[0] != COLS - 2)dat->Pos[0]++;
		if (GetAsyncKeyState(VK_RIGHT) && dat->Pos[1] != WIDES - 2)dat->Pos[1]++;
		if (GetAsyncKeyState(VK_SPACE))dat->AmmoPos[dat->Pos[0] - 1][dat->Pos[1]] = 2;
		start->MapSize[dat->Pos[0]][dat->Pos[1]] = 1;
	}
}
int main()
{
	DWORD time = 0;
	map start;
	setting dat;
	init(&start, &dat);
	while (1)
	{
		if(GetKeyState(VK_F2) < 0)
		{
			gotoxy(WIDES+2, COLS / 2 );
			printf("暂停!");
			while (1)
			{
				if (GetKeyState(VK_F2) > 0)
				{
					gotoxy(WIDES + 2, COLS / 2);
					printf("开始！");
					break;
				}
			}
		}
		starttime = GetTickCount();
		//if (flash == 1)
		print(&start, &dat);
		time = GetTickCount();
		if (time - starttime  <1000 / 20) //帧率控制  20FPS
		{
			Sleep(1000 / 20 - (time - starttime));
		}
		datchng(&start, &dat);
		moveshoot(&start, &dat);
		if (0)
		{
			system("cls");
			gotoxy(WIDES / 2, COLS / 2);
			printf("You Died!");
			Sleep(2000);
			break;
		}
	}
	return 0;
