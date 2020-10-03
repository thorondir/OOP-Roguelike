#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <array>

#include "entity.h"
#include "environment.h"
#include "constants.h"

class Level {
    public:
        Level();

        std::vector<Entity> entities_;
        std::array<std::array<Tile, kMapWidth>, kMapHeight> map_;
    private:
        std::vector<Room> rooms;

        void GenerateRooms();
        void ApplyRooms();
        void PopulateRooms();
};

#endif
