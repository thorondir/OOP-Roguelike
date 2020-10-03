#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <array>

#include "entity.h"

class Item {
    public:
        Item(std::string, float, float);

        std::string GetName();
        float GetWeight();
        float GetValue();

        void Drop(int, int);
    private:
        std::string name_;

        float weight_;
        float value_;
};

class EquippableItem : public Item {
    public:
        EquippableItem(std::string name, float weight, float value, std::array<int, 4> bonuses) : Item(name, weight, value), bonuses_(bonuses) {};

        Entity* GetUser();
        int GetSlot();
        std::array<int, 4> GetBonuses();

        void SetUser(Entity*);
    private:
        Entity* user_;
        std::array<int, 4> bonuses_;
        int slot_;
};

class ComestibleItem : public Item {
    public:
        ComestibleItem(std::string name, float weight, float value) : Item(name, weight, value) {};
        virtual void Consume(Entity*) = 0;
};

class HealingItem : public ComestibleItem {
    public:
        HealingItem(std::string name, float weight,  float value, int power) : ComestibleItem(name, weight, value), power_(power) {};
        void Consume(Entity*);
    private:
        int power_;
};

#endif
