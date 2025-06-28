#ifndef RHYTHM_GAME_H
#define RHYTHM_GAME_H

#include "bn_camera_ptr.h"
#include "songs.h"

class Rhythm_Game {
public:
    Rhythm_Game(const songs::song& song, bn::camera_ptr& cam);

private:
    void setup_fretboard();
};

#endif