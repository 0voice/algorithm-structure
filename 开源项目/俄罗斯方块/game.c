#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

int moveI = 3;	//向上移动一格，自增1
int moveJ = -4;	//向左移动一格，自增1

int board[21][11] = {0};
int presentGraph[4][4] = { 0 };
int graph[6][4][4] = { 
	{ 0, 0, 1, 0,
	  0, 0, 1, 0,
	  0, 0, 1, 0,
	  0, 0, 1, 0 },
	{ 0, 0, 0, 0,
	  0, 0, 0, 0,
	  1, 1, 1, 1,
	  0, 0, 0, 0 },
	{ 0, 1, 0, 0,
	  0, 1, 0, 0,
	  0, 1, 1, 0,
	  0, 0, 0, 0 },
	{ 0, 0, 0, 0,
	  0, 0, 1, 0,
	  1, 1, 1, 0,
	  0, 0, 0, 0 },
	{ 0, 0, 0, 0,
	  0, 1, 1, 0,
	  0, 0, 1, 0,
	  0, 0, 1, 0 },
	{ 0, 0, 0, 0,
	  0, 1, 1, 1,
	  0, 1, 0, 0,
	  0, 0, 0, 0 } 
};

void initGame(void);
void printBoard(void);
void randGraph(void);
void copyGraph(int *, int *);
int isCrash(void);
void copyValue(void);
void rotateGraph(void);
void moveGraph(char);

int main(void)
{
	initGame();

	while (1)
	{
		randGraph();
		while (1)
		{
			Sleep(500);

			if (kbhit())
			{
				moveGraph(getch());
			}

			if (isCrash())
			{
				copyValue();
				moveI = 3;
				moveJ = -4;
				break;
			}
			moveI--;
			printBoard();
		}
	}

	return 0;
}

void initGame(void)
{
	printBoard();
}

void printBoard(void)
{
	int i, j;

	system("cls");

	printf("┌──────────┐\n");
	for (i = 1; i <= 20; i++)
	{
		for (j = 0; j <= 11; j++)
		{
			if (0 == j)
			{
				printf("│");
			}
			else if (11 == j)
			{
				printf("│\n");
			}
			else if (moveI + i >= 0 && moveI + i <= 3 && moveJ + j >= 0 && moveJ + j <= 3 && 1 == (board[i][j] + presentGraph[moveI + i][moveJ + j]))
			{
				printf("▇");
			}
			else if (1 == board[i][j])
			{
				printf("▇");
			}
			else
			{
				printf("  ");
			}
		}
	}
	printf("└──────────┘");
}

void randGraph(void)
{
	int t;

	srand(time(0) * 1999);
	t = (int)(rand() / (RAND_MAX + 1.0) * 6);

	copyGraph(presentGraph, graph[t]);
}

void copyGraph(int * a, int * b)
{
	int i;

	for (i = 0; i < 16; i++)
	{
		a[i] = b[i];
	}

	return;
}

int isCrash(void)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (i + 1 - moveI >= 1 && i + 1 - moveI <= 20 && j - moveJ >= 1 && j - moveJ <= 10 && 2 == (presentGraph[i][j] + board[i + 1 - moveI][j - moveJ]))
			{
				return 1;
			}
			else if (1 == presentGraph[i][j] && 20 == i - moveI)
			{
				return 1;
			}
		}
	}

	return 0;
}

void copyValue(void)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (i - moveI >= 1 && i - moveI <= 20 && j - moveJ >= 1 && j - moveJ <= 10 && 1 == presentGraph[i][j])
			{
				board[i - moveI][j - moveJ] = presentGraph[i][j];
			}
		}
	}
}

void rotateGraph(void)
{
	int i, j;
	int tempGraph[4][4];

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			tempGraph[i][j] = presentGraph[j][3 - i];
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			presentGraph[i][j] = tempGraph[i][j];
		}
	}
}

void moveGraph(char ch)
{
	int i, j;

	switch (ch)
	{
	case 'a':
	case 'A':
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (1 == presentGraph[i][j] && 1 == j - moveJ)
				{
					return;
				}
			}
		}
		moveJ++;
		break;

	case 'd':
	case 'D':
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (1 == presentGraph[i][j] && 10 == j - moveJ)
				{
					return;
				} 
			}
		}
		moveJ--;
		break;

	case 'w':
	case 'W':
		rotateGraph();
		break;
	}
}
