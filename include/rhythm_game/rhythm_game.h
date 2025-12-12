#ifndef RHYTHM_GAME_H
#define RHYTHM_GAME_H

#include "state.h"

#include "bn_regular_bg_ptr.h"
#include "songs.h"
#include "bn_keypad.h"
#include "bn_timers.h"
#include "bn_sprite_text_generator.h"
#include "hit_popup.h"
#include "config.h"

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
    int frame_count = 0;
    int current_note_index = 0;
    bn::vector<Note, 100> active_notes;
    const songs::song& song;
    bool go_to_hub = false;
    bool setup_done = false;
    int hit_zone = 48; // 80 (bottom of screen) - 32 (height of centre of fretboard)
    int hit_perfect = 4; 
    int hit_great = 8;
    int hit_good = 12;
    int hit_poor = 16;
    int score = 0;
    int current_combo = 0;
    int max_combo = 0;
    int notes_hit = 0;
    int notes_missed = 0;
    int perfect_notes = 0;
    int great_notes = 0;
    int good_notes = 0;
    int poor_notes = 0;
    int ticks_per_beat = 0;
    int note_offset;
    bn::sprite_text_generator text_generator;
    bn::vector<bn::sprite_ptr, 32> text_sprites;
    bn::optional<Hit_Popup> hit_popup;
    void setup_fretboard();
    void song_setup();
    void check_for_hit(bn::keypad::key_type button);
    void check_inputs();
    void update_notes();
    void update_score(int score_to_add);
    void update_combo();
    void end_combo();
    void display_text();
    void display_popup(hit_type type);
    void calculate_note_offset();
};

#endif