#ifndef INVENTORY_H_
#define INVENTORY_H_

class Item;
#include "item.h"
#include <vector>
#include <algorithm>


class Inventory {
    public:
        ~Inventory();

        static bool TryMove(Inventory*, Inventory*, Item*);
        void AddItem(Item*);
        void RemoveItem(Item*);
        std::vector<Item*>::iterator FindItem(Item*);

        std::vector<Item*>& GetItems();
    private:
        std::vector<Item*> items_;
};

#endif
