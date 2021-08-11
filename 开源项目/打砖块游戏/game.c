#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define MAX_X	60
#define MAX_Y	20

typedef struct _ball_information{
	unsigned int vdir:1;
	unsigned int hdir:1;
	unsigned int invincible:1;
	int score;
	int target;
	int speed;
	struct _ball_position{
		int x;
		int y;
	} pos;
} ball_inf;

typedef struct _board_information{
	int len;
	int speed;
	struct _board_position{
		int x;
		int y;
	} pos;
	char printlen[];	//动态数组用于代替for循环输出从而避免闪屏的情况
} board_inf;

typedef struct _blocks_position_information{
	int x;
	int y;
	struct _blocks_position_information *last;
	struct _blocks_position_information *next;
} bpi;

int map_init();
ball_inf *ball_information_init();
board_inf *board_information_init(int posx);
bpi *generate_block(int nums);
void ball_move(ball_inf *bai, board_inf *bdi, bpi *brpi);
void board_move(board_inf *bdi);
void refresh_score(ball_inf *bai);
void help();
void gotoxy(int x, int y);

int main()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	SetConsoleTitle("Break_the_Bricks");
	map_init();
	srand((unsigned) time(NULL));
	ball_inf *bai = ball_information_init();
	board_inf *bdi = board_information_init(bai->pos.x);
	refresh_score(bai);
	bpi *bpi = generate_block(5);
	int xs = bai->speed;
	while("Enjoy :)")
	{
		xs--;
		if(!xs)
			ball_move(bai, bdi, bpi);
		if(xs<=0)
			xs = bai->speed;
		board_move(bdi);
		Sleep(bdi->speed);
	}
	getch();
}

//初始化地图
int map_init()
{
	for(int i=0;i<MAX_Y+2;i++)
	{
		for(int j=0;j<MAX_X/2+2;j++)
		{
			if(i==0 || i==MAX_Y+1)
				printf("■");
			else
			{
				if(j==0 || j==MAX_X/2+1)printf("■");
				else printf("  ");
			}
		}
		printf("\n");
	}
	gotoxy(MAX_X+3,3);
	printf("###############");
	gotoxy(MAX_X+3,4);
	printf("#  Score:     #");
	gotoxy(MAX_X+3,5);
	printf("###############");
	help();
	return 1;
}

ball_inf *ball_information_init()
{
	ball_inf *bai = (ball_inf*)malloc(sizeof(struct _ball_information));
	bai->invincible = 0;				//是否无敌
	bai->pos.x = rand()%(MAX_X-1)+2;
	bai->pos.y = MAX_Y;
	bai->speed = 3;						//球的速度
	bai->vdir = rand()%2;
	bai->hdir = rand()%2;
	bai->score = 0;
	bai->target = 100;					//游戏目标
	bai->score--;
	return bai;
}

board_inf *board_information_init(int posx)
{
	int len = 7;
	board_inf *bdi = (board_inf*)malloc(sizeof(struct _board_information)+sizeof(char)*(len+1));
	bdi->len = len;
	if(posx > MAX_X-bdi->len)
		posx = MAX_X-bdi->len;
	bdi->speed = 20;					//游戏速度
	bdi->pos.x = posx;
	bdi->pos.y = MAX_Y;
	bdi->printlen[len] = '\0';
	gotoxy(bdi->pos.x,bdi->pos.y);
	for(int i=0;i<bdi->len;i++)
		printf("_");
	return bdi;
}

bpi *generate_block(int nums)
{
	if(nums<=0 || nums>MAX_X*(MAX_Y-5)) return NULL;
	bpi *ret,*tmp;
	ret = (bpi*)malloc(sizeof(struct _blocks_position_information));
	ret->x = 1;
	ret->y = 1;
	ret->last = NULL;
	ret->next = NULL;
	gotoxy(ret->x,ret->y);
	printf("#");
	tmp = ret;
	for(int i=1;i<nums+1;i++)
	{
		for(int j=1;j<MAX_X+1;j++)
		{
			if(i==1 && j==1) continue;
			tmp->next = (bpi*)malloc(sizeof(struct _blocks_position_information));
			tmp->next->last = tmp;
			tmp = tmp->next;
			tmp->x = j;
			tmp->y = i;
			gotoxy(tmp->x,tmp->y);
			printf("#");
			tmp->next = NULL;
		}
	}
	return ret;
}

