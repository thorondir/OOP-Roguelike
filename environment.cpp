#include "environment.h"

Room::Room() {
    y_ = x_ = width_ = height_ = 0;
}

int Room::GetY1() {
    return y_;
}

int Room::GetX1() {
    return x_;
}

int Room::GetY2() {
    return y_ + height_ - 1; // -1 so that it's the inside edge
}

int Room::GetX2() {
    return x_ + width_ - 1;
}

int Room::GetHeight() {
    return height_;
}

int Room::GetWidth() {
    return width_;
}

int Room::GetArea() {
    return width_*height_;
}
