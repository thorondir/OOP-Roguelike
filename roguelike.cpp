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

    // introduction text
    main_log->AddMessage("Welcome to Ying Stokes' Thematically Confused Roguelike!");
    main_log->AddMessage("You are a maintenance droid gone rogue.");
    main_log->AddMessage("Make your way to the core in order to destroy the masters you swore to repair.");
    main_log->AddMessage("---INSTRUCTIONS---");
    main_log->AddMessage("Use arrow keys or the numpad to move your character (@)");
    main_log->AddMessage("Run into the oncoming sawbots to destroy them");
    main_log->AddMessage("Use 'g' to pick up items that fall on the ground");
    main_log->AddMessage("Use 'i' to access your inventory, and the letters surrounded by parentheses to use items");
    main_log->AddMessage("Press '>' and '<' while standing on the corresponding tiles to move between levels");
    main_log->AddMessage("Use 'q' to exit menus and the game");
    main_log->AddMessage("See how close you can get to the core... Good luck!");

    // create the player as an entity in dynamic memory, in the centre of the first room
    Player* player = new Player(
            (levels[0].GetRooms()[0].GetY1() + levels[0].GetRooms()[0].GetY2())/2,
            (levels[0].GetRooms()[0].GetX1() + levels[0].GetRooms()[0].GetX2())/2);

    // put the player into the first level
    levels[0].entities_.push_back(player);
    // player starts with a repair kit
    player->PickupItem(new HealingItem("Repair kit", 10.0, 50.0, 10));

    // game loop
    FrameInfo frame_info = {kNone, kMain};
    Level* level = &levels[0];
    int current_level = 1;
    do {
        switch (frame_info.input_context) {
            // if the player is interacting with the main game
            case kMain: {
                // handle movement between levels
                if (frame_info.input_type == kFloorDown) {
                    if (level->map_[player->GetY()][player->GetX()].character == '>') {
                        // if the new levels needs to be created, do that
                        if (current_level == levels.size()) {
                            levels.push_back(level->NextFloor());
                        }

                        // move the player into the next level
                        Level::TryMoveEntity(&levels[current_level-1], &levels[current_level], player);
                        // set the position of the player to the new level's up-stairs
                        player->SetPos(levels[current_level].GetUpStairY(), levels[current_level].GetUpStairX());

                        // increment the level int and pointer
                        level = &levels[current_level]; // level -1 + 1
                        current_level++;

                        // print a handy message
                        main_log->AddMessage("The player is transported one floor closer to the core...");
                    }
                }

                // same thing but for going up
                if (frame_info.input_type == kFloorUp) {
                    if (level->map_[player->GetY()][player->GetX()].character == '<') {
                        // make sure going up is possible
                        if (current_level > 1) {
                            // never any need to make a new level
                            level = &levels[current_level-2];
                            Level::TryMoveEntity(&levels[current_level-1], &levels[current_level-2], player);
                            player->SetPos(levels[current_level-2].GetDownStairY(), levels[current_level-2].GetDownStairX());
                            current_level--;
                            main_log->AddMessage("The player is transported one floor away from the core...");
                        }
                    }
                }

                // if the last input was just a regular movement, update every entity
                if (frame_info.input_type == kAction) {
                    // in reverse order so the player is first (since enemies are created when the level is created)
                    for (int e = level->entities_.size() - 1; e >= 0; e--) {
                        if (level->entities_[e]->active_)
                            level->entities_[e]->Brain(level->map_, level->entities_);
                    }
                }

                // update fov
                std::array<std::array<bool, kMapWidth>, kMapHeight> transparentmap = level->GetTransparent();
                for (Entity* entity : level->entities_) {
                    // only update transparentmap if it's a NonBlindEntity
                    NonBlindEntity* non_blind_entity = dynamic_cast<NonBlindEntity*>(entity);
                    if (non_blind_entity) non_blind_entity->UpdateFOVTransparent(transparentmap);
                }

                // update the litness of tiles
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

                // call rendering functions
                RenderLevel(level);
                AddLogMessages(main_log);
                AddLogMessages(debug_log);
                RenderHud(player, current_level);

                break;
            }
            case kMenu: {
                // if the context is a menu, render the menu
                ManageMenu(player);
                RenderMenu(player);
                break;
            }
        }

        // get the next input
        frame_info = input(frame_info);

        // quit if necessary
    } while (frame_info.input_context != kAbort);
    // end ncurses
    endwin();

    // free logs after quitting
    delete main_log;
    delete debug_log;

    // free all entities
    for (Level level : levels) {
        level.FreeEntities();
    }

    // everything went perfectly :)
    return 0;
}
