#include "player.h"
#include "collision_handler.h"
#include "bn_camera_ptr.h"
#include "bn_keypad.h"
#include "bn_log.h"

//#include "bn_sprite_items_temp_ry.h"

// Constructor - maybe to remove unless I add extra stuff later
Player::Player(bn::camera_ptr& cam, CollisionHandler& collision_handler, bn::sprite_item sprite_item, int x, int y) 
    : Actor(cam, collision_handler, sprite_item, x, y) 
{
}

// Method to update player state
void Player::update() {
    bn::fixed_point new_position = get_current_sprite().position();
    
    if(bn::keypad::left_held()) {
        new_position.set_x(new_position.x() - 1);
    }
    else if(bn::keypad::right_held()) {
        new_position.set_x(new_position.x() + 1);
    }
    if(bn::keypad::up_held()) {
        new_position.set_y(new_position.y() - 1);
    }
    else if(bn::keypad::down_held()) {
        new_position.set_y(new_position.y() + 1);
    }

    if(check_actor_collision(new_position)) {
        BN_LOG("Collision detected");
    }
    else {
        BN_LOG("No collision detected");
        set_position(new_position);
    }
}