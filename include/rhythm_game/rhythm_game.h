#ifndef RHYTHM_GAME_H
#define RHYTHM_GAME_H

#include "state.h"

#include "bn_regular_bg_ptr.h"
#include "songs.h"
#include "bn_keypad.h"

class Rhythm_Game : public State
{
public:
    Rhythm_Game(const songs::song& song_selection);
    void update() override;
    State* next_state() override;

private:
    bn::regular_bg_ptr ry_bg;
    bn::regular_bg_ptr fretboard_bg;
    bn::timer song_timer;
    int current_note_index = 0;
    bn::vector<Note, 100> active_notes;
    const songs::song& song;
    bool go_to_hub = false;
    bool setup_done = false;
    int hit_zone = 48; // 80 (bottom of screen) - 32 (height of centre of fretboard)
    int hit_perfect = 6; 
    int hit_great = 12;
    int hit_good = 18;
    int hit_sloppy = 24;
    int score = 0;
    void setup_fretboard();
    void check_for_hit(bn::keypad::key_type button);
};

#endif