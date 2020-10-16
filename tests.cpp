#include <iostream>
#include <array>

#include "constants.h"
#include "entity.h"
#include "environment.h"

// define ground tile
Tile test_floor = Tile{false, true, 3, 4, ' ', false, false};
// create test map
std::array<std::array<Tile, kMapWidth>, kMapHeight> map;

bool test_entity_move(Entity* entity) {
    std::vector<Entity*> entities;
    entities.push_back(entity);
    // test movement in all axes
    entity->MoveAttack(0,1, map, entities);
    if (entity->GetX() != 1) return false;
    entity->MoveAttack(1,0, map, entities);
    if (entity->GetY() != 1) return false;
    entity->MoveAttack(0,-1, map, entities);
    if (entity->GetX() != 0) return false;
    entity->MoveAttack(-1,0, map, entities);
    if (entity->GetY() != 0) return false;
    return true;
}

bool test_entity_health(Entity* entity) {
    entity->TakeDamage(5);
    if (entity->GetHP() != 5) return false;
    entity->Heal(2);
    if (entity->GetHP() != 7) return false;
    return true;
}

bool test_entity() {
    bool all_ok = true;

    // define test entity 
    Entity entity("Test Entity", "This is an entity made for testing", 0, 0, 'T');

    bool move_ok = test_entity_move(&entity);

    if (move_ok) {
        std::cout << "Testing entity movement......\tOK" << std::endl;
    } else {
        std::cout << "Testing entity movement......\tERROR!!" << std::endl;
        all_ok = false;
    }

    bool health_ok = test_entity_health(&entity);

    if (health_ok) {
        std::cout << "Testing entity health......\tOK" << std::endl;
    } else {
        std::cout << "Testing entity health......\tERROR!!" << std::endl;
        all_ok = false;
    }

    return all_ok;
}

int main() {
    // keeps track of if any errors happened
    bool some_error = false;


    //fill test map with floors
    for (int i = 0; i < kMapHeight; i++) {
        map[i].fill(test_floor);
    }

    some_error = (test_entity() == false);

    if (some_error) {
        std::cout << "WARNING! Some Errors Occured!" << std::endl;
    }
}
