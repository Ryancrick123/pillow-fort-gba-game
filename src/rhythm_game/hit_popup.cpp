#include "hit_popup.h"

#include "bn_sprite_items_perfect.h"
#include "bn_sprite_items_great.h"
#include "bn_sprite_items_good.h"
#include "bn_sprite_items_poor.h"
#include "bn_sprite_items_miss.h"
#include "bn_timers.h"

Hit_Popup::Hit_Popup(hit_type type) :
    sprite_item(select_sprite(type)),
    sprite(sprite_item.create_sprite(0, 64)),
    action(bn::create_sprite_animate_action_forever(sprite, 15, sprite_item.tiles_item(), 0, 1))
{
    sprite.set_z_order(-1);
}

void Hit_Popup::update()
{
    action.update();

    if (timer.elapsed_ticks() / bn::timers::ticks_per_second() >= lifetime_in_seconds)
    {
        marked_for_deletion = true;
    }
}

bool Hit_Popup::to_delete()
{
    return marked_for_deletion;
}

bn::sprite_item Hit_Popup::select_sprite(hit_type type)
{
    switch(type)
    {
        case HIT_TYPE_PERFECT:
            return bn::sprite_items::perfect;
        case HIT_TYPE_GREAT:
            return bn::sprite_items::great;
        case HIT_TYPE_GOOD:
            return bn::sprite_items::good;
        case HIT_TYPE_POOR:
            return bn::sprite_items::poor;
        case HIT_TYPE_MISS:
            return bn::sprite_items::miss;
    }
}