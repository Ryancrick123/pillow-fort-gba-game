#include "note.h"
#include "bn_sprite_items_buttons.h"
#include "config.h"

Note::Note(note_data note_data) :
    current_note_data(note_data),
    current_sprite(select_sprite())
{
}

void Note::update()
{
    set_position();

    if (int(current_sprite.position().y()) > 100)
    {
        marked_for_deletion = true;
    }
}

void Note::set_position()
{
    bn::fixed new_y = current_sprite.position().y() + config::note_speed;

    // Make notes rush off screen once missed
    if (int(current_sprite.position().y()) > 57)
    {
        new_y = current_sprite.position().y() + (4 * config::note_speed);
    }
    
    current_sprite.set_y(new_y);
}

bool Note::to_delete()
{
    return marked_for_deletion;
}

// to be called from rhythm_game to break combos
bool Note::missed_this_frame()
{
    if (!missed && int(current_sprite.position().y()) > 56)
    {
        missed = true;
        return true;
    }
    return false;
}

const bn::fixed_point& Note::get_position() const
{
    return current_sprite.position();
}

bn::sprite_ptr Note::select_sprite()
{
    switch (current_note_data.button)
    {
        case bn::keypad::key_type::L:
            return bn::sprite_items::buttons.create_sprite(-84, -100, 6); // L button sprite
        case bn::keypad::key_type::UP:
            return bn::sprite_items::buttons.create_sprite(-60, -100, 2); // UP button sprite
        case bn::keypad::key_type::DOWN:
            return bn::sprite_items::buttons.create_sprite(-36, -100, 3); // DOWN button sprite
        case bn::keypad::key_type::LEFT:
            return bn::sprite_items::buttons.create_sprite(-12, -100, 4); // LEFT button sprite
        case bn::keypad::key_type::RIGHT:
            return bn::sprite_items::buttons.create_sprite(12, -100, 5); // RIGHT button sprite
        case bn::keypad::key_type::B:
            return bn::sprite_items::buttons.create_sprite(36, -100, 1); // B button sprite
        case bn::keypad::key_type::A:
            return bn::sprite_items::buttons.create_sprite(60, -100, 0); // A button sprite
        case bn::keypad::key_type::R:
            return bn::sprite_items::buttons.create_sprite(84, -100, 7); // R button sprite
        default:
            return bn::sprite_items::buttons.create_sprite(108, -100, 0); // Default sprite (A button)
    }
}