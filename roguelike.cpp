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

    std::array<std::array<bool, kMapWidth>, kMapHeight> transparentmap;

    for (int y = 0; y < kMapHeight; y++) {
        for (int x = 0; x < kMapWidth; x++) {
            transparentmap[y][x] = levels[0].map_[y][x].transparent;
        }
    }

    player->UpdateFOVTransparent(transparentmap);

    // input character
    int ch;

    // game loop
    while (ch != 'q') {
        // render the level and the hud
        std::vector<std::vector<bool>> visible = player->GetFOV();

        for (int y = 0; y < kMapHeight; y++) {
            for (int x = 0; x < kMapWidth; x++) {
                if (visible[y][x]) {
                    levels[0].map_[y][x].lit = true;
                    levels[0].map_[y][x].seen = true;
                } else {
                    levels[0].map_[y][x].lit = false;
                }
            }
        }

        RenderLevel(&levels[0]);
        RenderHud(levels[0].entities_[0]);

        // placeholder input stuff
        ch = getch();
        switch (ch) {
            case KEY_UP:
                player->Move(-1, 0, levels[0].map_);
                AddHudMessage("Player Moved Up!");
                break;
            case KEY_DOWN:
                player->Move(1, 0, levels[0].map_);
                AddHudMessage("Player Moved Down!");
                break;
            case KEY_LEFT:
                player->Move(0, -1, levels[0].map_);
                AddHudMessage("Player Moved Left!");
                break;
            case KEY_RIGHT:
                player->Move(0, 1, levels[0].map_);
                AddHudMessage("Player Moved Right!");
                break;
        }
    }
    // end ncurses
    endwin();

    // everything went perfectly :)
    return 0;
}
