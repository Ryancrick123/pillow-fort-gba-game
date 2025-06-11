#include "actor.h"

Actor::Actor(bn::camera_ptr& cam, CollisionHandler& collision_handler, bn::sprite_item sprite_item, int x, int y) :
    collision_handler(collision_handler),
    sprite_item(sprite_item),
    current_sprite(sprite_item.create_sprite(x, y, 0)),
    current_direction(DOWN)
{
    current_sprite.set_camera(cam);
}

void Actor::update()
{
    
}

// Check an area around the bottom of the sprite for collision
// @param position: The position to check for collision
// @return True if collision detected, false if no collision
bool Actor::check_actor_collision(bn::fixed_point position){
    // +- small numbers to hardcode offset accounting for empty space
    // bottom
    if (collision_handler.check_collision(int(position.x()), int(position.y()) - 1 + current_sprite.dimensions().height() / 2)) {
        return true;
    }
    // left
    if (collision_handler.check_collision(int(position.x()) - current_sprite.dimensions().width() / 2 + 2, int(position.y()) + current_sprite.dimensions().height() / 2)) {
        return true;
    }
    // right
    if (collision_handler.check_collision(int(position.x()) + current_sprite.dimensions().width() / 2 - 3, int(position.y()) + current_sprite.dimensions().height() / 2)) {
        return true;
    }
    // top
    if (collision_handler.check_collision(int(position.x()), int(position.y()) - 4 + current_sprite.dimensions().height() / 2 )) {
        return true;
    }
    
    return false;
}

// Should run every time the player moves
// @param new_direction: The new direction the player is facing
void Actor::set_current_direction(direction new_direction)
{
    if (current_direction == new_direction) return;

   if (new_direction == UP) {
        current_sprite.set_tiles(sprite_item.tiles_item(), 2);
        current_direction = UP;
    }
    else if (new_direction == DOWN) {
        current_sprite.set_tiles(sprite_item.tiles_item(), 0);
        current_direction = DOWN;
    }
    else if (new_direction == LEFT) {
        current_sprite.set_tiles(sprite_item.tiles_item(), 3);
        current_direction = LEFT;
    }
    else if (new_direction == RIGHT) {
        current_sprite.set_tiles(sprite_item.tiles_item(), 1);
        current_direction = RIGHT;
    }
}

const direction& Actor::get_current_direction() const
{
	return current_direction;
}

void Actor::set_position(bn::fixed_point new_position)
{
    // check if new position is a different direction and set the direction accordingly
    if (int(new_position.y()) < int(current_sprite.position().y())) {
        set_current_direction(UP);
    }
    else if (int(new_position.y()) > int(current_sprite.position().y())) {
        set_current_direction(DOWN);
    }
    else if (int(new_position.x()) < int(current_sprite.position().x())) {
        set_current_direction(LEFT);
    }
    else if (int(new_position.x()) > int(current_sprite.position().x())) {
        set_current_direction(RIGHT);
    }

    current_sprite.set_position(new_position);
    

}

const bn::fixed_point& Actor::get_position() const
{
    return current_sprite.position();
}

const bn::sprite_ptr& Actor::get_current_sprite() const
{
    return current_sprite;
}
