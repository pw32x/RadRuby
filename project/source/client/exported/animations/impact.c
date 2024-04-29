#include <genesis.h>
#include "impact.h"
#include "engine\FrameTriggers.h"
#include "engine\animation_draw.h"
#include "engine\animation_utils.h"


const unsigned short const impactTileData[192] = // 12 tiles 
{
// tile: 0
    0xe000, 0x0,
    0x0fe0, 0x0,
    0x0eff, 0xe0ef,
    0x00ff, 0xfeff,
    0x00ef, 0xffff,
    0x000e, 0xfffe,
    0x00ef, 0xffff,
    0x00ff, 0xfeff,
// tile: 1
    0x0eff, 0xe0ef,
    0x0fe0, 0x0,
    0xe000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 2
    0x00e0, 0x0,
    0xef00, 0x0,
    0xfe00, 0x0,
    0xf000, 0x0,
    0xe000, 0x0,
    0x0000, 0x0,
    0xe000, 0x0,
    0xf000, 0x0,
// tile: 3
    0xfe00, 0x0,
    0xef00, 0x0,
    0x00e0, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 4
    0xe000, 0xe,
    0x0ee0, 0xf,
    0x0efe, 0xef,
    0x00ef, 0xffff,
    0x000f, 0xfff0,
    0x000f, 0xff00,
    0x00ef, 0xf000,
    0xefff, 0x0,
// tile: 5
    0x00ef, 0xf000,
    0x000f, 0xff00,
    0x000f, 0xfff0,
    0x00ef, 0xffff,
    0x0efe, 0xef,
    0x0ee0, 0xf,
    0xe000, 0xe,
    0x0000, 0x0,
// tile: 6
    0x0000, 0xe0,
    0x0000, 0xee00,
    0xe00e, 0xfe00,
    0xffff, 0xe000,
    0xffff, 0x0,
    0x0fff, 0x0,
    0x00ff, 0xe000,
    0x000f, 0xffe0,
// tile: 7
    0x00ff, 0xe000,
    0x0fff, 0x0,
    0xffff, 0x0,
    0xffff, 0xe000,
    0xe00e, 0xfe00,
    0x0000, 0xee00,
    0x0000, 0xe0,
    0x0000, 0x0,
// tile: 8
    0x0000, 0xfff,
    0x000f, 0xf000,
    0x00f0, 0x0,
    0x0f00, 0x0,
    0x0f00, 0x0,
    0xf000, 0x0,
    0xf000, 0x0,
    0xf000, 0x0,
// tile: 9
    0xf000, 0x0,
    0xf000, 0x0,
    0x0f00, 0x0,
    0x0f00, 0x0,
    0x00f0, 0x0,
    0x000f, 0xf000,
    0x0000, 0xfff,
    0x0000, 0x0,
// tile: 10
    0xff00, 0x0,
    0x00ff, 0x0,
    0x0000, 0xf000,
    0x0000, 0xf000,
    0x0000, 0xf00,
    0x0000, 0xf0,
    0x0000, 0xf0,
    0x0000, 0xf0,
// tile: 11
    0x0000, 0xf0,
    0x0000, 0xf0,
    0x0000, 0xf00,
    0x0000, 0xf00,
    0x0000, 0xf000,
    0x00ff, 0x0,
    0xff00, 0x0,
    0x0000, 0x0,
};

const Ruby_Sprite impactSprite0 = 
{
    -6, // x position offset
    -6, // y position offset
    -2, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const Ruby_Sprite impactSprite1 = 
{
    -8, // x position offset
    -8, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 4), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const Ruby_Sprite impactSprite2 = 
{
    -8, // x position offset
    -8, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 8), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const Ruby_Sprite* const impactSpriteArray0[1] = 
{
    &impactSprite0,
};

const Ruby_Sprite* const impactSpriteArray1[1] = 
{
    &impactSprite1,
};

const Ruby_Sprite* const impactSpriteArray2[1] = 
{
    &impactSprite2,
};

extern const Ruby_Frame impactFrame0;
extern const Ruby_Frame impactFrame1;
extern const Ruby_Frame impactFrame2;





const Ruby_Frame impactFrame0 = 
{
    impactSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    3, // frame time
    &impactFrame1, // next frame
};


const Ruby_Frame impactFrame1 = 
{
    impactSpriteArray1,
    1, // number of sprites
    0, // frame trigger data offset
    3, // frame time
    &impactFrame2, // next frame
};


const Ruby_Frame impactFrame2 = 
{
    impactSpriteArray2,
    1, // number of sprites
    0, // frame trigger data offset
    3, // frame time
    &impactFrame0, // loop to next frame. 
};

const Ruby_Frame* const impactFrames[3] = 
{
    &impactFrame0,
    &impactFrame1,
    &impactFrame2,
};

const Ruby_AnimationSetup const impactSetup = 
{
    Animation_DrawObject,
    AnimationUtils_updateStandardAnimation,
    &impactFrame0,
    0,
    3,
};

u16 impactVdpLocation;

const Ruby_Animation impact = 
{
    STANDARD_ANIMATION_RESOURCE_TYPE,
    &impactSetup,
    impactFrames,
    3, // number of frames
    16, // width in pixels
    16, // height in pixels
    4, // max tiles per frame
    12, // the total number of tiles in the animation
    (const u32*)impactTileData, // start of the sprite data
    NULL, // frame trigger data blob
    &impactVdpLocation, // location in vdp when loaded
};
