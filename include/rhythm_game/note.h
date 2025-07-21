#ifndef NOTE_H
#define NOTE_H

#include "bn_array.h"
#include "bn_keypad.h"
#include "bn_camera_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"

struct note_data {
        bn::keypad::key_type button;
        int timestamp;
        int descent_speed;
    };

// Base class for all actors to inherit
class Note {
    
public:
    Note(note_data note_data);
    void update();
    void set_position();
    bool to_delete();
    bool missed_this_frame();
    const bn::fixed_point& get_position() const;
    note_data current_note_data;
    
private:
    bn::sprite_ptr select_sprite();
    bool marked_for_deletion = false;
    bn::sprite_ptr current_sprite;
    bool missed = false;
};

#endif
