#include "renderer.h"

// ncurses variables
WINDOW* ncurses_hud_window;

// screen variables
int screen_width;
int screen_height;

// hud variables
int hud_width;
int hud_message_number = 0;
std::string hud_messages[10];

// predefine local functions for rendering level
void RenderEntities(std::vector<Entity*>, map_type);
void RenderEnvironment(map_type);

// predefine local functions for rendering hud
void PrintHudMessages();


// helper function to get the number of characters to be printed when printing int
int GetIntLength(int num) {
    int digits = 0;
    if (num <= 0) {
        num = 0 - num;
        digits++;
    }
    while (num >= 1) {
        num /= 10;
        digits++;
    }
    return digits;
}

// initialise ncurses, and its variables such as colours etc
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

    // update game window so it doesn't overlap with hud
    stdscr = newwin(screen_height, screen_width, 0, 0);

    // create hud window
    hud_width = screen_width-kMapWidth;
    ncurses_hud_window = newwin(screen_height, hud_width, 0, kMapWidth);

    // refresh all windows before the first frame
    wrefresh(stdscr);
    wrefresh(ncurses_hud_window);

    // define colour rgb values (this is necessary in case terminal colours have been altered)
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(COLOR_GREEN, 0, 1000, 0);
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    init_color(COLOR_BLUE, 1000, 0, 800);
    init_color(COLOR_MAGENTA, 1000, 0, 1000);
    init_color(COLOR_CYAN, 0, 1000, 1000);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_color(8, 0, 0, 500);
    //init_color(9, 800, 800, 800);
    init_color(10, 0, 100, 100);

    // initialise colour pairs
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, 8, 8);
    init_pair(3, COLOR_CYAN, COLOR_CYAN);
    init_pair(4, 10, 10); // dark cyan

    // define background
    bkgd(' ' | COLOR_PAIR(0));
}

// render the hud
void RenderHud(Entity* player) {
    wclear(ncurses_hud_window);
    box(ncurses_hud_window, 0, 0);

    // gui status information
    mvwprintw(ncurses_hud_window, 1, 1, "%s", player->GetName().c_str());
    mvwprintw(ncurses_hud_window, 2, 1, "HP: %d", player->GetHP());

    // stats box
    std::array<int, 4> stats = player->GetStats();
    std::string stat_titles[4] = {"Max HP: ", "DEF: ", "ATK Roll: ", "ATK Bonus: "};

    // get the length of the longest string that needs to be printed
    int statbox_width = 0;
    for (int i = 0; i < stats.size(); i ++) {
        if (stat_titles[i].length() + GetIntLength(stats[i]) > statbox_width) {
            statbox_width = stat_titles[i].length() + GetIntLength(stats[i]);
        }
    }

    // print stat lines
    for (int i = 0; i < stats.size(); i++) {
        mvwprintw(
                ncurses_hud_window,
                i + 1,
                hud_width - 2 - statbox_width,
                "%s",
                stat_titles[i].c_str());

        mvwprintw(
                ncurses_hud_window,
                i + 1,
                hud_width - 1 - GetIntLength(stats[i]),
                "%d", stats[i]);
    }

    // add the hud messages
    PrintHudMessages();

    // finally, refresh the hud window
    wrefresh(ncurses_hud_window);
}

// print messages
void PrintHudMessages() {
    // keep track of the line currently being printed on
    int current_term_line = screen_height-1;
    for (int i = hud_message_number - 1; i > hud_message_number - 10; i--) {
        // stop printing if we've run out of messages, or the messages would print too
        // (thus preventing printing over other hud information)
        if (i < 0 || current_term_line <= 10) {
            break;
        }

        // get the number  of lines this message will take up
        int num_lines = ceil(hud_messages[i%10].length() / (float) (hud_width - 2));

        // print each line of the message, with a maximum number of characters equal to the
        // width of the hud - 2 (since there are two border characters)
        for (int l = 0; l < num_lines; l++) {
            mvwprintw(
                    ncurses_hud_window,
                    current_term_line - num_lines + l,
                    1,
                    "%s",
                    hud_messages[i%10]
                        .substr((hud_width - 2) * l,(hud_width - 2) * (l + 1)).c_str());
        }

        // move the next print up by the number of lines just printed
        current_term_line -= num_lines;
    }
}

// render the main level window
void RenderLevel(Level* level) {
    wclear(stdscr);

    RenderEnvironment(level->map_);
    RenderEntities(level->entities_, level->map_);

    refresh();
}

// loop through the map, and render the corresponding tiles
void RenderEnvironment(map_type map) {
    for (int y = 0; y < kMapHeight; y++) {
        for (int x = 0; x < kMapWidth; x++) {
            if (map[y][x].lit) {
                mvaddch(y, x, map[y][x].character | COLOR_PAIR(map[y][x].lit_color_pair));
            } else {
                if (map[y][x].seen) {
                    mvaddch(y, x, map[y][x].character | COLOR_PAIR(map[y][x].unlit_color_pair));
                }
            }
        }
    }
}

// loop through entities and render those on top of the map
void RenderEntities(std::vector<Entity*> entities, map_type map) {
    for (Entity* entity : entities) {
        if (map[entity->GetY()][entity->GetX()].lit) {
            mvaddch(
                    entity->GetY(),
                    entity->GetX(),
                    entity->GetAvatar() | COLOR_PAIR(entity->GetColorPair()));
        }
    }
}

// add a message to the hud
void AddLogMessages(Log* log) {
    while (log->GetUnreads() > 0) {
        if (log->GetName() != "Main") {
            hud_messages[hud_message_number++ % 10] = log->GetName().append(": ").append(log->GetMessage());
        } else {
            hud_messages[hud_message_number++ % 10] = log->GetMessage();
        }
    }
}
