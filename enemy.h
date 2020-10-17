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
                faction_ = 1;
                doormat_ = false;
            };
        ~Enemy();
        void Brain(map_type, std::vector<Entity*>);
    private:
        Entity* target_;
};

#endif
