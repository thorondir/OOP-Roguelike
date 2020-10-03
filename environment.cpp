#include "environment.h"

int Room::GetY1() {
    return y_;
}

int Room::GetX1() {
    return x_;
}

int Room::GetY2() {
    return y_ + height_;
}

int Room::GetX2() {
    return x_ + width_;
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
