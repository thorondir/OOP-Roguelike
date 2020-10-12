#include "player.h"

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
