#ifndef PLAYER_H
#define PLAYER_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"

#include "collision_handler.h"

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player {
public:
    Player(bn::camera_ptr& cam, CollisionHandler& handler, int x = 0, int y = 0);
    void update(bool check_input = false);
    bool player_collision(bn::fixed_point position);

private:
    CollisionHandler& collision_handler;
    bn::sprite_item ry_sprite_item;
    bn::sprite_ptr sprite;
    direction current_direction;

    void move();
    void set_direction(direction new_direction);
};

#endif