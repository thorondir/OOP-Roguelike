#ifndef RENDERER_H_
#define RENDERER_H_

#include <ncurses.h>
#include <array>
#include <string>
#include <vector>
#include <cmath>

#include "entity.h"
#include "level.h"
#include "environment.h"
#include "constants.h"

void InitialiseRenderer();

void RenderHud(Entity*);
void RenderLevel(Level);

void AddHudMessage(std::string);

#endif
