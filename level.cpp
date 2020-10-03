#include "level.h"

Level::Level() {
    for (int i = 0; i < kMapHeight; i++) {
        map_[i].fill(Tile{false, true, 0, ' '});
    }
}
