#include "roguelike.h"

int main() {
    // get ncurses going
    InitialiseRenderer();

    // vector containing all levels
    std::vector<Level> levels;

    // initialise first level
    levels.push_back(Level());

    // input character
    int ch;

    // game loop
    while (ch != 'q') {
        // render the level and the hud
        RenderLevel(levels[0]);
        RenderHud(&(levels[0].entities_[0]));

        // placeholder input stuff
        ch = getch();
        switch (ch) {
            case KEY_UP:
                levels[0].entities_[0].Move(-1, 0, levels[0].GetMap());
                AddHudMessage("Player Moved Up!");
                break;
            case KEY_DOWN:
                levels[0].entities_[0].Move(1, 0, levels[0].GetMap());
                AddHudMessage("Player Moved Down!");
                break;
            case KEY_LEFT:
                levels[0].entities_[0].Move(0, -1, levels[0].GetMap());
                AddHudMessage("Player Moved Left!");
                break;
            case KEY_RIGHT:
                levels[0].entities_[0].Move(0, 1, levels[0].GetMap());
                AddHudMessage("Player Moved Right!");
                break;
        }
    }

    // end ncurses
    endwin();

    // everything went perfectly :)
    return 0;
}
