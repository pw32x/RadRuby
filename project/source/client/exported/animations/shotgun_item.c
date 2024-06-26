#include <genesis.h>
#include "shotgun_item.h"
#include "engine\FrameTriggers.h"
#include "engine\animation_draw.h"
#include "engine\animation_utils.h"


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

const Ruby_Sprite shotgun_itemSprite0 = 
{
    -4, // x position offset
    -8, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(1, 2), // sgdk sprite size
};

const Ruby_Sprite* const shotgun_itemSpriteArray0[1] = 
{
    &shotgun_itemSprite0,
};

extern const Ruby_Frame shotgun_itemFrame0;





const Ruby_Frame shotgun_itemFrame0 = 
{
    shotgun_itemSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    3, // frame time
    &shotgun_itemFrame0, // next frame
};

const Ruby_Frame* const shotgun_itemFrames[1] = 
{
    &shotgun_itemFrame0,
};

const Ruby_AnimationSetup const shotgun_itemSetup = 
{
    Animation_DrawObject,
    AnimationUtils_updateStandardAnimation,
    &shotgun_itemFrame0,
    0,
    3,
};

u16 shotgun_itemVdpLocation;

const Ruby_Animation shotgun_item = 
{
    STANDARD_ANIMATION_RESOURCE_TYPE,
    &shotgun_itemSetup,
    shotgun_itemFrames,
    1, // number of frames
    8, // width in pixels
    16, // height in pixels
    2, // max tiles per frame
    2, // the total number of tiles in the animation
    (const u32*)shotgun_itemTileData, // start of the sprite data
    NULL, // frame trigger data blob
    &shotgun_itemVdpLocation, // location in vdp when loaded
};
