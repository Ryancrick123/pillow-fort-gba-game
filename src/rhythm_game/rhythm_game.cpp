#include "rhythm_game.h"

#include "bn_core.h"
#include "bn_blending.h"
#include "bn_blending_actions.h"
#include "bn_music_items.h"
#include "bn_timers.h"
#include "hub.h"
#include "bn_log.h"

#include "bn_regular_bg_items_fretboard.h"
#include "bn_regular_bg_items_ry_guitar.h"

Rhythm_Game::Rhythm_Game(const songs::song& song_selection) :
    ry_bg(bn::regular_bg_items::ry_guitar.create_bg(0, 0)),    
    fretboard_bg(bn::regular_bg_items::fretboard.create_bg(0, 0)),
    song(song_selection)
{
    fretboard_bg.set_blending_enabled(true);
    bn::blending::set_transparency_alpha(0);
}

void Rhythm_Game::update()
{
    if(!setup_done)
    {
        setup_fretboard();
        song_timer.restart();
        bn::music_items::joan_test.play(1.0, false);
        setup_done = true;
        return;
    }

    // TODO: clean this up, it's sketchy and has some manual tweaks - BPM we're setting is to be multiplied by 4 for this calculation
    int offset = 148 * bn::timers::ticks_per_frame(); // offset to account for note travel time (manually calculated, but we can do better)
    int beats_per_second = song.tempo * 4 / 60;
    int ticks_per_beat = bn::timers::ticks_per_second() / beats_per_second;
    int elapsed_beats = (song_timer.elapsed_ticks() + offset) / ticks_per_beat;

    //BN_LOG("Elapsed beats: ", elapsed_beats);


    // creating new notes
    if (elapsed_beats >= song.notes[current_note_index].timestamp && 
        current_note_index < song.size) 
    {
        active_notes.emplace_back(song.notes[current_note_index]);
        current_note_index++;
    }

    // checking notes for deletion - de-increments (is that a word?) because deletion may change the index of later notes in the loop
    for (int i = active_notes.size() - 1; i >= 0; i--)
    {
        active_notes[i].update();

        if (active_notes[i].to_delete()) 
        {
            active_notes.erase(active_notes.begin() + i);
        }
    }

    // cgeck for inputs
    if(bn::keypad::any_pressed())
    {
        if(bn::keypad::a_pressed())
        {
            check_for_hit(bn::keypad::key_type::A);
        }
        if(bn::keypad::b_pressed())
        {
            check_for_hit(bn::keypad::key_type::B);
        }
        if(bn::keypad::r_pressed())
        {
            check_for_hit(bn::keypad::key_type::R);
        }
        if(bn::keypad::l_pressed())
        {
            check_for_hit(bn::keypad::key_type::L);
        }
        if(bn::keypad::up_pressed())
        {
            check_for_hit(bn::keypad::key_type::UP);
        }
        if(bn::keypad::down_pressed())
        {
            check_for_hit(bn::keypad::key_type::DOWN);
        }
        if(bn::keypad::left_pressed())
        {
            check_for_hit(bn::keypad::key_type::LEFT);
        }
        if(bn::keypad::right_pressed())
        {
            check_for_hit(bn::keypad::key_type::RIGHT);
        }

    }

    // Check for end of song
    if (current_note_index >= song.size && active_notes.empty()) 
    {
        BN_LOG("Score: ", score); // TODO: add score, combo etc
        // TODO - throw this into a function and do some score stuff, combos etc
        go_to_hub = true;
    }
}

State *Rhythm_Game::next_state()
{
    if(go_to_hub)
    {
        return new Hub();
    }
    return nullptr;
}

// fades in and stops further actions until fully faded in
void Rhythm_Game::setup_fretboard()
{
    bn::blending_transparency_alpha_to_action transparency_action(60, 1);
    while(int(bn::blending::transparency_alpha()) < 1)
    {
        transparency_action.update();
        bn::core::update();
    }
    fretboard_bg.set_blending_enabled(false);
}

void Rhythm_Game::check_for_hit(bn::keypad::key_type button)
{

    for(int i  = 0; i < active_notes.size() ; i++)
    {
        // checking if > 0 here bc it removes the need to normalise the hit position if it's in the top half
        if(active_notes[i].current_note_data.button == button 
            && active_notes[i].get_position().y() > 0)
        {
            int distance_from_hit_zone = abs(int(active_notes[i].get_position().y()) - hit_zone);

            BN_LOG(active_notes[i].get_position().y());
            if(distance_from_hit_zone <= hit_perfect/2)
            {
                BN_LOG("Perfect!");
                score += 100;
                active_notes.erase(active_notes.begin() + i);
            }
            else if(distance_from_hit_zone <= hit_great/2)
            {
                BN_LOG("Great!");
                score += 75;
                active_notes.erase(active_notes.begin() + i);
            }
            else if(distance_from_hit_zone <= hit_good/2)
            {
                BN_LOG("Good!");
                score += 50;
                active_notes.erase(active_notes.begin() + i);
            }
            else if(distance_from_hit_zone <= hit_sloppy/2)
            {
                BN_LOG("Sloppy!");
                score += 25;
                active_notes.erase(active_notes.begin() + i);
            }
        }
    }
}
