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
    levels[0].entities_.push_back(new Enemy("Sawbot","it's sawbot",
            (levels[0].GetRooms()[0].GetY1() + levels[0].GetRooms()[0].GetY2())/2,
            (levels[0].GetRooms()[0].GetX1() + levels[0].GetRooms()[0].GetX2())/2 + 1,
            's'));
    levels[0].entities_.push_back(player);

    std::array<std::array<bool, kMapWidth>, kMapHeight> transparentmap;

    for (int y = 0; y < kMapHeight; y++) {
        for (int x = 0; x < kMapWidth; x++) {
            transparentmap[y][x] = levels[0].map_[y][x].transparent;
        }
    }

    player->UpdateFOVTransparent(transparentmap);

    // creat the main log
    main_log = new Log("Main");

    // game loop
    do {
        //for (int i = 0; i < levels[0].entities_.size(); i++) {
        //    levels[0].entities_[i]->Brain(levels[0].map_, levels[0].entities_);
        //}
        levels[0].entities_[0]->Brain(levels[0].map_, levels[0].entities_);
        player->Brain(levels[0].map_, levels[0].entities_);

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
        AddLogMessages(main_log);
        RenderHud(player);

    } while (!input());
    // end ncurses
    endwin();
    delete main_log;

    // everything went perfectly :)
    return 0;
}
