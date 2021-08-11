#ifndef __minesweeper_H__
#define __minesweeper_H__

# define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ROW 9
#define COL 9

#define ROWS ROW+2
#define COLS COL+2

#define EASY_COUNT 10

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set);
void DisplayBoard(char board[ROWS][COLS], int row, int col);
void ScMinc(char board[ROWS][COLS], int row, int col);
void FindMind(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);
char FistStep(char mine[ROWS][COLS], int row, int col, int x, int y);

#endif __minesweeper_H__
