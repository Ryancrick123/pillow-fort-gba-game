#ifndef CHART_OVERRIDE_H
#define CHART_OVERRIDE_H

#include "bn_array.h"
#include "bn_keypad.h"
#include "songs.h"

namespace songs
{
    #define JOAN_OVERRIDE
    constexpr bn::array<note_data, 4> joan_data = {{
        {bn::keypad::key_type::A, 32, 1},
        {bn::keypad::key_type::L, 36, 1},
        {bn::keypad::key_type::R, 40, 1},
        {bn::keypad::key_type::L, 44, 1},
    }};

    constexpr song joan = {
        joan_data.data(),
        joan_data.size(),
        120,
        "Joan",
        normal,
        0,
        bn::music_items::a_joan
    };
}

#endif