#include "entity.h"

Entity::Entity(int y, int x, char avatar) {
    y_ = y;
    x_ = x;
    avatar_ = avatar;
}

// return the entity's character avatar
char Entity::GetAvatar() {
    return avatar_;
}

/*
// return the entity's colour pair
short Entity::GetColorPair() {
}
*/

// return the x coordinate of the entity, perhaps make this more elegant in terms of returning both y and x as a pair?
int Entity::GetX() {
    return x_;
}

// return the y coordinate of the entity
int Entity::GetY() {
    return y_;
}

// for both the following methods, the entity can move out of bounds. i don't care.

// move entity some number of units
void Entity::Move(int dy, int dx) {
    y_ += dy;
    x_ += dx;
}

// set entity's location to arguments
void Entity::SetPos(int y, int x) {
    y_ = y;
    x_ = x;
}
