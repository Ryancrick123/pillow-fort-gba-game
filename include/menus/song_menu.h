#ifndef SONG_MENU_H
#define SONG_MENU_H

#include "state.h"

#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_actions.h"
#include "bn_regular_bg_animate_actions.h"

class Song_Menu : public State {
public:
    Song_Menu();
    void update() override;
    State* next_state() override;

private:
    void write_song_name();
    bn::sprite_text_generator text_generator;
    bn::vector<bn::sprite_ptr, 64> text_sprites;
    bn::regular_bg_item background_item;
    bn::regular_bg_ptr background;
    bn::regular_bg_cached_animate_action<4> background_animation;
    bool go_to_rhythm_game = false;
    int current_index = 0;
    bn::sprite_ptr left;
    bn::sprite_ptr right;
    bn::sprite_move_loop_action left_action;
    bn::sprite_move_loop_action right_action;
};

#endif