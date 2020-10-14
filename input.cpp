#include "input.h"

int last_ch;

bool input() {
    last_ch = getch();
    return last_ch == 'q';
}

int GetLastCh() {
    return last_ch;
}
