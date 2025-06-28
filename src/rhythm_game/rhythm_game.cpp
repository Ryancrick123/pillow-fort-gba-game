#include "rhythm_game.h"

#include "bn_core.h"
#include "bn_regular_bg_ptr.h"
#include "bn_blending.h"
#include "bn_blending_actions.h"
#include "bn_vector.h"
#include "bn_music_items.h"
#include "bn_timer.h"
#include "bn_timers.h"

#include "bn_regular_bg_items_fretboard.h"

Rhythm_Game::Rhythm_Game(const songs::song& song, bn::camera_ptr &cam)
{
    setup_fretboard();

    // vector used for dynamic creation of notes
    bn::vector<Note, 100> active_notes;
    int current_note_index = 0;

    bn::timer song_timer;
    bn::music_items::joan_test.play(0.5, false);

    while(true)
    {
        // using seconds right now - might want to use ticks instead for more precision when I use actual music
        int elapsed_seconds = song_timer.elapsed_ticks()/ bn::timers::ticks_per_second();

        if (elapsed_seconds >= song.notes[current_note_index].timestamp) 
        {
            active_notes.emplace_back(cam, song.notes[current_note_index]);
            current_note_index++;
        }

        // de-increments (is that a word?) because deletion may change the index of later notes in the loop
        for (int i = active_notes.size() - 1; i >= 0; i--)
        {
            active_notes[i].update();

            if (active_notes[i].to_delete()) 
            {
                active_notes.erase(active_notes.begin() + i);
            }
        }

        if (current_note_index >= song.size && active_notes.empty()) 
        {
            break;
        }

        bn::core::update();
    }
}

// Creates the fretboard background - fades in and stops further actions until fully faded in
void Rhythm_Game::setup_fretboard()
{
    // set up fretboard for hit detection
    bn::regular_bg_ptr fretboard = bn::regular_bg_items::fretboard.create_bg(0, 0);
    //fretboard.set_camera(cam);
    fretboard.set_blending_enabled(true);
    bn::blending::set_transparency_alpha(0);
    bn::blending_transparency_alpha_to_action transparency_action(60, 1);
    while(int(bn::blending::transparency_alpha()) < 1)
    {
        transparency_action.update();
        bn::core::update();
    }
    fretboard.set_blending_enabled(false);
}
