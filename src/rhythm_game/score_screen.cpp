#include "score_screen.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_sprite_items_common_variable_8x16_font.h"

#include "hub.h"

Score_Screen::Score_Screen(int score_from_song, int max_combo_from_song) :
    text_generator(bn::sprite_font(bn::sprite_items::common_variable_8x16_font)),
    score(score_from_song),
    max_combo(max_combo_from_song)
{
    text_generator.set_center_alignment();
    
    // this seems to be the cleanest way to get things into bn::strings
    bn::string<32> score_string = "Score: ";
    score_string += bn::to_string<10>(score);
    bn::string<32> max_combo_string = "Combo: ";
    max_combo_string += bn::to_string<10>(max_combo);

    text_generator.generate(0, -40, score_string, text_sprites);
    text_generator.generate(0, 40, max_combo_string, text_sprites);
}

void Score_Screen::update()
{
    if (freeze_timer.elapsed_ticks() < 3 * bn::timers::ticks_per_second())
    {
        return;
    }

    if (bn::keypad::a_pressed())
    {
        go_to_hub = true;
    }
}

State *Score_Screen::next_state()
{
    if (go_to_hub)
    {
        return new Hub();
    }
    
    return nullptr;
}
