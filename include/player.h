#ifndef PLAYER_H
#define PLAYER_H

#include "bn_sprite_ptr.h"


class Player {
public:
    Player(bn::camera_ptr& cam);
    void update(bn::fixed new_position_x, bn::fixed new_position_y);

private:
    bn::sprite_ptr sprite_pointer;
};

#endif