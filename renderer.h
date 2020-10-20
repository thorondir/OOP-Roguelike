#ifndef RENDERER_H_
#define RENDERER_H_

#include <ncurses.h>
#include <array>
#include <string>
#include <vector>
#include <cmath>

#include "logger.h"
#include "entity.h"
#include "inventory.h"
#include "level.h"
#include "environment.h"
#include "constants.h"

extern void InitialiseRenderer();

extern void RenderHud(Entity*);
extern void RenderLevel(Level*);
extern void RenderMenu(Entity*);

extern void AddLogMessages(Log*);

#endif
