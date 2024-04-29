#include <genesis.h>
#include "walker.h"
#include "engine\FrameTriggers.h"
#include "engine\animation_draw.h"
#include "engine\animation_utils.h"


const unsigned short const walkerTileData[128] = // 8 tiles 
{
// tile: 0
    0x0000, 0x111,
    0x0001, 0x19ee,
    0x001c, 0xc19e,
    0x01cc, 0x6666,
    0x0119, 0x6661,
    0x1c61, 0x9661,
    0x1c61, 0x9666,
    0x1661, 0x9666,
// tile: 1
    0x1119, 0x6661,
    0x1c66, 0x6661,
    0x1116, 0x6666,
    0x19f1, 0x6666,
    0x1af8, 0x1999,
    0x01aa, 0xa111,
    0x0011, 0x1000,
    0x0000, 0x0,
// tile: 2
    0x1110, 0x1110,
    0x1691, 0x9ee1,
    0xe119, 0xee10,
    0x1161, 0x1100,
    0xff1f, 0xf100,
    0xf21f, 0x2110,
    0x1161, 0x1910,
    0x6666, 0x6910,
// tile: 3
    0x1111, 0x1910,
    0x6666, 0x1910,
    0x6996, 0x61a1,
    0x6ee6, 0x18a1,
    0x9991, 0xffa1,
    0x1111, 0x9a10,
    0x0000, 0x1100,
    0x0000, 0x0,
// tile: 4
    0x0000, 0x111,
    0x0001, 0x19ee,
    0x001c, 0xc19e,
    0x01cc, 0x6666,
    0x0119, 0x6661,
    0x1c61, 0x9661,
    0x1c61, 0x9666,
    0x1661, 0x9666,
// tile: 5
    0x1119, 0x6661,
    0x1c66, 0x6661,
    0x01c6, 0x6666,
    0x01c6, 0x6611,
    0x001c, 0x91ff,
    0x0001, 0x119f,
    0x0000, 0x1aa,
    0x0000, 0x111,
// tile: 6
    0x1110, 0x1110,
    0x1691, 0x9ee1,
    0xe119, 0xee10,
    0x1161, 0x1100,
    0xff1f, 0xf100,
    0xf21f, 0x2110,
    0x1161, 0x1910,
    0x6666, 0x6910,
// tile: 7
    0x1111, 0x1910,
    0x6666, 0x1910,
    0x6996, 0x9100,
    0x1ee6, 0x9100,
    0x8119, 0x1000,
    0xf9a1, 0x0,
    0xaaa1, 0x0,
    0x1111, 0x0,
};

const Ruby_Sprite walkerSprite0 = 
{
    -8, // x position offset
    -7, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const Ruby_Sprite walkerSprite1 = 
{
    -8, // x position offset
    -8, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 4), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const Ruby_Sprite* const walkerSpriteArray0[1] = 
{
    &walkerSprite0,
};

const Ruby_Sprite* const walkerSpriteArray1[1] = 
{
    &walkerSprite1,
};

extern const Ruby_Frame walkerFrame0;
extern const Ruby_Frame walkerFrame1;





const Ruby_Frame walkerFrame0 = 
{
    walkerSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    12, // frame time
    &walkerFrame1, // next frame
};


const Ruby_Frame walkerFrame1 = 
{
    walkerSpriteArray1,
    1, // number of sprites
    0, // frame trigger data offset
    12, // frame time
    &walkerFrame0, // next frame
};

const Ruby_Frame* const walkerFrames[2] = 
{
    &walkerFrame0,
    &walkerFrame1,
};

const Ruby_AnimationSetup const walkerSetup = 
{
    Animation_DrawObject,
    AnimationUtils_updateStandardAnimation,
    &walkerFrame0,
    0,
    12,
};

u16 walkerVdpLocation;

const Ruby_Animation walker = 
{
    STANDARD_ANIMATION_RESOURCE_TYPE,
    &walkerSetup,
    walkerFrames,
    2, // number of frames
    16, // width in pixels
    16, // height in pixels
    4, // max tiles per frame
    8, // the total number of tiles in the animation
    (const u32*)walkerTileData, // start of the sprite data
    NULL, // frame trigger data blob
    &walkerVdpLocation, // location in vdp when loaded
};
