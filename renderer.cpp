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
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(COLOR_GREEN, 0, 1000, 0);
    init_color(COLOR_YELLOW, 0, 1000, 1000);
    init_color(COLOR_BLUE, 0, 0, 1000);
    init_color(COLOR_MAGENTA, 1000, 0, 1000);
    init_color(COLOR_CYAN, 0, 1000, 1000);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
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
            mvaddch(y, x, map[y][x].character | COLOR_PAIR(map[y][x].color_pair));
        }
    }
}

void Renderer::RenderEntities(std::vector<Entity> entities) {
    for (Entity entity : entities) {
        mvaddch(entity.GetY(),  entity.GetX(), entity.GetAvatar() | COLOR_PAIR(entity.GetColorPair()));
    }
}
