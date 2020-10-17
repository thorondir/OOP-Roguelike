#include "enemy.h"

Enemy::~Enemy() {
}

void Enemy::Brain(map_type map, std::vector<Entity*> residents) {
    if (!dead_) {
        if (hp_ <= 0) {
            dead_ = true;
            doormat_ = true;
            color_pair_ = 5;
            return;
        }
        // get FOV
        std::vector<std::vector<bool>> visible = GetFOV();

        // try to find a target
        if (target_ == nullptr) {
            for (Entity* entity : residents) {
                if (entity->GetFaction() != faction_ && entity->GetLiving() &&
                        visible[entity->GetY()][entity->GetX()]) {
                    target_ = entity;
                }
            }
        }

        // if you've got a target, run at it
        if (target_ != nullptr) {
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
    }
}
