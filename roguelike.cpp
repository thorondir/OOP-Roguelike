#include "roguelike.h"
#include "player.h"

int main() {
    // this all placeholder testing stuff
    int x,y,ch;
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();

    getmaxyx(stdscr, y, x);
    Player player(y/2, x/2);
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    bkgd(' ' | COLOR_PAIR(0));

    while (ch != 'q') {
        wclear(stdscr);
        mvaddch(player.GetY(),  player.GetX(), player.GetAvatar());
        refresh();
        ch = getch();
        switch (ch) {
            case KEY_UP:
                player.Move(-1,0);
                break;
            case KEY_DOWN:
                player.Move(1,0);
                break;
            case KEY_LEFT:
                player.Move(0,-1);
                break;
            case KEY_RIGHT:
                player.Move(0,1);
                break;
        }
    }

    endwin();

    return 0;
}
