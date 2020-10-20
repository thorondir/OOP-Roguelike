#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <array>
#include <vector>
#include <map>
#include <algorithm>

#include "logger.h"
#include "constants.h"
#include "rng.h"
#include "environment.h"
#include "spiralpath.h"
#include "item.h"
#include "inventory.h"

class Inventory;
class Item; // see corresponding comment in item.h
class ComestibleItem;

class Entity {
    public:
        Entity(std::string, std::string, int, int, char);
        virtual ~Entity();

        static int next_id_;

        int GetX();
        int GetY();
        char GetAvatar();
        std::string GetName();
        int GetId();

        int GetHP();
        std::array<int, 4> GetStats(); // this is known to be int[4], which will not change
        short GetColorPair();
        int GetFaction();
        bool GetDoormat();
        bool GetLiving();
        bool GetDead();
        void SetPos(int, int);

        virtual void Brain(map_type, std::vector<Entity*>*); // picks an action
        void Move(int, int);
        void MoveAttack(int, int, map_type, std::vector<Entity*>);

        void TakeDamage(int);
        //void Damage(int);
        void Heal(int);

        // inventory stuff
        Inventory* GetInventory();
        void PickupItem(Item*);
        void TakeItems(Entity*);
        bool DropItem(Item*, std::vector<Entity*>*);
        void EquipItem();
        void DequipItem();
        void UseItem();
        bool ConsumeItem(ComestibleItem*);

    protected:
        int x_,y_;
        int hp_;
        std::array<int, 4> stats_; // {maximum_hp, defense, maximum_attack_roll, attack_bonus}
        std::array<int, 4> equipment_slots_; // {heads, arms, torsos, feet}
        bool faction_; // integer id of entity's faction, 0 being the player
        bool doormat_; // whether the entity can be walked over
        bool living_;
        bool dead_;
        short color_pair_;

        float max_weight_;
        Inventory inventory_;
        //bool InventoryComp(Item, Item);
        float GetInvenWeight();
    private:
        std::string name_;
        std::string description_;
        char avatar_;
        int id_;
};

class NonBlindEntity : public Entity {
    public:
        NonBlindEntity(std::string name, std::string description, int y, int x, char avatar, int radius) :
            Entity(name, description, y, x, avatar),
            FOV(kMapHeight, kMapWidth, radius, 0, 2*M_PI) {};
        virtual ~NonBlindEntity();

        std::vector<std::vector<bool>> GetFOV();
        void UpdateFOVTransparent(std::array<std::array<bool, kMapWidth>, kMapHeight>);
    private:
        SpiralPathFOV FOV;
};

class ItemEntity : public Entity {
    public:
        ItemEntity(std::string name, std::string description, int y, int x, char avatar) :
            Entity(name, description, y, x, avatar),
            position_(nullptr) {
        }
        void Brain(map_type, std::vector<Entity*>*);

        std::vector<Entity*>::iterator position_;
};

#endif
