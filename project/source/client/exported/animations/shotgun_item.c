#include <genesis.h>
#include "shotgun_item.h"
#include "engine\FrameTriggers.h"


const unsigned short const shotgun_itemTileData[32] = // 2 tiles 
{
// tile: 0
    0x0022, 0x2200,
    0x0266, 0x6620,
    0x2666, 0x6662,
    0x2699, 0x9962,
    0x21ff, 0xff12,
    0x0f11, 0x11f0,
    0x2f44, 0x4412,
    0x21ff, 0xff42,
// tile: 1
    0x2411, 0x11f2,
    0x0f44, 0x44f0,
    0x01ff, 0xff10,
    0x2411, 0x1142,
    0x2699, 0x9962,
    0x2666, 0x6662,
    0x0266, 0x6620,
    0x0022, 0x2200,
};

const GGSprite shotgun_itemSprite0 = 
{
    -4, // x position offset
    -8, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(1, 2), // sgdk sprite size
};

const GGSprite* const shotgun_itemSpriteArray0[1] = 
{
    &shotgun_itemSprite0,
};

extern const GGFrame shotgun_itemFrame0;





const GGFrame shotgun_itemFrame0 = 
{
    shotgun_itemSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    3, // frame time
    &shotgun_itemFrame0, // loop to next frame. 
};

const GGFrame* const shotgun_itemFrames[1] = 
{
    &shotgun_itemFrame0,
};



const GGAnimation shotgun_item = 
{
    STANDARD_ANIMATION_RESOURCE_TYPE,
    shotgun_itemFrames,
    1, // number of frames
    8, // width in pixels
    16, // height in pixels
    2, // max tiles per frame
    2, // the total number of tiles in the animation
    (const u32*)shotgun_itemTileData, // start of the sprite data
    NULL, // frame trigger data blob
};
