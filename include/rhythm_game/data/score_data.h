#ifndef SCORE_DATA_H
#define SCORE_DATA_H

namespace score_data
{
    struct score_data
    {
        int song_index;
        int score;
        int max_combo;
        int notes_hit;
        int notes_missed;
        int perfect_notes;
        int great_notes;
        int good_notes;
        int poor_notes;
    };
}

#endif