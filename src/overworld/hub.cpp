#include "hub.h"

//#include "bn_sprite_ptr.h"

#include "bn_keypad.h"
#include "rhythm_game.h"

#include "bn_sprite_items_temp_ry.h"
#include "bn_regular_bg_items_test_map_collision.h"
#include "bn_regular_bg_items_test_map_floor.h"
#include "bn_regular_bg_items_test_map_world.h"

#include "chart_override.h"
#include "song_data.h"

Hub::Hub() :
    collision_bg_item(bn::regular_bg_items::test_map_collision),
    map_bg(bn::regular_bg_items::test_map_floor.create_bg(0, 0)),
    world_bg(bn::regular_bg_items::test_map_world.create_bg(0, 0)),
    collision_handler(collision_bg_item),
    player(collision_handler, bn::sprite_items::temp_ry)
{
}

void Hub::update()
{
    player.update();
    if(bn::keypad::b_pressed())
    {
        go_to_rhythm_game = true;
    }

}

State *Hub::next_state()
{
    if(go_to_rhythm_game)
    {
        return new Rhythm_Game(songs::joan);
    }
    return nullptr;
}
