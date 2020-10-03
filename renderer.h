#ifndef RENDERER_H_
#define RENDERER_H_

#include <ncurses.h>
#include <array>
#include <string>
#include <vector>

#include "entity.h"
#include "level.h"
#include "environment.h"
#include "constants.h"

class Renderer {
    public:
        Renderer();

        void RenderGui(std::array<std::string, 10>);
        void RenderLevel(Level);
    private:
        int screen_width_;
        int screen_height_;
        int gui_message_number_;
        void RenderEntities(std::vector<Entity>);
        void RenderEnvironment(std::array<std::array<Tile, kMapWidth>, kMapHeight>);
};

#endif
