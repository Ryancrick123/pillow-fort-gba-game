#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_keypad.h"
#include "bn_camera_actions.h"
#include "bn_log.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_sprite_text_generator.h"
#include "bn_music_items.h"
#include "bn_vector.h"
#include "bn_timer.h"
#include "bn_timers.h"
#include "bn_blending.h"
#include "bn_blending_actions.h"

#include "player.h"
#include "collision_handler.h"
#include "npc_dialogue.h"
#include "note.h"
#include "songs.h"

#include "bn_sprite_items_temp_ry.h"
#include "bn_regular_bg_items_test_map_floor.h"
#include "bn_regular_bg_items_test_map_world.h"
#include "bn_regular_bg_items_test_map_collision.h"
#include "bn_regular_bg_items_fretboard.h"
#include "bn_sprite_items_common_variable_8x16_font.h"

#include "bn_dmg_music_items_joan_test.h"


// Forward declaration of log_stuff
void log_stuff(bn::sprite_ptr& player, bn::regular_bg_ptr& background, bn::camera_ptr& cam);

void play_rhythm_game(const songs::song& song, bn::camera_ptr& cam);

int main() 
{
    bn::core::init();

    // font testing stuff
    bn::sprite_item font_sprite(bn::sprite_items::common_variable_8x16_font);
    bn::sprite_font font(font_sprite);
    bn::sprite_text_generator text_generator(font);

    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);

    // collision setup
    bn::regular_bg_item collision_bg_item = bn::regular_bg_items::test_map_collision;
    bn::regular_bg_ptr collision_bg = collision_bg_item.create_bg(0, 0);
    collision_bg.set_camera(camera);
    CollisionHandler collision_handler(collision_bg_item);

    // floor setup
    bn::regular_bg_ptr map_bg = bn::regular_bg_items::test_map_floor.create_bg(0, 0);
    map_bg.set_camera(camera);

    // world setup
    bn::regular_bg_ptr world_bg = bn::regular_bg_items::test_map_world.create_bg(0, 0);
    world_bg.set_camera(camera);

    // player setup
    Player player(camera, collision_handler, bn::sprite_items::temp_ry);

    text_generator.set_center_alignment();

    bn::vector<bn::sprite_ptr, 32> text_sprites;

    while(true)
    {
        player.update();

        if(bn::keypad::a_pressed()) {
            text_sprites.clear();
        }
        if(bn::keypad::b_pressed()) {
            text_sprites.clear();
            text_generator.generate(0, 0, "Playing song", text_sprites);
            play_rhythm_game(songs::test_song, camera);
            text_sprites.clear();
            text_generator.generate(0, 0, "Song complete", text_sprites);
        }

        bn::core::update();
    }
}

void log_stuff(bn::sprite_ptr& player, bn::regular_bg_ptr& background, bn::camera_ptr& cam) 
{
    BN_LOG("Camera x: ", cam.x());
    BN_LOG("Camera y: ", cam.y());
    BN_LOG("Sprite x: ", player.x());
    BN_LOG("Sprite y: ", player.y());
    BN_LOG("Background x: ", background.x());
    BN_LOG("Background y: ", background.y());
}

void play_rhythm_game(const songs::song& song, bn::camera_ptr& cam)
{
    // set up fretboard for hit detection
    bn::regular_bg_ptr fretboard = bn::regular_bg_items::fretboard.create_bg(0, 0);
    fretboard.set_camera(cam);
    fretboard.set_blending_enabled(true);
    bn::blending::set_transparency_alpha(0);
    bn::blending_transparency_alpha_to_action transparency_action(60, 1);
    while(int(bn::blending::transparency_alpha()) < 1)
    {
        transparency_action.update();
        bn::core::update();
    }
    fretboard.set_blending_enabled(false);

    // vector used for dynamic creation of notes
    bn::vector<Note, 100> active_notes;
    int current_note_index = 0;

    bn::timer song_timer;
    bn::music_items::joan_test.play(0.5, false);
    //bn::dmg_music_items::joan_test.play();

    // rhythm game loop
    while(true)
    {
        // using seconds right now - might want to use ticks instead for more precision when I use actual music

        int elapsed_seconds = song_timer.elapsed_ticks()/ bn::timers::ticks_per_second();

        BN_LOG("Elapsed seconds: ", elapsed_seconds);

        if (elapsed_seconds >= song.notes[current_note_index].timestamp) 
        {
            active_notes.emplace_back(cam, song.notes[current_note_index]);
            current_note_index++;
        }

        // de-increments (is that a word?) because deletion may change the index of later notes in the loop
        for (int i = active_notes.size() - 1; i >= 0; i--)
        {
            active_notes[i].update();

            if (active_notes[i].to_delete()) 
            {
                active_notes.erase(active_notes.begin() + i);
            }
        }

        if (current_note_index >= song.size && active_notes.empty()) 
        {
            BN_LOG("All notes played, ending song.");
            break;
        }

        bn::core::update();
    }

}
