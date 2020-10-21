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

    active_ = true; // whether or not it exists

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

// return the faction
int Entity::GetFaction() {
    return faction_;
}

// return bool of whether this entity can be walked over (without being attacked)
bool Entity::GetDoormat() {
    return doormat_;
}

// is this entity a living thing?
bool Entity::GetLiving() {
    return living_;
}

// is this entity dead (living things can be dead)
bool Entity::GetDead() {
    return dead_;
}

// return the entity's colour pair
short Entity::GetColorPair() {
    return color_pair_;
}

// the most default entity just sits around doing nothing
void Entity::Brain(map_type map, std::vector<Entity*>& entities) {
    return;
}

void Entity::CheckDead(std::vector<Entity*>& residents) {
}

// for both the following methods, the entity can move out of bounds. i don't care.
void Entity::MoveAttack(int dy, int dx, map_type map, std::vector<Entity*> residents) {
    int new_y = y_ + dy;
    int new_x = x_ + dx;

    for (Entity* target : residents) {
        // check if each entity is in the way of this movement
        if (target->GetY() == new_y && target->GetX() == new_x) {
            // if it's not an ally, it's alive, and it isn't a doormat
            if (target->GetFaction() != GetFaction() && !target->GetDead() && target->active_ && !target->GetDoormat()) {
                // damage roll can be up to maximum roll
                std::uniform_int_distribution<> damage_range(0, stats_[2]);

                // the damage is equal to a roll plus the bonus stat
                int damage = damage_range(kRng) + stats_[3];

                // apply that damage
                target->TakeDamage(damage);

                // print a message about the attack
                main_log->AddMessage(std::string("").append(name_)
                        .append(std::string(" attacks ")).append(target->GetName())
                        .append(" for ").append(std::to_string(damage)).append(" damage!"));
                return;
            } else if (!target->GetDoormat()){
                // otherwise, if the entity isn't a doormat, interrupt this movement
                return;
            }
        }
    }

    // if nothing was in the way, move into that spot
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
Inventory* Entity::GetInventory() {
    return &inventory_;
}

// return the total weight carried by this entity
float Entity::GetInvenWeight() {
    float weight = 0;
    for (auto item : inventory_.GetItems()) {
        weight += item->GetWeight()*item->count_;
    }
    return weight;
}

// add an item to this entity's inventory
void Entity::PickupItem(Item* item){
    inventory_.AddItem(item);
}

// take everything from another entity's inventory into this one's
void Entity::TakeItems(Entity* other_entity) {
    Inventory* other_inventory = other_entity->GetInventory();
    // first get items
    if (other_inventory->GetItems().size() > 0 && other_entity != this) {
        for (auto item : other_inventory->GetItems()) {
            Inventory::TryMove(other_inventory, &this->inventory_, item);
        }

        // then remove them all from the target
         /*
        for (std::pair<Item, int> item : *other_inventory) {
            other_inventory->erase(item.first);
        }*/
    }
}

// drop an item on the ground, spawning an ItemEntity for it
bool Entity::DropItem(Item* item, std::vector<Entity*>& entities) {
    auto item_it = inventory_.FindItem(item);
    // check that the item exists in the other entity's inventory
    if (item_it != inventory_.GetItems().end()) {
        int count = item->count_;
        if (count > 0) {
            std::string description;

            // change the description based on how many there are
            if (count > 1) {
                description = std::to_string(count).append("x ").append(item->GetName());
            } else {
                description = std::string("A ").append(item->GetName());
            }

            // create the ItemEntity
            ItemEntity* new_entity = new ItemEntity(
                    item->GetName(),
                    description,
                    GetY(),
                    GetX(),
                    item->GetName()[0]);
            // add it to the entities vector
            entities.push_back(new_entity);

            // move the item into the ItemEntity's inventory
            Inventory::TryMove(&inventory_, (*std::find(entities.begin(), entities.end(), new_entity))->GetInventory(), item);

            return true;
        }
    }
    return false;
}

// unimplemented
void Entity::EquipItem(){
}

void Entity::DequipItem(){
}

void Entity::UseItem(){
}

// eat an item, calling its consume method, with entity pointer to this entity
bool Entity::ConsumeItem(ComestibleItem* item){
    if (item->count_ > 0) {
        item->Consume(this);
        item->count_--;
        return true;
    } else {
        return false;
    }
}


// non-blind entity
std::vector<std::vector<bool>> NonBlindEntity::GetFOV() {
    return FOV.SpiralPath(y_, x_);
}

// updated the transparentmap of an entity that can see
void NonBlindEntity::UpdateFOVTransparent(std::array<std::array<bool, kMapWidth>, kMapHeight> transparentmap) {
    for (int y = 0; y < kMapHeight; y++) {
        for (int x = 0; x < kMapWidth; x++) {
            FOV.transparentmap_[y][x] = transparentmap[y][x];
        }
    }
}

// Item entity update function
void ItemEntity::Brain(map_type map, std::vector<Entity*>& entities) {
    int total_count = 0;
    for (auto item : inventory_.GetItems()) {
        total_count += item->count_;
    }
    if (total_count <= 0) {
        // disable this entity if it's empty
        active_ = false;
    }
};
