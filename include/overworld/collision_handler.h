#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "bn_regular_bg_item.h"

class CollisionHandler {
public:
    CollisionHandler(bn::regular_bg_item& bg_item);
    void setup_map(bn::regular_bg_item& new_collision_bg_item);
    bool check_collision(int x, int y);

private:
    int invalid_tile_index; // The index of the invalid tile
    int width;
    int height;
    bn::regular_bg_item& collision_bg_item;
};

#endif