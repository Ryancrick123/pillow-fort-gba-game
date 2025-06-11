#include "note.h"
#include "bn_sprite_items_temp_ry.h"

Note::Note(bn::camera_ptr& cam, note_data note_data) :
    current_sprite(bn::sprite_items::temp_ry.create_sprite(0, -100)),
    current_note_data(note_data)
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