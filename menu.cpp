#include "menu.h"

// the default menu is the inventory
// others are even implemented so this is pretty redundant
// i'd like to add this later though, so.....
MenuContext current_menu_context = kInven;

// at this stage, print the inventory with the right letters for items
void ManageMenu(Entity* player) {
    int ch = GetLastCh();
    if (current_menu_context == kInven) {
        char current_char_option = 'a';
        // loop through items
        for (auto item : player->GetInventory()->GetItems()) {
            // only print listing if there's more than 0
            if (item->count_ > 0) {
                // skip 'q'
                if (current_char_option == 'q') current_char_option++;
                // if the player pressed the corresponding character
                if (ch == current_char_option++) {
                    ComestibleItem* pointer_to_eat = dynamic_cast<ComestibleItem*>(item);
                    if (pointer_to_eat) player->ConsumeItem(pointer_to_eat);
                }
            }
        }
    } else if (current_menu_context == kItemOptions) {
        // nothing happens here yet
    }
}
