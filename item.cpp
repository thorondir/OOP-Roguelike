#include "item.h"

Item::Item(std::string name, float weight, float value) {
    name_ = name;
    weight_ = weight;
    value_ = value;
}

std::string Item::GetName() {
    return name_;
}

float Item::GetWeight() {
    return weight_;
}

float Item::GetValue() {
    return value_;
}

void Item::Drop(int y, int x) {
    // gotta figure this out lol
}

Entity* EquippableItem::GetUser() {
    return user_;
}

int EquippableItem::GetSlot() {
    return slot_;
}

std::array<int, 4> EquippableItem::GetBonuses() {
    return bonuses_;
}

void EquippableItem::SetUser(Entity* user) {
    user_ = user;
}

void HealingItem::Consume(Entity* user) {
    user->Heal(power_);
}
