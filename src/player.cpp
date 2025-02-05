#include "player.h"
#include "bn_camera_ptr.h"

#include "bn_sprite_items_temp_ry.h"

// Constructor
Player::Player(bn::camera_ptr& cam) : sprite_pointer(bn::sprite_items::temp_ry.create_sprite(0, 0)) {
    // Initialize player properties
    sprite_pointer.set_camera(cam);
}

// Method to update player state
void Player::update(bn::fixed new_position_x, bn::fixed new_position_y) {
    // Update code
    sprite_pointer.set_position(new_position_x, new_position_y);
}