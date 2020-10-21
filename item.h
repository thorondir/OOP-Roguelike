#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <array>

// forward declaration
class Entity;

// generic item class
class Item {
    public:
        // item constructor
        Item(std::string name, float weight, float value) :
            name_(name), weight_(weight), value_(value), count_(1) {};

        std::string GetName();
        float GetWeight();
        float GetValue();

        virtual Item* Clone();

        int count_;

    private:
        std::string name_;

        float weight_;
        float value_;
};

// an item that can be equipped
class EquippableItem : public Item {
    public:
        EquippableItem(
                std::string name,
                float weight,
                float value,
                std::array<int, 4> bonuses) :
                    Item(
                        name,
                        weight,
                        value),
                    bonuses_(bonuses) {};

        // user wearing this item
        Entity* GetUser();
        int GetSlot();
        std::array<int, 4> GetBonuses();

        void SetUser(Entity*);
    private:
        Entity* user_;
        std::array<int, 4> bonuses_;
        int slot_;
};

// item that can be consumed
class ComestibleItem : public Item {
    public:
        ComestibleItem(std::string name, float weight, float value) : Item(name, weight, value) {};

        // pure virtual function to consume with some user
        virtual void Consume(Entity*) = 0;
};

// comestible item that heals the user
class HealingItem : public ComestibleItem {
    public:
        HealingItem(std::string name, float weight,  float value, int power) :
            ComestibleItem(name, weight, value), power_(power) {};
        void Consume(Entity*);
        HealingItem* Clone();
    private:
        int power_;
};

#endif
