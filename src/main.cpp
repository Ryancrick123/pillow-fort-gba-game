#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_keypad.h"
#include "bn_camera_actions.h"
#include "bn_log.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_regular_bg_map_cell_info.h"

#include "player.h"

#include "bn_sprite_items_temp_ry.h"
#include "bn_regular_bg_items_floor.h"

// Forward declaration of log_stuff
void log_stuff(bn::sprite_ptr& player, bn::regular_bg_ptr& background, bn::camera_ptr& cam);


int main()
{
    bn::core::init();

    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);

    // Create player object
    
    
    bn::regular_bg_ptr map_bg = bn::regular_bg_items::floor.create_bg(0, 0);
    bn::regular_bg_map_item map_item = bn::regular_bg_items::floor.map_item();
    bn::regular_bg_map_cell invalid_map_cell = map_item.cell(0, 0);
    int invalid_tile_index = bn::regular_bg_map_cell_info(invalid_map_cell).tile_index();

    Player player(camera);


    bn::sprite_ptr temp_test = bn::sprite_items::temp_ry.create_sprite(100, 40);

    bn::point player_map_position(0, 0);

    while(true)
    {
        bn::point new_position = player_map_position;

        temp_test.set_camera(camera);
        map_bg.set_camera(camera);

        //log_stuff(temp_ry_sprite, map_bg, camera);

        // Move the player sprite
        if(bn::keypad::left_held())
        {
            new_position.set_x(new_position.x() - 1);
        }
        else if(bn::keypad::right_held())
        {
            new_position.set_x(new_position.x() + 1);
        }
        if (bn::keypad::up_held())
        {
            new_position.set_y(new_position.y() - 1);
        }
        else if (bn::keypad::down_held())
        {
            new_position.set_y(new_position.y() + 1);
        }

        // getting cell of next move
        bn::regular_bg_map_cell new_map_cell = map_item.cell((new_position.x() % 64 + 64) % 64, (new_position.y() % 64 + 64) % 64);
        int new_tile_index = bn::regular_bg_map_cell_info(new_map_cell).tile_index();
        BN_LOG("New tile index: ", new_tile_index);

        // check if invalid tile
        // TODO: find tiles programatically
        if(new_tile_index > 8)
        {
            player_map_position = new_position;
        }

        // calculate position of player sprite in screen coordinates
        bn::fixed player_x = (player_map_position.x() * 8) - (map_item.dimensions().width() * 4) + 4;
        bn::fixed player_y = (player_map_position.y() * 8) - (map_item.dimensions().height() * 4) + 4;

        player.update(player_x, player_y);
        camera.set_position(player_x, player_y);

        bn::core::update();
    }
}

void log_stuff(bn::sprite_ptr& player, bn::regular_bg_ptr& background, bn::camera_ptr& cam) 
{
    BN_LOG("Camera x: ", cam.x());
    BN_LOG("Camera y: ", cam.y());
    BN_LOG("Sprite x: ", player.x());
    BN_LOG("Sprite y: ", player.y());
    BN_LOG("Background x: ", background.x());
    BN_LOG("Background y: ", background.y());
}
