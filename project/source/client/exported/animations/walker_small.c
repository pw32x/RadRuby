#include <genesis.h>
#include "walker_small.h"
#include "engine\FrameTriggers.h"
#include "engine\animation_draw.h"
#include "engine\animation_utils.h"


const unsigned short const walker_smallTileData[32] = // 2 tiles 
{
// tile: 0
    0x0011, 0x1110,
    0x0169, 0xe69e,
    0x1666, 0xf6f1,
    0x1c66, 0x2621,
    0x7766, 0x6677,
    0x7f76, 0x67f7,
    0x1771, 0x1771,
    0x0000, 0x0,
// tile: 1
    0x0011, 0x1110,
    0x0169, 0xe69e,
    0x1666, 0xf6f1,
    0x1c66, 0x2621,
    0x1666, 0x6661,
    0x0166, 0x6610,
    0x001f, 0xf710,
    0x0017, 0x7710,
};

const Ruby_Sprite walker_smallSprite0 = 
{
    -4, // x position offset
    -3, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(1, 1), // sgdk sprite size
};

const Ruby_Sprite walker_smallSprite1 = 
{
    -4, // x position offset
    -4, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 1), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(1, 1), // sgdk sprite size
};

const Ruby_Sprite* const walker_smallSpriteArray0[1] = 
{
    &walker_smallSprite0,
};

const Ruby_Sprite* const walker_smallSpriteArray1[1] = 
{
    &walker_smallSprite1,
};

extern const Ruby_Frame walker_smallFrame0;
extern const Ruby_Frame walker_smallFrame1;





const Ruby_Frame walker_smallFrame0 = 
{
    walker_smallSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    8, // frame time
    &walker_smallFrame1, // next frame
};


const Ruby_Frame walker_smallFrame1 = 
{
    walker_smallSpriteArray1,
    1, // number of sprites
    0, // frame trigger data offset
    8, // frame time
    &walker_smallFrame0, // loop to next frame. 
};

const Ruby_Frame* const walker_smallFrames[2] = 
{
    &walker_smallFrame0,
    &walker_smallFrame1,
};

const Ruby_AnimationSetup const walker_smallSetup = 
{
    Animation_DrawObject,
    AnimationUtils_updateStandardAnimation,
    &walker_smallFrame0,
    0,
    8,
};

u16 walker_smallVdpLocation;

const Ruby_Animation walker_small = 
{
    STANDARD_ANIMATION_RESOURCE_TYPE,
    &walker_smallSetup,
    walker_smallFrames,
    2, // number of frames
    8, // width in pixels
    8, // height in pixels
    1, // max tiles per frame
    2, // the total number of tiles in the animation
    (const u32*)walker_smallTileData, // start of the sprite data
    NULL, // frame trigger data blob
    &walker_smallVdpLocation, // location in vdp when loaded
};
