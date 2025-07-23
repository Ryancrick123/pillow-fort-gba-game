#include "song_menu.h"

#include "rhythm_game.h"
#include "bn_keypad.h"
#include "chart_override.h"
#include "song_data.h"

#include "bn_sprite_items_common_variable_8x16_font.h"

Song_Menu::Song_Menu() :
    text_generator(bn::sprite_font(bn::sprite_items::common_variable_8x16_font))
{
    text_generator.set_center_alignment();
    write_song_name();
}

void Song_Menu::update()
{
    if (bn::keypad::right_pressed())
    {
        current_index++;
        int prev_index = bn::max(current_index - 1, 0);
        // Loop song selection and only show one locked song at any given time
        if(current_index >= songs::all_songs.size() || !songs::all_songs[prev_index]->is_unlocked(0))
        {
            current_index = 0;
        }
        write_song_name();
    }
    else if (bn::keypad::left_pressed())
    {
        current_index--;
        if(current_index < 0)
        {
            int last_showable_song_index = 0;
            // this assumes there will always be one song unlocked from the start (should be the case unless modded)
            for(int i = songs::all_songs.size() - 1; i >= 0; --i)
            {
                if(songs::all_songs[i - 1]->is_unlocked(0))
                {
                    last_showable_song_index = i;
                    break;
                }
            }

            current_index = last_showable_song_index;
        }
        write_song_name();
    }

    if(bn::keypad::a_pressed())
    {
        go_to_rhythm_game = true;
    }
}

State *Song_Menu::next_state()
{
    if(go_to_rhythm_game)
    {
        return new Rhythm_Game(*songs::all_songs[current_index]);
    }
    return nullptr;
}

void Song_Menu::write_song_name()
{
    text_sprites.clear();
    text_generator.generate(0, 0, songs::all_songs[current_index]->name, text_sprites);
    if (!songs::all_songs[current_index]->is_unlocked(0))
    {
        text_generator.generate(0, 40, "LOCKED", text_sprites);
    }
}
