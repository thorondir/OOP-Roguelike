#include "menu.h"

MenuContext current_menu_context = kInven;

void ManageMenu(Entity* player) {
    int ch = GetLastCh();
    if (current_menu_context == kInven) {
        char current_char_option = 'a';
        for (auto item : *player->GetInventory()) {
            if (ch == current_char_option++) {
                ComestibleItem* pointer_to_eat = dynamic_cast<ComestibleItem*>(item.second.first);
                if (pointer_to_eat) player->ConsumeItem(pointer_to_eat);
            }
        }
    } else if (current_menu_context == kItemOptions) {
    }
}
