#include "inventory.h"

// free every item from dynamic memory
Inventory::~Inventory() {
    for (Item* item : items_) {
        delete item;
    }
}

// try to move an item between inventories
bool Inventory::TryMove(Inventory* source, Inventory* dest, Item* item) {
    if (source != nullptr && dest != nullptr && item != nullptr) {
        // check the item exists in the source
        auto source_it = std::find(source->items_.begin(), source->items_.end(), item);
        if (source_it != source->items_.end()) {
            auto dest_it = std::find(dest->items_.begin(), dest->items_.end(), item);
            if (dest_it == dest->items_.end()) {
                // if it doesn't exist in the destination, create it!
                dest->items_.push_back(item);
            } else {
                (*dest_it)->count_ += (*source_it)->count_;
            }
            // remove the item from the original inventory
            source->RemoveItem(item);
            return true;
        }
    }
    return false; // return false if an error occurs
}

// add a new item to this inventory
void Inventory::AddItem(Item* item) {
    if (item != nullptr) {
        auto item_it = std::find(items_.begin(), items_.end(), item);
        if (item_it == items_.end()) {
            // add the item to the end of the inventory if it doens't already exist
            items_.push_back(item);
        } else {
            // otherwise just increase the count
            (*item_it)->count_ += item->count_;
        }
    }
}

// remove an item from the vector
// this could be dangerous (memory leak), be careful
void Inventory::RemoveItem(Item* item) {
    items_.erase(FindItem(item));
}

// return the iterator to the item in this inventory
std::vector<Item*>::iterator Inventory::FindItem(Item* item) {
    return std::find(items_.begin(), items_.end(), item);
}

// return a reference to the vector of items
std::vector<Item*>& Inventory::GetItems() {
    return items_;
}
