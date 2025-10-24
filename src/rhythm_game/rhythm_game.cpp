#include "rhythm_game.h"

#include "bn_core.h"
#include "bn_blending.h"
#include "bn_blending_actions.h"
#include "bn_music_items.h"
#include "bn_music.h"
#include "bn_log.h"
#include "bn_string.h"
#include "score_screen.h"
#include "maxmod.h"

#include "bn_regular_bg_items_fretboard.h"
#include "bn_regular_bg_items_ry_guitar.h"
#include "bn_sprite_items_common_variable_8x16_font.h"

Rhythm_Game::Rhythm_Game(const songs::song& song_selection) :
    ry_bg(bn::regular_bg_items::ry_guitar.create_bg(0, 0)),
    fretboard_bg(bn::regular_bg_items::fretboard.create_bg(0, 0)),
    song(song_selection),
    text_generator(bn::sprite_font(bn::sprite_items::common_variable_8x16_font))
{
    fretboard_bg.set_blending_enabled(true);
    bn::blending::set_transparency_alpha(0);

    text_generator.set_center_alignment();
    display_text();

    // Calculate note offset based on note travel time, song tempo and note speed
    bn::fixed travel_time_frames = bn::fixed(148) / config::note_speed; // 148 is distance from note spawn position to centre of fretboard
    int travel_time_ticks = int(travel_time_frames * bn::timers::ticks_per_frame());
    int rows_per_second = song.tempo * 4 / 60; // 4 rows per beat
    int ticks_per_row = bn::timers::ticks_per_second() / rows_per_second;
    note_offset = (travel_time_ticks + ticks_per_row / 2) / ticks_per_row; // +0.5 to round to nearest int
    BN_LOG("Note offset (rows): ", note_offset);
}

void Rhythm_Game::update()
{
    song_setup();

    frame_count++;

    int current_pattern = mmGetPosition();
    int current_row = mmGetPositionRow();
    int absolute_row = 0;

    // First pattern has 32 rows, subsequent patterns have 64 rows
    if (current_pattern == 0) 
    {
        absolute_row = current_row;
    } 
    else
    {
        absolute_row = 32 + (current_pattern - 1) * 64 + current_row;
    }

    BN_LOG("Pattern: ", current_pattern, " Row: ", current_row, " tick: ", mmGetPositionTick(), " Abs Row: ", absolute_row);
    BN_LOG("offset row: ", absolute_row + note_offset);
    if (absolute_row + note_offset >= song.notes[current_note_index].timestamp && 
        current_note_index < song.size) 
    {
        active_notes.emplace_back(song.notes[current_note_index]);
        current_note_index++;
    }

    update_notes();
    check_inputs();

    // Check for end of song
    if (current_note_index >= song.size && active_notes.empty()) 
    {
        BN_LOG("Score: ", score); // TODO: add score, combo etc

        BN_LOG("Max combo: ", max_combo);

        bn::music::stop();
        // TODO - throw this into a function and do some score stuff, combos etc
        go_to_hub = true;
    }

    display_text();

    if (hit_popup.has_value())
    {
        hit_popup->update();
        if (hit_popup->to_delete())
        {
            hit_popup.reset();
        }
    }
}

State *Rhythm_Game::next_state()
{
    if(go_to_hub)
    {
        score_data data = {
            score,
            max_combo,
            notes_hit,
            notes_missed,
            perfect_notes,
            great_notes,
            good_notes,
            poor_notes
        };
        return new Score_Screen(data);
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

void Rhythm_Game::song_setup()
{
    if(!setup_done)
    {
        setup_fretboard();
        song_timer.restart();
        song.audio.play(1.0, false); // TODO - select song from menu
        // Allow a few frames for maxmod to update positions
        for (int i = 0; i < 3; i++) {
            bn::core::update();
        }
        setup_done = true;
        return;
    }
}

// Doesn't seem to be a way to get the currently pressed button, so we check each one
void Rhythm_Game::check_inputs()
{
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
}

void Rhythm_Game::check_for_hit(bn::keypad::key_type button)
{
    bool hit = false;
    for(int i  = 0; i < active_notes.size() ; i++)
    {
        // checking if > 0 here bc it removes the need to normalise the hit position if it's in the top half
        if(active_notes[i].current_note_data.button == button 
            && active_notes[i].get_position().y() > 0)
        {
            int distance_from_hit_zone = abs(int(active_notes[i].get_position().y()) - hit_zone);

            if(distance_from_hit_zone <= hit_perfect/2)
            {
                BN_LOG("Perfect!");
                update_score(100);
                active_notes.erase(active_notes.begin() + i);
                update_combo();
                hit = true;
                display_popup(HIT_TYPE_PERFECT);
                perfect_notes++;
            }
            else if(distance_from_hit_zone <= hit_great/2)
            {
                BN_LOG("Great!");
                update_score(75);
                active_notes.erase(active_notes.begin() + i);
                update_combo();
                hit = true;
                display_popup(HIT_TYPE_GREAT);
                great_notes++;
            }
            else if(distance_from_hit_zone <= hit_good/2)
            {
                BN_LOG("Good!");
                update_score(50);
                active_notes.erase(active_notes.begin() + i);
                update_combo();
                hit = true;
                display_popup(HIT_TYPE_GOOD);
                good_notes++;
            }
            else if(distance_from_hit_zone <= hit_poor/2)
            {
                BN_LOG("Poor!");
                update_score(25);
                active_notes.erase(active_notes.begin() + i);
                update_combo();
                hit = true;
                display_popup(HIT_TYPE_POOR);
                poor_notes++;
            }
        }
        if (hit)
        {
            notes_hit++;
            break;
        }
    }
    if(!hit)
    {
        end_combo();
    }
}

void Rhythm_Game::update_notes()
{
    // de-increments (is that a word?) because deletion may change the index of later notes in the loop
    for (int i = active_notes.size() - 1; i >= 0; i--)
    {
        active_notes[i].update();

        if (active_notes[i].missed_this_frame())
        {
            end_combo();
            notes_missed++;
            display_popup(HIT_TYPE_MISS);
        }

        if (active_notes[i].to_delete()) 
        {
            active_notes.erase(active_notes.begin() + i);
        }
    }
}

void Rhythm_Game::update_score(int score_to_add)
{
    if (current_combo >= 40)
    {
        score_to_add *= 4;
    }
    else if (current_combo >= 30)
    {
        score_to_add *= 3;
    }
    else if (current_combo >= 20)
    {
        score_to_add *= 2;
    }
    else if (current_combo >= 10)
    {
        score_to_add *= 1.5;
    }
    
    score += score_to_add;
}

void Rhythm_Game::update_combo()
{
    current_combo++;
    if (current_combo > max_combo)
    {
        max_combo = current_combo;
    }
}

// short method, but more readable so it felt better
void Rhythm_Game::end_combo()
{
    current_combo = 0;
}

void Rhythm_Game::display_text()
{
    text_sprites.clear();

    // this seems to be the cleanest way to get things into bn::strings
    bn::string<32> score_string = "Score: ";
    score_string += bn::to_string<10>(score);
    bn::string<32> max_combo_string = "Combo: ";
    max_combo_string += bn::to_string<10>(current_combo);

    text_generator.generate(-60, 72, score_string, text_sprites);
    text_generator.generate(60, 72, max_combo_string, text_sprites);
}

void Rhythm_Game::display_popup(hit_type type)
{
    hit_popup = Hit_Popup(type);
}
