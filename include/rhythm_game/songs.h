#ifndef SONGS_H
#define SONGS_H

#include "bn_array.h"
#include "bn_keypad.h"
#include "bn_music_items.h"

#include "note.h"

namespace songs
{

    enum song_type {
        normal,
        bonus
    };

    struct song {
        const note_data* notes;
        int size; // Number of notes in the song
        int tempo;
        const char* name;
        song_type type;
        int unlock_requirement; // Number of completed songs required to unlock, 0 means no requirement
        bn::music_item audio;
        bool is_unlocked(int completed_songs) const {
            return completed_songs >= unlock_requirement;
        }
    };
}

#endif