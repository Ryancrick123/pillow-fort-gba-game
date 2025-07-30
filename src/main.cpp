#include "bn_core.h"

#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"
#include "state.h"
#include "hub.h"
#include "song_menu.h"

#include "rhythm_game.h"

#include "bn_sprite_items_common_variable_8x16_font.h"

int main() 
{
    bn::core::init();

    State* current_state = new Song_Menu();

    while(true)
    {
        if(current_state)
        {
            current_state->update();
            
            State* next_state = current_state->next_state();
            if(next_state)
            {
                delete current_state;
                current_state = next_state;
            }
        }
        else
        {
            break;
        }

        bn::core::update();
    }
}