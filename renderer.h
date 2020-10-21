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

// rendering functions
//
extern void InitialiseRenderer();

extern void RenderHud(Entity*, int);
extern void RenderLevel(Level*);
extern void RenderMenu(Entity*);

// add log messages to the hud
extern void AddLogMessages(Log*);

#endif
