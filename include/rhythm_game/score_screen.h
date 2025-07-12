#ifndef SCORE_SCREEN_H
#define SCORE_SCREEN_H

#include "state.h"

#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_timers.h"

class Score_Screen : public State
{
    public:
        Score_Screen(int score, int max_combo);
        void update() override;
        State* next_state() override;

    private:
        bn::sprite_text_generator text_generator;
        int score;
        int max_combo;
        bn::vector<bn::sprite_ptr, 64> text_sprites;
        bn::timer freeze_timer;
        bool go_to_hub = false;
};

#endif // SCORE_SCREEN_H