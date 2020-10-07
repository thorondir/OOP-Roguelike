#include "roguelike.h"

int main() {
    // get ncurses going
    InitialiseRenderer();

    // vector containing all levels
    std::vector<Level> levels;

    // initialise first level
    levels.push_back(Level());

    // create the player entity reference
    Player* player = new Player(
            (levels[0].GetRooms()[0].GetY1() + levels[0].GetRooms()[0].GetY2())/2,
            (levels[0].GetRooms()[0].GetX1() + levels[0].GetRooms()[0].GetX2())/2);
    // put the player into the first level
    levels[0].entities_.push_back(player);

    // input character
    int ch;

    // game loop
    while (ch != 'q') {
        // render the level and the hud
        RenderLevel(levels[0]);
        RenderHud(levels[0].entities_[0]);

        // placeholder input stuff
        ch = getch();
        switch (ch) {
            case KEY_UP:
                player->Move(-1, 0, levels[0].GetMap());
                AddHudMessage("Player Moved Up!");
                break;
            case KEY_DOWN:
                player->Move(1, 0, levels[0].GetMap());
                AddHudMessage("Player Moved Down!");
                break;
            case KEY_LEFT:
                player->Move(0, -1, levels[0].GetMap());
                AddHudMessage("Player Moved Left!");
                break;
            case KEY_RIGHT:
                player->Move(0, 1, levels[0].GetMap());
                AddHudMessage("Player Moved Right!");
                break;
        }
    }
    levels[0].entities_[0] = nullptr;
    levels[0].FreeEntities();
    // end ncurses
    endwin();

    // everything went perfectly :)
    return 0;
}
