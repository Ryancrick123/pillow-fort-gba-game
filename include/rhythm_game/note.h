#ifndef NOTE_H
#define NOTE_H

#include "bn_array.h"
#include "bn_keypad.h"
#include "bn_camera_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"

enum note_type {
        normal,
        bonus
    };

struct note_data {
        bn::keypad::key_type button;
        int timestamp;
        int descent_speed;
        note_type type;
    };

// Base class for all actors to inherit
class Note {
    
public:
    Note(bn::camera_ptr& cam, note_data note_data);
    void update();
    void set_position();
    bool to_delete();
    
private:
    bn::sprite_ptr select_sprite();
    bool marked_for_deletion = false;
    note_data current_note_data;
    bn::sprite_ptr current_sprite;
};

#endif // NOTE_H
