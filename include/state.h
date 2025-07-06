#ifndef STATE_H
#define STATE_H

#include "bn_timer.h"
#include "bn_vector.h"

class State {
public:
    virtual ~State() = default;
    virtual void update() = 0;
    virtual void pause() {}; // TODO - set up pausing
    virtual State* next_state() = 0; // To return a state, or nullptr if no next state
};

#endif