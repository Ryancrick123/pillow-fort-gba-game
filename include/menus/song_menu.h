#ifndef SONG_MENU_H
#define SONG_MENU_H

#include "state.h"

#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"

class Song_Menu : public State {
public:
    Song_Menu();
    void update() override;
    State* next_state() override;

private:
    void write_song_name();
    bn::sprite_text_generator text_generator;
    bn::vector<bn::sprite_ptr, 64> text_sprites;
    bool go_to_rhythm_game = false;
    int current_index = 0;
};

#endif