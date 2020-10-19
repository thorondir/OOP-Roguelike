#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>
#include <string>

#include "logger.h"
#include "constants.h"
#include "entity.h"
#include "spiralpath.h"

class Enemy : public NonBlindEntity {
    public:
        Enemy(std::string name, std::string description, int y, int x, char avatar) :
            NonBlindEntity(name, description, y, x, avatar, 15),
            target_(nullptr) {
                HealingItem jeff = HealingItem("Jeff", 69.0, 42.0, 2);
                inventory_[jeff] = 1;
                faction_ = 1;
                doormat_ = false;
            };
        ~Enemy();
        void Brain(map_type, std::vector<Entity*>*);
    private:
        Entity* target_;
};

#endif
