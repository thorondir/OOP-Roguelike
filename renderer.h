#ifndef RENDERER_H_
#define RENDERER_H_

#include <ncurses.h>
#include <array>
#include <string>
#include <vector>

#include "entity.h"
#include "player.h"
#include "level.h"
#include "environment.h"
#include "constants.h"

void InitialiseRenderer();

void RenderHud(Player*, std::array<std::string, 10>);
void RenderLevel(Level);

#endif
