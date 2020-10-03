#include "renderer.h"

Renderer::Renderer() {
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();

    getmaxyx(stdscr, screen_height_, screen_width_);
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    bkgd(' ' | COLOR_PAIR(0));
}

void Renderer::RenderGui(std::array<std::string, 10> messages) {
    for (int i = gui_message_number_; i > gui_message_number_ - 10; i--) {
        // print messages[i%10]

        if (i == 0) {
            break;
        }
    }
}

void Renderer::RenderLevel(Level level) {
    wclear(stdscr);

    RenderEnvironment(level.map_);
    RenderEntities(level.entities_);

    refresh();
}

void Renderer::RenderEnvironment(std::array<std::array<Tile, kMapWidth>, kMapHeight> map) {
    for (int y = 0; y < kMapHeight; y++) {
        for (int x = 0; x < kMapWidth; x++) {
            mvaddch(y, x, map[y][x].character);
        }
    }
}

void Renderer::RenderEntities(std::vector<Entity> entities) {
    for (Entity entity : entities) {
        mvaddch(entity.GetY(),  entity.GetX(), entity.GetAvatar());
    }
}
