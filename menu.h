#ifndef MENU_H_
#define MENU_H_

#include "input.h"
#include "entity.h"
#include "item.h"

// pages of the menu
enum MenuContext {
    kInven,
    kItemOptions,
};

// global variable tracking what page the user is interacting with
extern MenuContext current_menu_context;

// function to manage menu
extern void ManageMenu(Entity*);

#endif
