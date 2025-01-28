#ifndef BN_SPRITE_ITEMS_TEMP_RY_H
#define BN_SPRITE_ITEMS_TEMP_RY_H

#include "bn_sprite_item.h"

//{{BLOCK(temp_ry_bn_gfx)

//======================================================================
//
//	temp_ry_bn_gfx, 16x32@4, 
//	+ palette 16 entries, not compressed
//	+ 8 tiles Metatiled by 2x4 not compressed
//	Total size: 32 + 256 = 288
//
//	Time-stamp: 2025-01-26, 02:45:42
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TEMP_RY_BN_GFX_H
#define GRIT_TEMP_RY_BN_GFX_H

#define temp_ry_bn_gfxTilesLen 256
extern const bn::tile temp_ry_bn_gfxTiles[8];

#define temp_ry_bn_gfxPalLen 32
extern const bn::color temp_ry_bn_gfxPal[16];

#endif // GRIT_TEMP_RY_BN_GFX_H

//}}BLOCK(temp_ry_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item temp_ry(sprite_shape_size(sprite_shape::TALL, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(temp_ry_bn_gfxTiles, 8), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(temp_ry_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

