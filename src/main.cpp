#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_items_temp_ry.h"

int main()
{
    bn::core::init();  

    bn::sprite_ptr temp_ry_sprite = bn::sprite_items::temp_ry.create_sprite(0, 0);

    while(true)
    {
        bn::core::update();
    }
}
