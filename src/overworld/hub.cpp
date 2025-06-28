#include "hub.h"

#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"

#include "player.h"
#include "collision_handler.h"

#include "bn_sprite_items_temp_ry.h"
#include "bn_regular_bg_items_test_map_collision.h"
#include "bn_regular_bg_items_test_map_floor.h"
#include "bn_regular_bg_items_test_map_world.h"

Hub::Hub(bn::camera_ptr& camera)
{
    // THIS NEEDS HEAVY CLEANUP

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
    Player player(camera, collision_handler, bn::sprite_items::temp_ry);

    while(true)
    {
        player.update();

        bn::core::update();
    }
}