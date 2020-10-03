#include "roguelike.h"

int main() {
    Renderer renderer;

    std::vector<Level> levels;

    levels.push_back(Level());
    levels[0].entities_.push_back(Player(20, 40));

    int ch;

    while (ch != 'q') {
        renderer.RenderLevel(levels[0]);

        ch = getch();
        switch (ch) {
            case KEY_UP:
                levels[0].entities_[0].Move(-1,0);
                break;
            case KEY_DOWN:
                levels[0].entities_[0].Move(1,0);
                break;
            case KEY_LEFT:
                levels[0].entities_[0].Move(0,-1);
                break;
            case KEY_RIGHT:
                levels[0].entities_[0].Move(0,1);
                break;
        }
    }

    endwin();

    return 0;
}
