#ifndef SCORE_SCREEN_H
#define SCORE_SCREEN_H

#include "state.h"

#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_timers.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_animate_actions.h"
#include "score_data.h"

class Score_Screen : public State
{
    public:
        Score_Screen(score_data::score_data data_from_game);
        void update() override;
        State* next_state() override;

    private:
        bn::sprite_text_generator text_generator;
        score_data::score_data data;
        bn::vector<bn::sprite_ptr, 64> text_sprites;
        bn::timer freeze_timer;
        bool go_to_hub = false;
        bn::regular_bg_item background_item;
        bn::regular_bg_ptr background;
        bn::regular_bg_cached_animate_action<4> background_animation;
};

#endif