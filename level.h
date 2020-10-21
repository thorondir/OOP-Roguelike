#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <array>
#include <algorithm>

#include "entity.h"
#include "enemy.h"
#include "environment.h"
#include "constants.h"
#include "rng.h"

class Level {
    public:
        Level();
        ~Level();

        Level NextFloor();

        static void TryMoveEntity(Level*, Level*, Entity*);

        std::vector<Entity*> entities_;

        int GetUpStairY();
        int GetUpStairX();
        int GetDownStairY();
        int GetDownStairX();

        std::array<std::array<Tile, kMapWidth>, kMapHeight> map_;
        std::array<std::array<bool, kMapWidth>, kMapHeight> GetTransparent();
        std::vector<Room> GetRooms();

        void FreeEntities();

    private:
        std::vector<Room> rooms_;

        int up_stair_y, up_stair_x, down_stair_y, down_stair_x;

        void GenerateRooms();
        void GenerateTunnels();
        void ApplyRooms();
        void PopulateRooms();
};

#endif
