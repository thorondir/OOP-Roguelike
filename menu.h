#ifndef MENU_H_
#define MENU_H_

#include "input.h"
#include "entity.h"
#include "item.h"

enum MenuContext {
    kInven,
    kItemOptions,
};

extern MenuContext current_menu_context;

extern void ManageMenu(Entity*);

#endif
