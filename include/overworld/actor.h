#ifndef ACTOR_H
#define ACTOR_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_camera_ptr.h"

#include "collision_handler.h"

// Direction in screenspace
enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Base class for all actors to inherit
class Actor {
public:
    Actor(CollisionHandler& collision_handler, bn::sprite_item sprite_item, int x = 0, int y = 0);
    void update();
    void set_current_direction(direction new_direction);
    const direction& get_current_direction() const;
    bool check_actor_collision(bn::fixed_point position);
    void set_position(bn::fixed_point new_position);
    const bn::fixed_point& get_position() const;
    const bn::sprite_ptr& get_current_sprite() const;

private:
    CollisionHandler& collision_handler;
    bn::sprite_item sprite_item;
    bn::sprite_ptr current_sprite;
    direction current_direction;
};

#endif