#include "renderer.h"

// ncurses variables

// screen variables
int screen_width;
int screen_height;
int hud_start_x;

int hud_message_number;

void RenderEntities(std::vector<Entity>);
void RenderEnvironment(std::array<std::array<Tile, kMapWidth>, kMapHeight>);

void InitialiseRenderer() {
    // initialise ncurses
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();

    // get screen dimensions
    getmaxyx(stdscr, screen_height, screen_width);

    // find position where the hud starts
    hud_start_x = screen_width - kMapWidth;

    // create hud window

    // define colour rgb values (this is necessary in case terminal colours have been altered)
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(COLOR_GREEN, 0, 1000, 0);
    init_color(COLOR_YELLOW, 0, 1000, 1000);
    init_color(COLOR_BLUE, 0, 0, 1000);
    init_color(COLOR_MAGENTA, 1000, 0, 1000);
    init_color(COLOR_CYAN, 0, 1000, 1000);
    init_color(COLOR_WHITE, 1000, 1000, 1000);

    // initialise colour pairs
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_BLUE, COLOR_BLUE);

    // define background
    bkgd(' ' | COLOR_PAIR(0));
}

void RenderHud(Player* player, std::array<std::string, 10> messages) {
    for (int i = hud_message_number; i > hud_message_number - 10; i--) {
        // print messages[i%10]

        if (i == 0) {
            break;
        }
    }
}

void RenderLevel(Level level) {
    wclear(stdscr);

    RenderEnvironment(level.map_);
    RenderEntities(level.entities_);

    refresh();
}

void RenderEnvironment(std::array<std::array<Tile, kMapWidth>, kMapHeight> map) {
    for (int y = 0; y < kMapHeight; y++) {
        for (int x = 0; x < kMapWidth; x++) {
            mvaddch(y, x, map[y][x].character | COLOR_PAIR(map[y][x].color_pair));
        }
    }
}

void RenderEntities(std::vector<Entity> entities) {
    for (Entity entity : entities) {
        mvaddch(entity.GetY(),  entity.GetX(), entity.GetAvatar() | COLOR_PAIR(entity.GetColorPair()));
    }
}