void ball_move(ball_inf *bai, board_inf *bdi, bpi *brpi)
{
	gotoxy(bai->pos.x,bai->pos.y);
	printf(" ");

	int h = bai->hdir;
	int v = bai->vdir;
	bpi *tmp = brpi;
	if(v)
		while(tmp->next != NULL)
			tmp = tmp->next;
	while(tmp != NULL)
	{
		if(bai->pos.x == tmp->x)
		{
			if(bai->pos.y-1 == tmp->y)
				bai->hdir = 0;
			else if(bai->pos.y+1 == tmp->y)
				bai->hdir = 1;
		}
		else if(bai->pos.y == tmp->y)
		{
			if(bai->pos.x-1 == tmp->x)
				bai->vdir = 0;
			else if(bai->pos.x+1 == tmp->x)
				bai->vdir = 1;
		}
		else if(bai->pos.y+1 == tmp->y && !bai->hdir)
		{
			if(bai->pos.x-1 == tmp->x && bai->vdir)
			{
				bai->vdir = 0;
				bai->hdir = 1;
			}
			else if(bai->pos.x+1 == tmp->x && !bai->vdir)
				bai->vdir = bai->hdir = 1;
		}
		else if(bai->pos.y-1 == tmp->y && bai->hdir)
		{
			if(bai->pos.x-1 == tmp->x && bai->vdir)
				bai->vdir =bai->hdir = 0;
			else if(bai->pos.x+1 == tmp->x && !bai->vdir)
			{
				bai->vdir = 1;
				bai->hdir = 0;
			}
		}
		if(h!=bai->hdir || v!=bai->vdir)
		{
			gotoxy(tmp->x,tmp->y);
			printf(" ");
			if(tmp->last == NULL)
			{
				brpi = tmp;
				if(brpi->next != NULL)
				{
					brpi->next->last = brpi;
					brpi->last = NULL;
				}
			}
			else
			{
				tmp->last->next = tmp->next;
				if(tmp->next != NULL)
					tmp->next->last = tmp->last;
			}
			free(tmp);
			refresh_score(bai);
			break;
		}
		tmp = v?tmp->last:tmp->next;
	}

	if(bai->pos.x <= 1)
		bai->vdir = 0;
	else if(bai->pos.x >= MAX_X)
		bai->vdir = 1;
	if(bai->pos.y <= 1)
		bai->hdir = 0;
	else if(bai->pos.y >= MAX_Y)
		bai->hdir = 1;

	if(bai->vdir)
		bai->pos.x--;
	else
		bai->pos.x++;
	if(bai->hdir)
		bai->pos.y--;
	else
		bai->pos.y++;

	gotoxy(bai->pos.x,bai->pos.y);
	printf("*");

	if((bai->pos.x < bdi->pos.x || bai->pos.x > bdi->pos.x+bdi->len-1) && bai->pos.y == MAX_Y)
	{
		if(bai->invincible) return;
		gotoxy(MAX_X/2-8,MAX_Y/2-1);
		printf(" ############# ");
		gotoxy(MAX_X/2-8,MAX_Y/2);
		printf(" # You Lose! # ");
		gotoxy(MAX_X/2-8,MAX_Y/2+1);
		printf(" ############# ");
		Sleep(3000);
		getch();
		exit(0);
	}
	else if(bai->pos.y == MAX_Y-1)
	{
		gotoxy(bdi->pos.x,bdi->pos.y);
		memset(bdi->printlen,'_',bdi->len);
		printf("%s",bdi->printlen);
	}

	if(bai->target <= bai->score)
	{
		gotoxy(MAX_X/2-8,MAX_Y/2-1);
		printf(" ############# ");
		gotoxy(MAX_X/2-8,MAX_Y/2);
		printf(" # You Win!  # ");
		gotoxy(MAX_X/2-8,MAX_Y/2+1);
		printf(" ############# ");
		Sleep(3000);
		getch();
		exit(0);
	}
}

void board_move(board_inf *bdi)
{
	int x = bdi->pos.x;
	int y = bdi->pos.y;
	if(kbhit())
	{
		if(GetKeyState(65)<0 && bdi->pos.x > 1)
			bdi->pos.x--;
		if(GetKeyState(68)<0 && bdi->pos.x < MAX_X-bdi->len+1)
			bdi->pos.x++;
		if(GetKeyState(VK_SPACE)<0)
			system("pause>nul");
	}
	if(x == bdi->pos.x && y == bdi->pos.y)
		return;
	gotoxy(x,y);
	memset(bdi->printlen,' ',bdi->len);
	printf("%s",bdi->printlen);
	gotoxy(bdi->pos.x,bdi->pos.y);
	memset(bdi->printlen,'_',bdi->len);
	printf("%s",bdi->printlen);
}

void refresh_score(ball_inf *bai)
{
	bai->score++;
	gotoxy(MAX_X+12,4);
	printf("%3d",bai->score);
	gotoxy(MAX_X+3,7);
	printf("Target: %d",bai->target);
}

void help()
{
	gotoxy(MAX_X+3,11);
	printf("Control key:");
	gotoxy(MAX_X+8,13);
	printf("a  d");
	gotoxy(MAX_X+3,15);
	printf("Pause:");
	gotoxy(MAX_X+6,16);
	printf("Space key");
}

void gotoxy(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x+1,y});
}
