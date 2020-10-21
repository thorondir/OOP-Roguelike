#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <array>
#include <cmath>
#include <ncurses.h>

#include "constants.h"
#include "entity.h"
#include "item.h"
#include "spiralpath.h"
#include "input.h"

// player class, the player can see
class Player : public NonBlindEntity {
    public:
        // player instantiated with specific name etc
        Player(int y, int x) : NonBlindEntity("Player", "This is you, the player", y, x, '@', 10) {
            living_ = true;
            doormat_ = false;
            stats_[2] = 9;
        };
        ~Player();

        void Brain(map_type, std::vector<Entity*>&);
        void CheckDead(std::vector<Entity*>&);
    private:
        std::vector<std::pair<Item,int>> equipment_;
        float max_weight_;

        float GetInvenWeight();
};

#endif
