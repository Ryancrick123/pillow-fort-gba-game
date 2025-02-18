#include "player.h"
#include "collision_handler.h"
#include "bn_camera_ptr.h"
#include "bn_keypad.h"
#include "bn_log.h"

#include "bn_sprite_items_temp_ry.h"

// Constructor
Player::Player(bn::camera_ptr& cam, CollisionHandler& handler, int x, int y) 
    : sprite_pointer(bn::sprite_items::temp_ry.create_sprite(x, y)), 
    collision_handler(handler) 
{
    // Initialize player properties
    sprite_pointer.set_camera(cam);
}

// Method to update player state
void Player::update(bool check_input) {
    // Update code
    if(check_input) {
        move();
    }

    

    BN_LOG("Sprite position: ", sprite_pointer.x(), " ", sprite_pointer.y());
}

// this is duplicated, gotta move it all to the player class
void Player::move() {

    bn::fixed_point new_position = sprite_pointer.position();
    
    if(bn::keypad::left_held()) {
        new_position.set_x(new_position.x() - 1);
    }
    else if(bn::keypad::right_held()) {
        new_position.set_x(new_position.x() + 1);
    }
    if (bn::keypad::up_held()) {
        new_position.set_y(new_position.y() - 1);
    }
    else if (bn::keypad::down_held()) {
        new_position.set_y(new_position.y() + 1);
    }

    if (collision_handler.check_collision(int(new_position.x()), int(new_position.y()))) {
        BN_LOG("Collision detected");
    }
    else {
        BN_LOG("No collision detected");
        sprite_pointer.set_position(new_position);
    }
}