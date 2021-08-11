#include"game.h" 

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    initgame();


    signal(14, drawgame);

    struct itimerval itimer;
    itimer.it_interval.tv_sec = 0;
    itimer.it_interval.tv_usec = 100000;
    itimer.it_value.tv_sec = 0;
    itimer.it_value.tv_usec = 1000;
    setitimer(ITIMER_REAL, &itimer, NULL);

    Opoint.x = cx;
    Opoint.y = Y - 4;

    attron(COLOR_PAIR(4));
    gotoxy_putc(Opoint.x, Opoint.y, 'o');
    attroff(COLOR_PAIR(4));


    refresh();

    while(1) {
       int c = getch();
        switch(c) {
            case KEY_LEFT:
                Bdir.x -= 2;
                break;
            case KEY_RIGHT:
                Bdir.x += 2;
                break;
            case KEY_UP:
                if (flag) break;
                flag = 1;
                Odir.x = dir_r[get_random(12)];
                Odir.y = -1;
                char blank[] = "";
                gotoxy_puts(3, Y + 4, blank);
                gotoxy_puts(3, Y + 5, blank);
                break;
            default:
                break;
        }
    }

    getch();
    endwin();
    return 0;
}
