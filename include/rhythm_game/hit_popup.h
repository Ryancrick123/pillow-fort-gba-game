#ifndef HIT_POPUP_H
#define HIT_POPUP_H

#include "bn_sprite_item.h"
#include "bn_sprite_animate_actions.h"
#include "bn_timer.h"

enum hit_type {
    HIT_TYPE_PERFECT,
    HIT_TYPE_GREAT,
    HIT_TYPE_GOOD,
    HIT_TYPE_POOR,
    HIT_TYPE_MISS
};

class Hit_Popup {

public:
    Hit_Popup(hit_type type);
    void update();
    bool to_delete();
    

private:
    
    bn::sprite_item select_sprite(hit_type type);
    bn::sprite_item sprite_item;
    bn::sprite_ptr sprite;
    bn::sprite_animate_action<2> action;
    bn::timer timer;
    int lifetime_in_seconds = 1.5;
    bool marked_for_deletion = false;
};

#endif