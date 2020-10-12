#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <array>
#include <algorithm>

#include "entity.h"
#include "player.h"
#include "environment.h"
#include "constants.h"
#include "rng.h"

class Level {
    public:
        Level();
        ~Level();

        std::vector<Entity*> entities_;

        std::array<std::array<Tile, kMapWidth>, kMapHeight> map_;
        std::vector<Room> GetRooms();

    private:
        std::vector<Room> rooms_;

        void GenerateRooms();
        void GenerateTunnels();
        void ApplyRooms();
        void PopulateRooms();
};

#endif
