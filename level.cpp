#include "level.h"

Tile wall = Tile{true, false, 1, ' '};
Tile ground = Tile{false, true, 0, ' '};

int max_rooms = 15;
int min_rooms = 10;

int min_room_size = 3;
int max_room_size = 10;

std::uniform_int_distribution<> room_y_distribution(1, kMapHeight-max_room_size-1);
std::uniform_int_distribution<> room_x_distribution(1, kMapWidth-max_room_size-1);
std::uniform_int_distribution<> room_size_distribution(min_room_size, max_room_size);
std::uniform_int_distribution<> number_rooms_distribution(min_rooms, max_rooms);

Level::Level() {
    // initialise blank tiles
    for (int i = 0; i < kMapHeight; i++) {
        map_[i].fill(wall);
    }

    GenerateRooms();
    ApplyRooms();
    PopulateRooms();
}

std::array<std::array<Tile, kMapWidth>, kMapHeight> Level::GetMap() {
    return map_;
}

void Level::GenerateRooms() {
    // generate a random number of rooms
    int y,x,width,height;
    bool room_ok;
    for (int i = 0; i < number_rooms_distribution(kRng); i++) {
        room_ok = false;
        while (room_ok == false) {
            y = room_y_distribution(kRng);
            x = room_x_distribution(kRng);
            width = room_size_distribution(kRng);
            height = room_size_distribution(kRng);

            room_ok = true;
            // discard rooms if they overlap with other rooms. this allows for edges to overlap, but i think that's cool so i'm leaving it that way
            for (Room room : rooms_) {
                if (!(((room.GetX1() < x && room.GetX2() < x) || (room.GetX1() > x + width && room.GetX2() > x + width)) || ((room.GetY1() < y && room.GetY2() < y) || (room.GetY1() > y + height && room.GetY2() > y + height)))) {
                    room_ok = false;
                    break;
                }
            }

        }
        rooms_.push_back(Room(y, x, width, height));
    }
    
    
    // now create the tunnels between rooms. these are, at least for the time being, represented as more rooms
    int num_rooms = rooms_.size();
    for (int i = 0; i < num_rooms - 1; i++) {
        // distributions for target points
        std::uniform_int_distribution<> origin_y(rooms_[i].GetY1(), rooms_[i].GetY2());
        std::uniform_int_distribution<> origin_x(rooms_[i].GetX1(), rooms_[i].GetX2());
        std::uniform_int_distribution<> target_y(rooms_[i+1].GetY1(), rooms_[i+1].GetY2());
        std::uniform_int_distribution<> target_x(rooms_[i+1].GetX1(), rooms_[i+1].GetX2());
        // coinflip for x or y first
        std::bernoulli_distribution y_first(0.5);

        // generate the point the tunnel should go to
        int target[2] = {target_y(kRng), target_x(kRng)};

        // REVISIT THIS LATER AND MAKE SURE IT DOES WHAT IT'S SUPPOSED TO!
        if (y_first(kRng)) {
            int corner_x = origin_x(kRng);
            if (!(target[0] >= rooms_[i].GetY1() && target[0] <= rooms_[i].GetY2())) { // if target y doesn't require a vertical tunnel, don't bother
                if (target[0] < rooms_[i].GetY1()){ // if the tunnel needs to go up
                    rooms_.push_back(Room(target[0], corner_x, 1, rooms_[i].GetY1() - target[0]));
                } else { // otherwise, travel down first
                    rooms_.push_back(Room(rooms_[i].GetY2() + 1, corner_x, 1, target[0] - rooms_[i].GetY2()));
                }
            }
            if (target[1] < corner_x) { // if the tunnel needs to go left
                // used corner_x - 1 so edges of tunnel "rooms" don't overlap
                rooms_.push_back(Room(target[0], rooms_[i+1].GetX2() + 1, (corner_x - 1) - rooms_[i+1].GetX2(), 1));
            } else { // otherwise travel right
                // used corner_x + 1 so edges of tunnel "rooms" don't overlap
                rooms_.push_back(Room(target[0], corner_x + 1, rooms_[i+1].GetX1() - (corner_x + 1), 1));
            }
        } else {
            int corner_y = origin_y(kRng);
            if (!(target[1] >= rooms_[i].GetX1() && target[1] <= rooms_[i].GetX2())) { // if target x doesn't require a horizontal tunnel, don't bother
                if (target[1] < rooms_[i].GetX1()) { // if the tunnel needs to go left
                    rooms_.push_back(Room(corner_y, target[1], rooms_[i].GetX1() - target[1], 1));
                } else { // otherwise travel right
                    rooms_.push_back(Room(corner_y, rooms_[i].GetX2() + 1, target[1] - rooms_[i].GetX2(), 1));
                }
            }
            if (target[0] < corner_y) { // if the tunnel needs to go up
                rooms_.push_back(Room(rooms_[i+1].GetY2() + 1, target[1], 1, (corner_y - 1) - rooms_[i+1].GetY2()));
            } else { // otherwise travel down
                rooms_.push_back(Room(corner_y + 1, target[1], 1, (rooms_[i+1].GetY1() - 1) - corner_y));
            }
        }
    }

}

void Level::ApplyRooms() {
    for (Room room : rooms_) {
        for (int y = 0; y < room.GetHeight(); y++) {
            for (int x = 0; x < room.GetWidth(); x++) {
                map_[room.GetY1() + y][room.GetX1() + x] = ground;
            }
        }
    }
}

void Level::PopulateRooms() {
    entities_.push_back(Player((rooms_[0].GetY1() + rooms_[0].GetY2())/2, (rooms_[0].GetX1() + rooms_[0].GetX2())/2));
}
