#include "player.h"

float Player::GetInvenWeight() {
    float weight = 0;
    for (std::pair<Item, int> item : equipment_) {
        weight += item.first.GetWeight()*item.second;
    }
    return weight;
}

