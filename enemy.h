#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>
#include <string>

#include "logger.h"
#include "constants.h"
#include "entity.h"

class Enemy : public Entity {
    public:
        Enemy(std::string name, std::string description, int y, int x, char avatar) :
            Entity(name, description, y, x, avatar), target_(nullptr) {};
        ~Enemy();
        void Brain(map_type, std::vector<Entity*>);
    private:
        Entity* target_;
};

#endif
