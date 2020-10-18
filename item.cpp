#include "item.h"

// return the item's name
std::string Item::GetName() const {
    return name_;
}

// return its weight
float Item::GetWeight() {
    return weight_;
}

// return its value
float Item::GetValue() {
    return value_;
}

// drop the item, and spawn an item entity with a reference to this item
void Item::Drop(int y, int x) {
    // gotta figure this out lol
}

// methods for EquippableItem

// get the user of this equippable item
Entity* EquippableItem::GetUser() {
    return user_;
}

// get the slot that this item is relevant to
int EquippableItem::GetSlot() {
    return slot_;
}

// get the stat bonuses provided by this item
std::array<int, 4> EquippableItem::GetBonuses() {
    return bonuses_;
}

// set the current user of this item
void EquippableItem::SetUser(Entity* user) {
    user_ = user;
}

// HealingItem methods

// heal this item's user
void HealingItem::Consume(Entity* user) {
    user->Heal(power_);
}

bool operator<(Item const& item_1, Item const& item_2) {
    return item_1.GetName().compare(item_2.GetName()) < 0;
}
