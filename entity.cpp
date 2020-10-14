#include "entity.h"

int Entity::next_id_ = 0;

// entity constructor, initialise default entity variables
Entity::Entity(std::string name, std::string description, int y, int x, char avatar) {
    name_ = name;
    description_ = description;
    y_ = y;
    x_ = x;
    avatar_ = avatar;

    id_ = next_id_++;

    // set default stats
    stats_[0] = 10; // normal entity has 10 hp
    stats_[1] = 0; // 0 defense
    stats_[2] = 0; // 0 maximum attack roll
    stats_[3] = 1; // 1 attack bonus (min damage)

    hp_ = stats_[0];

    //set default slots
    equipment_slots_[0] = 1; // normal entity has 1 head
    equipment_slots_[1] = 2; // 2 arms
    equipment_slots_[2] = 1; // 1 torso
    equipment_slots_[3] = 2; // 2 feet

    friendly_ = true;    
    // defines whether the player will attack when moving into this entity
    // the player shouldn't attack the default entity (monsters are a special case)

    doormat_ = true;
    // defines whether other can walk over/through this entity's tile
    // player should be able to walk over the default entity? might be worth changing

    living_ = false; // monsters attack living things, but shouldn't attack every entity
    dead_ = false; // entities start alive

    color_pair_ = 0;
}

Entity::~Entity() {
}

// return the x coordinate of the entity
// perhaps make this more elegant in terms of returning both y and x as a pair?
int Entity::GetX() {
    return x_;
}

// return the y coordinate of the entity
int Entity::GetY() {
    return y_;
}

// return the entity's character avatar
char Entity::GetAvatar() {
    return avatar_;
}

// return the entity's name
std::string Entity::GetName() {
    return name_;
}

// return the id number of the entity.
// this can doesn't get reset at all until the end of execution,
// so it will continually increase even after changing levels etc
// (not sure how this interacts with moving the player entity between levels...)
int Entity::GetId() {
    return id_;
}

// return the entity's current hp
int Entity::GetHP() {
    return hp_;
}

// return the stat array of the entity
std::array<int, 4> Entity::GetStats() {
    return stats_;
}

// return the entity's colour pair
short Entity::GetColorPair() {
    return color_pair_;
}

void Entity::Brain(map_type map, std::vector<Entity*> entities) {
    return;
}

// for both the following methods, the entity can move out of bounds. i don't care.
void Entity::MoveAttack(int dy, int dx, map_type map, std::vector<Entity*> residents) {
    int new_y = y_ + dy;
    int new_x = x_ + dx;

    for (Entity* target : residents) {
        if (target->GetY() == new_y && target->GetX() == new_x) {
            main_log->AddMessage(std::string("").append(name_).append(std::string(" attacks ")).append(target->GetName()));
            return;
        }
    }

    if (!map[new_y][new_x].blocking) {
        Move(dy, dx);
    }
}

// move entity some number of units
void Entity::Move(int dy, int dx) {
    y_ += dy;
    x_ += dx;
}

// set entity's location to arguments
void Entity::SetPos(int y, int x) {
    y_ = y;
    x_ = x;
}

// apply damage to this entity
// it might be worth adding a damage source pointer or something like that?
void Entity::TakeDamage(int damage) {
    hp_ -= (damage - stats_[1]);
}

/* deal damage to another entity from this entity
 * maybe imoplement this later, but it probably isn't necessary
void Entity::Damage() {

} */

// heal this entity. it might be worth making this virtual and/or adding a
// heal bonus stat or something like that
void Entity::Heal(int heal) {
    hp_ += heal;
}
