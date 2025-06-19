#include "note.h"
#include "bn_sprite_items_buttons.h"

Note::Note(bn::camera_ptr& cam, note_data note_data) :
    current_note_data(note_data),
    current_sprite(select_sprite())
{
    current_sprite.set_camera(cam);
}

void Note::update()
{
    set_position();

    if (int(current_sprite.position().y()) > 60)
    {
        marked_for_deletion = true;
    }
}

void Note::set_position()
{
    bn::fixed new_y = current_sprite.position().y() + current_note_data.descent_speed;
    current_sprite.set_y(new_y);
}

bool Note::to_delete()
{
    return marked_for_deletion;
}

bn::sprite_ptr Note::select_sprite()
{
    switch (current_note_data.button)
    {
        case bn::keypad::key_type::A:
            return bn::sprite_items::buttons.create_sprite(-96, -100, 0); // A button sprite
        case bn::keypad::key_type::B:
            return bn::sprite_items::buttons.create_sprite(-72, -100, 1); // B button sprite
        case bn::keypad::key_type::UP:
            return bn::sprite_items::buttons.create_sprite(-48, -100, 2); // Up button sprite
        case bn::keypad::key_type::DOWN:
            return bn::sprite_items::buttons.create_sprite(-24, -100, 3); // Down button sprite
        case bn::keypad::key_type::LEFT:
            return bn::sprite_items::buttons.create_sprite(0, -100, 4); // Left button sprite
        case bn::keypad::key_type::RIGHT:
            return bn::sprite_items::buttons.create_sprite(24, -100, 5); // Right button sprite
        case bn::keypad::key_type::L:
            return bn::sprite_items::buttons.create_sprite(48, -100, 6); // L button sprite
        case bn::keypad::key_type::R:
            return bn::sprite_items::buttons.create_sprite(72, -100, 7); // R button sprite
        default:
            return bn::sprite_items::buttons.create_sprite(96, -100, 0); // Default to A button sprite
    }
}