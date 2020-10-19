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

    faction_ = 0;
    // defines whether the player will attack when moving into this entity
    // the player shouldn't attack the default entity (monsters are a special case)

    doormat_ = true;
    // defines whether other can walk over/through this entity's tile
    // player should be able to walk over the default entity? might be worth changing

    living_ = false; // monsters attack living things, but shouldn't attack every entity
    dead_ = false; // entities start alive

    color_pair_ = 3;

    // inventory
    max_weight_ = 40.0;
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

int Entity::GetFaction() {
    return faction_;
}

bool Entity::GetDoormat() {
    return doormat_;
}

bool Entity::GetLiving() {
    return living_;
}

bool Entity::GetDead() {
    return dead_;
}

// return the entity's colour pair
short Entity::GetColorPair() {
    return color_pair_;
}

void Entity::Brain(map_type map, std::vector<Entity*>* entities) {
    return;
}

// for both the following methods, the entity can move out of bounds. i don't care.
void Entity::MoveAttack(int dy, int dx, map_type map, std::vector<Entity*> residents) {
    int new_y = y_ + dy;
    int new_x = x_ + dx;

    for (Entity* target : residents) {
        if (target->GetY() == new_y && target->GetX() == new_x) {
            if (target->GetFaction() != GetFaction() && !target->GetDead()) {
                // damage roll can be up to maximum roll
                std::uniform_int_distribution<> damage_range(0, stats_[2]);

                int damage = damage_range(kRng) + stats_[3];

                target->TakeDamage(damage);
                main_log->AddMessage(std::string("").append(name_)
                        .append(std::string(" attacks ")).append(target->GetName())
                        .append(" for ").append(std::to_string(damage)).append(" damage!"));
                return;
            } else if (!target->GetDoormat()){
                return;
            }
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

// inventory stuff

//bool Entity::InventoryComp(Item a, Item b) {
//    return a.GetName().compare(b.GetName()) < 0;
//}

// get the total weight held by the entity
std::map<Item, int>* Entity::GetInventory() {
    return &inventory_;
}

float Entity::GetInvenWeight() {
    float weight = 0;
    for (std::pair<Item, int> item : inventory_) {
        weight += item.first.GetWeight()*item.second;
    }
    return weight;
}

void Entity::PickupItem(Item item){
    inventory_[item]++;
}

void Entity::TakeItems(Entity* other_entity) {
    std::map<Item, int>* other_inventory = other_entity->GetInventory();
    // first get items
    if (other_inventory->size() > 0 && other_entity != this) {
        for (std::pair<Item, int> item : *other_inventory) {
            if (item.second) {
                inventory_[item.first] += item.second;
                other_inventory->at(item.first) = 0;
                main_log->AddMessage(
                        std::string()
                        .append(GetName())
                        .append(" picks up ")
                        .append(std::to_string(item.second))
                        .append("x ")
                        .append(item.first.GetName()));
            }
        }
         
        // then remove them all from the target
         /*
        for (std::pair<Item, int> item : *other_inventory) {
            other_inventory->erase(item.first);
        }*/
    }
}

bool Entity::DropItem(Item item, int count, std::vector<Entity*>* entities) {
    if (inventory_[item] >= count) {
        inventory_[item]--;
        std::string description;

        if (count > 1) {
            description = std::to_string(count).append("x ").append(item.GetName());
        } else {
            description = std::string("A ").append(item.GetName());
        }

        entities->push_back(new ItemEntity(
                item.GetName(),
                description,
                GetY(),
                GetX(),
                item.GetName()[0],
                &item,
                count,
                entities->end()));
    }
    return false;
}

void Entity::EquipItem(){
}

void Entity::DequipItem(){
}

void Entity::UseItem(){
}

bool Entity::ConsumeItem(ComestibleItem* item){
    if (inventory_[*item] > 0) {
        item->Consume(this);
        if (inventory_[*item] > 1) {
            inventory_[*item]--;
        } else {
            inventory_.erase(*item);
        }
        return true;
    } else {
        inventory_.erase(*item);
        return false;
    }
}


// non-blind entity
std::vector<std::vector<bool>> NonBlindEntity::GetFOV() {
    return FOV.SpiralPath(y_, x_);
}

void NonBlindEntity::UpdateFOVTransparent(std::array<std::array<bool, kMapWidth>, kMapHeight> transparentmap) {
    for (int y = 0; y < kMapHeight; y++) {
        for (int x = 0; x < kMapWidth; x++) {
            FOV.transparentmap_[y][x] = transparentmap[y][x];
        }
    }
}

NonBlindEntity::~NonBlindEntity() {
}

// Item entity
void ItemEntity::Brain(map_type map, std::vector<Entity*>* entities) {
    int total_count = 0;
    for (std::pair <Item, int> item : inventory_) {
        total_count += inventory_[item.first];
    }
    if (total_count <= 0) {
        entities->erase(position_);
        delete this;
    }
};
