#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

class Room {
    public:
        Room(int y, int x, int w, int h) : y_(y), x_(x), width_(w), height_(h) {};

        int GetY1();
        int GetX1();
        int GetY2();
        int GetX2();
        int GetHeight();
        int GetWidth();
        int GetArea();
    private:
        int y_, x_, width_, height_;
};

struct Tile {
    bool blocking;
    bool transparent;
    int color_pair;
    char character;
};

#endif
