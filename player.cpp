#include "player.h"

Player::~Player() {
}

// get the total weight held by the player
float Player::GetInvenWeight() {
    float weight = 0;
    for (std::pair<Item, int> item : equipment_) {
        weight += item.first.GetWeight()*item.second;
    }
    return weight;
}

std::vector<std::vector<bool>> Player::GetFOV() {
    return FOV.SpiralPath(y_, x_);
}

void Player::UpdateFOVTransparent(std::array<std::array<bool, kMapWidth>, kMapHeight> transparentmap) {
    for (int y = 0; y < kMapHeight; y++) {
        for (int x = 0; x < kMapWidth; x++) {
            FOV.transparentmap_[y][x] = transparentmap[y][x];
        }
    }
}

void Player::Brain(map_type map, std::vector<Entity*> residents) {
    int ch = GetLastCh();
    if (ch == '8' || ch == KEY_UP) {
        MoveAttack(-1, 0, map, residents);
    } else if (ch == '9') {
        MoveAttack(-1, 1, map, residents);
    } else if (ch == '6' || ch == KEY_RIGHT) {
        MoveAttack(0, 1, map, residents);
    } else if (ch == '3') {
        MoveAttack(1, 1, map, residents);
    } else if (ch == '2' || ch == KEY_DOWN) {
        MoveAttack(1, 0, map, residents);
    } else if (ch == '1') {
        MoveAttack(1, -1, map, residents);
    } else if (ch == '4' || ch == KEY_LEFT) {
        MoveAttack(0, -1, map, residents);
    } else if (ch == '7') {
        MoveAttack(-1,-1, map, residents);
    } else if (ch == '5') {
        MoveAttack(0, 0, map, residents);
    }
}
