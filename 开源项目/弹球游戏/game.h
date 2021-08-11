#ifndef _GAME_H
#define _GAME_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <curses.h>
#include <string.h>
#include <stdint.h>
#define X 70
#define Y 20

struct point {
    int x;
    int y;
};


struct point Bpoint;
struct point Opoint;
struct point Bdir, Odir;


int cx = (X - 2) / 2 + 1;
int cy = (Y - 2) / 2 + 1;

int dir_r[] = {-1, 0, 1, -1, -1, -1, 0, 1, -1, 1, 1, 0, 1};

int flag = 0;
int score = 0;

uint32_t get_random(uint32_t max) {
    uint32_t value;
    srand((unsigned)time(NULL));
    value = rand() % (max + 1);
    return value;
}



void gotoxy(int x, int y) {
    move(y, x);
}

void gotoxy_putc(int x, int y, char c) {
    mvaddch(y, x, c);
    move(LINES - 1, 1);
    refresh();

}
void gotoxy_puts(int x, int y, char *c) {
    mvaddstr(y, x, c);
    move(LINES - 1, 1);
    refresh();
}
void initfield(int x, int y) {
    mvaddch(0, 0, '0');
    //mvaddch(0, X, 'X');
    gotoxy_putc(X + 2, 0, 'X');
    //mvaddch(Y, 0, 'Y');
    gotoxy_putc(0, Y + 2, 'Y');
    attron(COLOR_PAIR(1));
    for(int i = 1; i <= X; i++) {
        gotoxy_putc(i, 1, '-');
        gotoxy_putc(i, y, '-');
    }
    for(int i = 1; i <= y; i++) {
        gotoxy_putc(1, i, '|');
        gotoxy_putc(X, i, '|');
    }
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(4));
    gotoxy_puts(2, Y+ 3, "Message:");
    gotoxy_puts(X + 3, 2, "Help:");
    attroff(COLOR_PAIR(4));

}


void initgame() {
    if (!has_colors() || start_color() == ERR) {
        endwin();
        fprintf(stderr, "终端不支持颜色！\n");
        exit(1);
    }
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    initfield(X, Y);

    Bpoint.x = cx - 3;
    Bpoint.y = Y - 3;
    attron(COLOR_PAIR(3));
    for (int i = 0; i < 8; i++) {
        gotoxy_putc(Bpoint.x + i, Bpoint.y, ' ');
        gotoxy_putc(Bpoint.x + i, Bpoint.y + 1, ' ');
    }
    attroff(COLOR_PAIR(3));
    refresh();
    

}

void drawgame() {
    gotoxy_putc(Opoint.x, Opoint.y, ' ');

    
    if (!flag) {
        Opoint.x = Bpoint.x + 4;
    }

    if (flag) {
        Opoint.x += Odir.x;
        Opoint.y += Odir.y;
    }

    if (Opoint.x > X - 1) {
        Opoint.x = X - 1;
        Odir.x = -1;
        x:Odir.y = dir_r[get_random(12)];
        if (Odir.y == 0) goto x;
        
        
    }
    if (Opoint.x <= 2) {
        Opoint.x = 2;
        Odir.x = 1;
        y:Odir.y = dir_r[get_random(12)];
        if (Odir.y == 0) goto y;
    }

    if (Opoint.y <= 1) {
        Opoint.y = 2;
        Odir.y = 1;
        Odir.x = dir_r[get_random(12)];
    }
    if (Opoint.y >= Y - 1) {
        char info[1024] = {0};
        sprintf(info, "GameOver! Score = %d!", score);
        gotoxy_puts(3, Y + 5, info);
        flag = 0;
        score = 0;
        Opoint.x = cx;
        Opoint.y = Y - 4;
        
        for (int i = 0; i < 8; i++) {
            gotoxy_putc(Bpoint.x + i, Bpoint.y, ' ');
            gotoxy_putc(Bpoint.x + i, Bpoint.y + 1, ' ');
        }
        Bpoint.x = cx - 3;
        Bpoint.y = Y - 3;
    }

    attron(COLOR_PAIR(4));
    gotoxy_putc(Opoint.x, Opoint.y, 'O');
    attroff(COLOR_PAIR(4));


    attron(COLOR_PAIR(2));
    for (int i = 0; i < 8; i++) {
        gotoxy_putc(Bpoint.x + i, Bpoint.y, ' ');
        gotoxy_putc(Bpoint.x + i, Bpoint.y + 1, ' ');
    }
    attroff(COLOR_PAIR(2));
    Bpoint.x += Bdir.x;
    Bpoint.y += Bdir.y;
    
    memset(&Bdir, 0, sizeof(Bdir));

    if (Bpoint.x >= X - 8) Bpoint.x = X - 8;
    if (Bpoint.x <= 2) Bpoint.x = 2;
    
    
    attron(COLOR_PAIR(3));
    for (int i = 0; i < 8; i++) {
        gotoxy_putc(Bpoint.x + i, Bpoint.y, ' ');
        gotoxy_putc(Bpoint.x + i, Bpoint.y + 1, ' ');
    }
    attroff(COLOR_PAIR(3));
   
    if (flag && Opoint.x <= Bpoint.x + 8 && Opoint.x >= Bpoint.x && Opoint.y >= Y - 4) {
        score += 100;
        Odir.y = -1;
        Odir.x = dir_r[get_random(12)];
        char info[1024] = {0};
        sprintf(info, "You get %d, Total %d !", 100, score);
        gotoxy_puts(3, Y + 4, info);
    }
}

#endif
