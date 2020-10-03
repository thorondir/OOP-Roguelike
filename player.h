#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>

#include "entity.h"
#include "item.h"

class Player : public Entity {
    public:
        Player(int y, int x) : Entity("Player", "This is you, the player", y, x, '@') {};
    private:
        std::vector<std::pair<Item,int>> equipment_;
        float max_weight_;

        float GetInvenWeight();
};

#endif
