#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_items_temp_ry.h"
#include "bn_keypad.h"

int main()
{
    bn::core::init();  

    bn::sprite_ptr temp_ry_sprite = bn::sprite_items::temp_ry.create_sprite(0, 0);

    while(true)
    {
        if(bn::keypad::left_held())
            {
                temp_ry_sprite.set_x(temp_ry_sprite.x() - 1);
            }
            else if(bn::keypad::right_held())
            {
                temp_ry_sprite.set_x(temp_ry_sprite.x() + 1);
            }

            if(bn::keypad::up_held())
            {
                temp_ry_sprite.set_y(temp_ry_sprite.y() - 1);
            }
            else if(bn::keypad::down_held())
            {
                temp_ry_sprite.set_y(temp_ry_sprite.y() + 1);
            }
        bn::core::update();
    }
}
