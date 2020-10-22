#include <iostream>
#include <array>

#include "constants.h"
#include "entity.h"
#include "environment.h"
#include "item.h"
#include "inventory.h"
#include "spiralpath.h"
#include "level.h"

// define ground tile
Tile test_floor = Tile{false, true, 3, 4, ' ', false, false};
// create test map
std::array<std::array<Tile, kMapWidth>, kMapHeight> map;

void testvar(int& errors, std::string text, int var, int expected) {
    std::cout << "Testing " << text << "......\t";
    if (var != expected) {
        std::cout << "ERROR! Expected " << expected << " , got " << var << std::endl;
        errors++;
    } else {
        std::cout << "OK" << std::endl;
    }
}

int test_entity_move(Entity* entity) {
    std::vector<Entity*> entities;
    entities.push_back(entity);
    int errors = 0;
    // test movement in all axes
    entity->MoveAttack(0,1, map, entities);
    testvar(errors, "entity positive x movement", entity->GetX(), 1);
    entity->MoveAttack(1,0, map, entities);
    testvar(errors, "entity positive y movement", entity->GetY(), 1);
    entity->MoveAttack(0,-1, map, entities);
    testvar(errors, "entity negative x movement", entity->GetX(), 0);
    entity->MoveAttack(-1,0, map, entities);
    testvar(errors, "entity negative y movement", entity->GetY(), 0);
    return errors;
}

int test_entity_health(Entity* entity) {
    entity->TakeDamage(5);
    int errors = 0;
    testvar(errors, "entity damage by 5", entity->GetHP(), 5);
    entity->Heal(2);
    testvar(errors, "entity heal by 2", entity->GetHP(), 7);
    return errors;
}

int test_entity() {
    int total_errors = 0;

    // define test entity
    Entity entity("Test Entity", "This is an entity made for testing", 0, 0, 'T');


    std::cout << std::endl << "Testing entity movement......" << std::endl;
    int move_error = test_entity_move(&entity);

    if (move_error) {
        if (move_error == 1) std::cout << move_error << "error occurred while testing movement!" << std::endl;
        else std::cout << move_error << " errors occurred while testing movement!" << std::endl;
        total_errors += move_error;
    }

    std::cout << std::endl << "Testing entity health......" << std::endl;
    int health_error = test_entity_health(&entity);

    if (health_error) {
        if (health_error == 1) std::cout << move_error << "error occurred while testing health!" << std::endl;
        else std::cout << move_error << " errors occurred while testing health!" << std::endl;
        total_errors += health_error;
    }

    return total_errors;
}

int test_inventory_additem() {
    int errors = 0;
    Inventory inventory;
    Item* item = new Item("Test item", 10.0, 1.0);

    std::cout << "Testing item exists in vector......\t";
    inventory.AddItem(item);
    if (inventory.FindItem(item) == inventory.GetItems().end()) {
        std::cout << "ERROR! Expected iterator to item position, got end() iterator" << std::endl;;
        errors++;
    } else {
        std::cout << "OK" << std::endl;
    }

    inventory.AddItem(item);
    testvar(errors, "that adding item again increases count", (*inventory.FindItem(item))->count_, 2);

    return errors;
}

int test_inventory_transfer() {
    int errors = 0;
    Inventory i1;
    Inventory i2;
    Item* item = new Item("Test item", 10.0, 1.0);
    i1.AddItem(item);

    Inventory::TryMove(&i1, &i2, item);
    testvar(errors, "item exists in destination", i2.FindItem(item) != i2.GetItems().end(), 1);
    testvar(errors, "item no longer exists in source", i1.FindItem(item) != i1.GetItems().end(), 0);

    return errors;
}

int test_inventory() {
    int total_errors = 0;

    std::cout << std::endl << "Testing adding items to inventory......" << std::endl;
    int adding_errors = test_inventory_additem();
    if (adding_errors) {
        if (adding_errors == 1) std::cout << adding_errors << " error occurred while testing item adding!" << std::endl;
        else std::cout << adding_errors << " errors occurred while testing item adding!" << std::endl;
    }
    total_errors += adding_errors;

    std::cout << "Testing moving items between inventories......" << std::endl;
    int moving_errors = test_inventory_transfer();
    if (moving_errors) {
        if (moving_errors == 1) std::cout << moving_errors << " error occurred while testing item transfer!" << std::endl;
        else std::cout << moving_errors << " errors occurred while testing item transfer!" << std::endl;
    }
    total_errors += moving_errors;

    return total_errors;
}

int test_fov() {
    int total_errors = 0;

    std::cout << std::endl << "Testing FOV......" << std::endl;

    std::vector<std::vector<bool>> test_map;
    test_map.resize(5);
    for (int row = 0; row < 5; row++) {
        test_map[row].resize(5);
        for (int col = 0; col < 5; col++) {
            if (row == 0 || row == 4 || col == 0 || col == 4 || (col == 2 && row == 2)) {
                test_map[row][col] = false;
            } else test_map[row][col] = true;
        }
    }

    SpiralPathFOV test_fov(5,5,5,0,2*M_PI);
    test_fov.transparentmap_ = test_map;
    std::vector<std::vector<bool>> lit_map = test_fov.SpiralPath(3, 2);

    testvar(total_errors, "pillar blocks sight", lit_map[1][2], 0);
    testvar(total_errors, "adjacent squares lit (-1, 0)", lit_map[2][2], 1);
    testvar(total_errors, "adjacent squares lit (-1, 1)", lit_map[2][3], 1);
    testvar(total_errors, "adjacent squares lit (0, 1)", lit_map[3][3], 1);
    testvar(total_errors, "adjacent squares lit (1, 1)", lit_map[4][3], 1);
    testvar(total_errors, "adjacent squares lit (1, 0)", lit_map[4][2], 1);
    testvar(total_errors, "adjacent squares lit (1, -1)", lit_map[4][1], 1);
    testvar(total_errors, "adjacent squares lit (0, -1)", lit_map[3][1], 1);
    testvar(total_errors, "adjacent squares lit (-1, -1)", lit_map[2][1], 1);
    testvar(total_errors, "adjacent squares lit (0, 0)", lit_map[3][2], 1);

    return total_errors;
}

int test_level() {
    int total_errors = 0;

    std::cout << std::endl << "Testing entity movement between levels" << std::endl;

    Entity* entity = new Entity("Test Entity", "This is an entity made for testing", 0, 0, 'T');

    Level level1;
    level1.entities_.push_back(entity);
    Level level2 = level1.NextFloor();

    Level::TryMoveEntity(&level1, &level2, entity);
    testvar(total_errors, "entity exists in destination", std::find(level2.entities_.begin(), level2.entities_.end(), entity) != level2.entities_.end(), 1);
    testvar(total_errors, "entity no longer exists in source", std::find(level1.entities_.begin(), level1.entities_.end(), entity) != level1.entities_.end(), 0);

    return total_errors;
}

int main() {
    // keeps track of if any errors happened
    int errors = 0;


    //fill test map with floors
    for (int i = 0; i < kMapHeight; i++) {
        map[i].fill(test_floor);
    }

    errors += test_entity();
    errors += test_inventory();
    errors += test_fov();
    errors += test_level();

    if (errors) {
        if (errors == 1) {
            std::cout << "WARNING! " << errors << " error occurred!" << std::endl;
        }
        else {
            std::cout << "WARNING! " << errors << " errors occurred!" << std::endl;
        }
    } else {
        std::cout << "No errors occurred." << std::endl;
    }
}
