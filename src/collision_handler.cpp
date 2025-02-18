#include "collision_handler.h"

#include "bn_regular_bg_map_cell_info.h"
#include "bn_log.h"

CollisionHandler::CollisionHandler(bn::regular_bg_item& bg_item) : collision_bg_item(bg_item) {
    setup_map(bg_item);
}

void CollisionHandler::setup_map(bn::regular_bg_item& new_collision_bg_item) {
    // Get the index of the tile at the specified cell
    collision_bg_item = new_collision_bg_item;

    invalid_tile_index = bn::regular_bg_map_cell_info(collision_bg_item.map_item().cell(0, 0)).tile_index();

    width = collision_bg_item.map_item().dimensions().width() * 8;
    height = collision_bg_item.map_item().dimensions().height() * 8;
}

bool CollisionHandler::check_collision(int x, int y) {
    // adding width/2 standardizes so 0,0 is in the center of the screen 
    int cell_x = (x % width + width + width / 2) % width / 8;
    int cell_y = (y % height + height + height / 2) % width / 8;

    BN_LOG("cell: ",  cell_x, " ", cell_y);

    // Get the index of the tile at the specified cell and compare to see if it's invalid
    bn::regular_bg_map_cell target_cell = collision_bg_item.map_item().cell(cell_x, cell_y);
    int target_tile_index = bn::regular_bg_map_cell_info(target_cell).tile_index();

    if(target_tile_index == invalid_tile_index) {
        return true;
    }

    /*bn::regular_bg_map_cell new_map_cell = map_item.cell((new_position.x() % 64 + 64) % 64, (new_position.y() % 64 + 64) % 64);
    int new_tile_index = bn::regular_bg_map_cell_info(new_map_cell).tile_index();
    */
    return false;
}