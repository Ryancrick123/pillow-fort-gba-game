#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_keypad.h"
#include "bn_camera_actions.h"
#include "bn_log.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_regular_bg_map_cell_info.h"

#include "player.h"
#include "collision_handler.h"

#include "bn_sprite_items_temp_ry.h"
#include "bn_regular_bg_items_test_map_floor.h"
#include "bn_regular_bg_items_test_map_world.h"
#include "bn_regular_bg_items_test_map_collision.h"

// Forward declaration of log_stuff
void log_stuff(bn::sprite_ptr& player, bn::regular_bg_ptr& background, bn::camera_ptr& cam);


int main() {
    bn::core::init();

    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);

    // collision setup
    bn::regular_bg_item collision_bg_item = bn::regular_bg_items::test_map_collision;
    bn::regular_bg_ptr collision_bg = collision_bg_item.create_bg(0, 0);
    collision_bg.set_camera(camera);
    CollisionHandler collision_handler(collision_bg_item);

    // floor setup
    bn::regular_bg_ptr map_bg = bn::regular_bg_items::test_map_floor.create_bg(0, 0);
    map_bg.set_camera(camera);


    // world setup
    bn::regular_bg_ptr world_bg = bn::regular_bg_items::test_map_world.create_bg(0, 0);
    world_bg.set_camera(camera);

    // player setup
    Player player(camera, collision_handler);

    //bn::sprite_ptr temp_test = bn::sprite_items::temp_ry.create_sprite(100, 40);

    while(true)
    {
        player.update(true);

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
