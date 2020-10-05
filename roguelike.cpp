#include "roguelike.h"

int main() {
    InitialiseRenderer();

    std::vector<Level> levels;

    levels.push_back(Level());

    int ch;

    while (ch != 'q') {
        RenderLevel(levels[0]);
        RenderHud(&(levels[0].entities_[0]));

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

    endwin();

    return 0;
}
