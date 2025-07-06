#ifndef PLAYER_H
#define PLAYER_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"

#include "actor.h"
#include "collision_handler.h"

class Player : public Actor {
public:
    Player(CollisionHandler& collision_handler, bn::sprite_item sprite_item, int x = 0, int y = 0);
    void update();
};

#endif