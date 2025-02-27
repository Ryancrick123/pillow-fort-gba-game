#include "player.h"
#include "collision_handler.h"
#include "bn_camera_ptr.h"
#include "bn_keypad.h"
#include "bn_log.h"

#include "bn_sprite_items_temp_ry.h"

// Constructor
Player::Player(bn::camera_ptr& cam, CollisionHandler& collision_handler, bn::sprite_item sprite_item, int x, int y) 
    : Actor(cam, collision_handler, sprite_item, x, y) 
{
}

// Method to update player state
void Player::update() {
    bn::fixed_point new_position = get_current_sprite().position();
    direction new_direction = get_current_direction();
    
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

    set_current_direction(new_direction);

    if(check_actor_collision(new_position)) {
        BN_LOG("Collision detected");
    }
    else {
        BN_LOG("No collision detected");
        set_position(new_position);
    }
}

/*
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
    */