#ifndef PLAYER_H
#define PLAYER_H

#include "bn_sprite_ptr.h"
#include "collision_handler.h"


class Player {
public:
    Player(bn::camera_ptr& cam, CollisionHandler& handler, int x = 0, int y = 0);
    void update(bool check_input = false);

private:
    bn::sprite_ptr sprite_pointer;
    void move();
    CollisionHandler& collision_handler;
};

#endif