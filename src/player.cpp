#include "player.h"
#include "collision_handler.h"
#include "bn_camera_ptr.h"
#include "bn_keypad.h"
#include "bn_log.h"

#include "bn_sprite_items_temp_ry.h"

// Constructor
Player::Player(bn::camera_ptr& cam, CollisionHandler& handler, int x, int y) 
    : collision_handler(handler),
    ry_sprite_item(bn::sprite_items::temp_ry),
    sprite(ry_sprite_item.create_sprite(x, y, 0)),
    current_direction(DOWN)
{
    // Initialize player properties
    sprite.set_camera(cam);
}

// Method to update player state
void Player::update(bool check_input) {
    // Update code
    if(check_input) {
        move();
    }

    BN_LOG("Sprite position: ", sprite.x(), " ", sprite.y());
}

void Player::move() {

    bn::fixed_point new_position = sprite.position();
    direction new_direction = current_direction;
    
    if(bn::keypad::left_held()) {
        new_position.set_x(new_position.x() - 1);
        new_direction = LEFT;
    }
    else if(bn::keypad::right_held()) {
        new_position.set_x(new_position.x() + 1);
        new_direction = RIGHT;
    }
    if(bn::keypad::up_held()) {
        new_position.set_y(new_position.y() - 1);
        new_direction = UP;
    }
    else if(bn::keypad::down_held()) {
        new_position.set_y(new_position.y() + 1);
        new_direction = DOWN;
    }

    set_direction(new_direction);

    if(player_collision(new_position)) {
        BN_LOG("Collision detected");
    }
    else {
        BN_LOG("No collision detected");
        sprite.set_position(new_position);
    }
}

void Player::set_direction(direction new_direction) {
    if(current_direction == new_direction) return;

    if(new_direction == UP) {
        sprite = ry_sprite_item.create_sprite(sprite.x(), sprite.y(), 2);
        current_direction = UP;
    }
    else if(new_direction == DOWN) {
        sprite = ry_sprite_item.create_sprite(sprite.x(), sprite.y(), 0);
        current_direction = DOWN;
    }
    else if(new_direction == LEFT) {
        sprite = ry_sprite_item.create_sprite(sprite.x(), sprite.y(), 3);
        current_direction = LEFT;
    }
    else if(new_direction == RIGHT) {
        sprite = ry_sprite_item.create_sprite(sprite.x(), sprite.y(), 1);
        current_direction = RIGHT;
    }
}

// Check an area around the bottom of the player sprite for collision
// @param position: The position to check for collision
// @return True if collision detected, false if no collision
bool Player::player_collision(bn::fixed_point position) {
    // +- small numbers to hardcode offset accounting for empty space
    // bottom
    if (collision_handler.check_collision(int(position.x()), int(position.y()) - 1 + sprite.dimensions().height() / 2)) {
        return true;
    }
    // left
    if (collision_handler.check_collision(int(position.x()) - sprite.dimensions().width() / 2 + 2, int(position.y()) + sprite.dimensions().height() / 2)) {
        return true;
    }
    // right
    if (collision_handler.check_collision(int(position.x()) + sprite.dimensions().width() / 2 - 3, int(position.y()) + sprite.dimensions().height() / 2)) {
        return true;
    }
    // top
    if (collision_handler.check_collision(int(position.x()), int(position.y()) - 4 + sprite.dimensions().height() / 2 )) {
        return true;
    }
    
    return false;
}