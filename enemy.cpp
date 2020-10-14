#include "enemy.h"

Enemy::~Enemy() {
}

void Enemy::Brain(map_type map, std::vector<Entity*> residents) {
    if (target_ == nullptr) {
        for (Entity* entity : residents) {
            if (entity->GetName() == "Player") {
                target_ = entity;
            }
        }
    }
    int dy, dx;
    if (y_ < target_->GetY()) {
        dy = 1;
    } else if (y_ > target_->GetY()) {
        dy = -1;
    } else dy = 0;

    if (x_ < target_->GetX()) {
        dx = 1;
    } else if (x_ > target_->GetX()) {
        dx = -1;
    } else dx = 0;

    MoveAttack(dy, dx, map, residents);
}
