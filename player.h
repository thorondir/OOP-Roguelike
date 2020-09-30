#ifndef PLAYER_H_
#define PLAYER_H_

#include "entity.h"

class Player : public Entity {
    public:
        Player(int y, int x) : Entity(y, x, '@') {};
};

#endif
