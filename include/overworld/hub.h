#ifndef HUB_H
#define HUB_H

#include "state.h"

#include "bn_regular_bg_ptr.h"
#include "player.h"
#include "collision_handler.h"

class Hub : public State {
public:
    Hub();
    void update() override;
    State* next_state() override;

private:
    bn::regular_bg_item collision_bg_item;
    bn::regular_bg_ptr map_bg;
    bn::regular_bg_ptr world_bg;
    CollisionHandler collision_handler;
    Player player;
    bool go_to_rhythm_game = false;
};

#endif