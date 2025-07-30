#include "score_screen.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_sprite_items_common_variable_8x16_font.h"
#include "bn_regular_bg_items_song_selection_menu.h"

#include "hub.h"
#include "song_menu.h"

Score_Screen::Score_Screen(score_data data_from_game) :
    text_generator(bn::sprite_font(bn::sprite_items::common_variable_8x16_font)),
    data(data_from_game),
    background_item(bn::regular_bg_items::song_selection_menu),
    background(background_item.create_bg(0, 0)),
    background_animation(bn::create_regular_bg_cached_animate_action_forever(background, 15, background_item.map_item(), 0, 1, 2, 3))
{
    text_generator.set_center_alignment();
    
    // this seems to be the cleanest way to get things into bn::strings
    bn::string<32> score_string = "Score: ";
    score_string += bn::to_string<10>(data.score);
    bn::string<32> max_combo_string = "Combo: ";
    max_combo_string += bn::to_string<10>(data.max_combo);

    text_generator.generate(0, -40, score_string, text_sprites);
    text_generator.generate(0, 40, max_combo_string, text_sprites);
}

void Score_Screen::update()
{
    background_animation.update();
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
        return new Song_Menu();
    }
    
    return nullptr;
}
