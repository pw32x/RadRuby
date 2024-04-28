#include <genesis.h>
#include "shotgun.h"
#include "engine\FrameTriggers.h"
#include "engine\draw_utils.h"
#include "engine\animation_utils.h"


const unsigned short const shotgunTileData[96] = // 6 tiles 
{
// tile: 0
    0x0099, 0x0,
    0x0966, 0x9000,
    0x96ff, 0x6900,
    0x96ff, 0x6900,
    0x0966, 0x9000,
    0x0099, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 1
    0x0099, 0x9900,
    0x0966, 0x6690,
    0x966f, 0xf669,
    0x96ff, 0xff69,
    0x96ff, 0xff69,
    0x966f, 0xf669,
    0x0966, 0x6690,
    0x0099, 0x9900,
// tile: 2
    0x0000, 0x999,
    0x0009, 0x9666,
    0x0096, 0x6666,
    0x0966, 0x6699,
    0x0966, 0x99ff,
    0x9666, 0x9fff,
    0x9669, 0xffff,
    0x9669, 0xffff,
// tile: 3
    0x9669, 0xffff,
    0x9669, 0xffff,
    0x9666, 0x9fff,
    0x0966, 0x99ff,
    0x0966, 0x6699,
    0x0096, 0x6666,
    0x0009, 0x9666,
    0x0000, 0x999,
// tile: 4
    0x9990, 0x0,
    0x6669, 0x9000,
    0x6666, 0x6900,
    0x9966, 0x6690,
    0xff99, 0x6690,
    0xfff9, 0x6669,
    0xffff, 0x9669,
    0xffff, 0x9669,
// tile: 5
    0xffff, 0x9669,
    0xffff, 0x9669,
    0xfff9, 0x6669,
    0xff99, 0x6690,
    0x9966, 0x6690,
    0x6666, 0x6900,
    0x6669, 0x9000,
    0x9990, 0x0,
};

const Ruby_Sprite shotgunSprite0 = 
{
    -3, // x position offset
    -3, // y position offset
    3, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(1, 1), // sgdk sprite size
};

const Ruby_Sprite shotgunSprite1 = 
{
    -4, // x position offset
    -4, // y position offset
    4, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 1), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(1, 1), // sgdk sprite size
};

const Ruby_Sprite shotgunSprite2 = 
{
    -8, // x position offset
    -8, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 2), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const Ruby_Sprite* const shotgunSpriteArray0[1] = 
{
    &shotgunSprite0,
};

const Ruby_Sprite* const shotgunSpriteArray1[1] = 
{
    &shotgunSprite1,
};

const Ruby_Sprite* const shotgunSpriteArray2[1] = 
{
    &shotgunSprite2,
};

extern const Ruby_Frame shotgunFrame0;
extern const Ruby_Frame shotgunFrame1;
extern const Ruby_Frame shotgunFrame2;





const Ruby_Frame shotgunFrame0 = 
{
    shotgunSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &shotgunFrame1, // next frame
};


const Ruby_Frame shotgunFrame1 = 
{
    shotgunSpriteArray1,
    1, // number of sprites
    0, // frame trigger data offset
    7, // frame time
    &shotgunFrame2, // next frame
};


const Ruby_Frame shotgunFrame2 = 
{
    shotgunSpriteArray2,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &shotgunFrame0, // loop to next frame. 
};

const Ruby_Frame* const shotgunFrames[3] = 
{
    &shotgunFrame0,
    &shotgunFrame1,
    &shotgunFrame2,
};

const Ruby_AnimationSetup const shotgunSetup = 
{
    DrawUtils_drawMetasprite,
    AnimationUtils_updateStandardAnimation,
    &shotgunFrame0,
    0,
    2,
};

u16 shotgunVdpLocation;

const Ruby_Animation shotgun = 
{
    STANDARD_ANIMATION_RESOURCE_TYPE,
    &shotgunSetup,
    shotgunFrames,
    3, // number of frames
    16, // width in pixels
    16, // height in pixels
    4, // max tiles per frame
    6, // the total number of tiles in the animation
    (const u32*)shotgunTileData, // start of the sprite data
    NULL, // frame trigger data blob
    &shotgunVdpLocation, // location in vdp when loaded
};
