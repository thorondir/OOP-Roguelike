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

class Player : public Entity {
    public:
        Player(int y, int x) : Entity("Player", "This is you, the player", y, x, '@'),
            FOV(kMapHeight, kMapWidth, 10, 0, 2*M_PI) {};
        ~Player();
        std::vector<std::vector<bool>> GetFOV();
        void UpdateFOVTransparent(std::array<std::array<bool, kMapWidth>, kMapHeight>);

        void Brain(map_type, std::vector<Entity*>);
    private:
        std::vector<std::pair<Item,int>> equipment_;
        float max_weight_;

        SpiralPathFOV FOV;

        float GetInvenWeight();
};

#endif
