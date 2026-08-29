#ifndef CONFIG_H
#define CONFIG_H

#include "bn_fixed.h"

namespace config
{
    constexpr bn::fixed note_speed = 2.0;

    // TODO: Check if needed to separate builds
    // enum play_mode { HARDWARE, EMULATOR };
    // constexpr play_mode mode = HARDWARE; // Change this to compile for emulator or hardware
}

#endif