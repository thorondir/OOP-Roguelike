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
    player->PickupItem(new HealingItem("Jess", 69.0, 42.0, 10));

    // game loop
    FrameInfo frame_info = {kNone, kMain};
    Level* level = &levels[0];
    int current_level = 1;
    do {
        switch (frame_info.input_context) {
            case kMain: {
                if (frame_info.input_type == kFloorDown) {
                    if (level->map_[player->GetY()][player->GetX()].character == '>') {
                        if (current_level == levels.size()) {
                            levels.push_back(level->NextFloor());
                        }

                        Level::TryMoveEntity(&levels[current_level-1], &levels[current_level], player);
                        player->SetPos(levels[current_level].GetUpStairY(), levels[current_level].GetUpStairX());

                        level = &levels[current_level]; // level -1 + 1
                        current_level++;

                        main_log->AddMessage("The player is transported one floor closer to the core...");
                    }
                }

                if (frame_info.input_type == kFloorUp) {
                    if (level->map_[player->GetY()][player->GetX()].character == '<') {
                        if (current_level > 1) {
                            level = &levels[current_level-2];
                            Level::TryMoveEntity(&levels[current_level-1], &levels[current_level-2], player);
                            player->SetPos(level[current_level-2].GetDownStairY(), level[current_level-2].GetDownStairX());
                            current_level--;
                            main_log->AddMessage("The player is transported one floor away from the core...");
                        }
                    }
                }

                if (frame_info.input_type == kAction) {
                    for (Entity* entity : level->entities_) {
                        entity->Brain(level->map_, &level->entities_);
                    }
                }

                // update fov
                // loop again just in case the entity got deleted
                std::array<std::array<bool, kMapWidth>, kMapHeight> transparentmap = level->GetTransparent();
                for (Entity* entity : level->entities_) {
                    // only update transparentmap if it's a NonBlindEntity
                    NonBlindEntity* non_blind_entity = dynamic_cast<NonBlindEntity*>(entity);
                    if (non_blind_entity) non_blind_entity->UpdateFOVTransparent(transparentmap);
                }

                // render the level and the hud
                std::vector<std::vector<bool>> visible = player->GetFOV();

                for (int y = 0; y < kMapHeight; y++) {
                    for (int x = 0; x < kMapWidth; x++) {
                        if (visible[y][x]) {
                            level->map_[y][x].lit = true;
                            level->map_[y][x].seen = true;
                        } else {
                            level->map_[y][x].lit = false;
                        }
                    }
                }

                RenderLevel(level);
                AddLogMessages(main_log);
                AddLogMessages(debug_log);
                RenderHud(player);

                break;
            }
            case kMenu: {
                ManageMenu(player);
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
