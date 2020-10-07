#include "environment.h"

// room constructor
Room::Room() {
    y_ = x_ = width_ = height_ = 0;
}

// return the y coordinate of the top left corner
int Room::GetY1() {
    return y_;
}

// return the x coordinate of the top left corner
int Room::GetX1() {
    return x_;
}

// return the y coordinate of the bottom right corner
int Room::GetY2() {
    return y_ + height_ - 1; // -1 so that it's the inside edge
}

// return the x coordinate of the bottom right corner
int Room::GetX2() {
    return x_ + width_ - 1;
}

// return the height of the room
int Room::GetHeight() {
    return height_;
}

// return the width of the room
int Room::GetWidth() {
    return width_;
}

// return the area of the room
int Room::GetArea() {
    return width_*height_;
}

// maybe add a getter for perimeter?
