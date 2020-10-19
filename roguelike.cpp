#include "roguelike.h"

int main() {
    // get ncurses going
    InitialiseRenderer();

    // create the main log
    main_log = new Log("Main");
    debug_log = new Log("Debug");

    // vector containing all levels
    std::vector<Level> levels;

    // initialise first level
    levels.push_back(Level());

    debug_log->AddMessage(std::to_string(levels[0].entities_.size()));

    // create the player entity reference
    Player* player = new Player(
            (levels[0].GetRooms()[0].GetY1() + levels[0].GetRooms()[0].GetY2())/2,
            (levels[0].GetRooms()[0].GetX1() + levels[0].GetRooms()[0].GetX2())/2);
    levels[0].entities_.push_back(new Entity("Test", "Test Entity",
            (levels[0].GetRooms()[0].GetY1() + levels[0].GetRooms()[0].GetY2())/2,
            (levels[0].GetRooms()[0].GetX1() + levels[0].GetRooms()[0].GetX2())/2 + 1, 'T'));

    // put the player into the first level
    /*levels[0].entities_.push_back(new Enemy("Sawbot","it's sawbot",
            (levels[0].GetRooms()[0].GetY1() + levels[0].GetRooms()[0].GetY2())/2,
            (levels[0].GetRooms()[0].GetX1() + levels[0].GetRooms()[0].GetX2())/2 + 1,
            's'));*/
    levels[0].entities_.push_back(player);
    HealingItem jeff = HealingItem("Jeff", 69.0, 42.0, 2);
    player->PickupItem(jeff);

    std::array<std::array<bool, kMapWidth>, kMapHeight> transparentmap;

    for (int y = 0; y < kMapHeight; y++) {
        for (int x = 0; x < kMapWidth; x++) {
            transparentmap[y][x] = levels[0].map_[y][x].transparent;
        }
    }

    player->UpdateFOVTransparent(transparentmap);

    // game loop
    FrameInfo frame_info = {kNone, kMain};
    do {
        switch (frame_info.input_context) {
            case kMain: {
                if (frame_info.input_type == kAction) {
                    for (Entity* entity : levels[0].entities_) {
                        entity->Brain(levels[0].map_, &levels[0].entities_);
                    }
                    // loop again just in case the entity got deleted    
                    for (Entity* entity : levels[0].entities_) {
                        // only update transparentmap if it's a NonBlindEntity
                        NonBlindEntity* non_blind_entity = dynamic_cast<NonBlindEntity*>(entity);
                        if (non_blind_entity) non_blind_entity->UpdateFOVTransparent(transparentmap);
                    }
                }

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
                AddLogMessages(debug_log);
                RenderHud(player);

                break;
            }
            case kMenu: {
                if (GetLastCh() == 'n') player->ConsumeItem(&jeff);
                RenderMenu(player);
                break;
            }
        }

        frame_info = input(frame_info);

    } while (frame_info.input_context != kAbort);
    // end ncurses
    endwin();
    delete main_log;
    delete debug_log;
    
    // free all entities
    for (Level level : levels) {
        level.FreeEntities();
    }

    // everything went perfectly :)
    return 0;
}
