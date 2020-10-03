#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <array>

#include "constants.h"
#include "environment.h"

class Entity {
    public:
        Entity(std::string, std::string, int, int, char);

        static int next_id_;

        int GetX();
        int GetY();
        char GetAvatar();
        int GetId();
        int* GetStats(); // this is known to be int[4], which will not change
        short GetColorPair();
        void SetPos(int, int);
        void Move(int, int, std::array<std::array<Tile, kMapWidth>, kMapHeight>);
        void TakeDamage(int);
        //void Damage(int);
        void Heal(int);

    protected:
        int x_,y_;
        int hp_;
        int stats_[4]; // {maximum_hp, defense, maximum_attack_roll, attack_bonus}
        int equipment_slots_[4]; // {heads, arms, torsos, feet}
        bool friendly_; // whether the player attacks the entity
        bool doormat_; // whether the entity can be walked over
        bool living_;
        bool dead_;
        short color_pair_;
    private:
        std::string name_;
        std::string description_;
        char avatar_;
        int id_;
};
#endif
