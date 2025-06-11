#ifndef SONGS_H
#define SONGS_H

#include "bn_array.h"
#include "bn_keypad.h"

#include "note.h"

namespace songs
{
    struct song {
        const note_data* notes; // Pointer to the first element of the array of notes
        int size; // Number of notes in the song
        const char* name; // Name of the song
    };

    constexpr bn::array<note_data, 5> test_song_data = {{
        {bn::keypad::key_type::A, 0, 1, normal},
        {bn::keypad::key_type::B, 1, 2, normal},
        {bn::keypad::key_type::B, 5, 2, normal},
        {bn::keypad::key_type::B, 6, 2, normal},
        {bn::keypad::key_type::B, 7, 4, normal}
    }};

    constexpr song test_song = {
        test_song_data.data(),
        test_song_data.size(),
        "Test Song"
    };
}

#endif // SONGS_H