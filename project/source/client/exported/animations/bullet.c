#include <genesis.h>
#include "bullet.h"
#include "engine\FrameTriggers.h"
#include "engine\draw_utils.h"
#include "engine\animation_utils.h"


const unsigned short const bulletTileData[16] = // 1 tiles 
{
// tile: 0
    0x0222, 0x2000,
    0x2fff, 0xf200,
    0x2fff, 0xf200,
    0x2fff, 0xf200,
    0x2fff, 0xf200,
    0x0222, 0x2000,
    0x0000, 0x0,
    0x0000, 0x0,
};

const Ruby_Sprite bulletSprite0 = 
{
    -3, // x position offset
    -3, // y position offset
    -1, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(1, 1), // sgdk sprite size
};

const Ruby_Sprite* const bulletSpriteArray0[1] = 
{
    &bulletSprite0,
};

extern const Ruby_Frame bulletFrame0;





const Ruby_Frame bulletFrame0 = 
{
    bulletSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    5, // frame time
    &bulletFrame0, // loop to next frame. 
};

const Ruby_Frame* const bulletFrames[1] = 
{
    &bulletFrame0,
};

const Ruby_AnimationSetup const bulletSetup = 
{
    DrawUtils_drawMetasprite,
    AnimationUtils_updateStandardAnimation,
    &bulletFrame0,
    0,
    5,
};

u16 bulletVdpLocation;

const Ruby_Animation bullet = 
{
    STANDARD_ANIMATION_RESOURCE_TYPE,
    &bulletSetup,
    bulletFrames,
    1, // number of frames
    8, // width in pixels
    16, // height in pixels
    1, // max tiles per frame
    1, // the total number of tiles in the animation
    (const u32*)bulletTileData, // start of the sprite data
    NULL, // frame trigger data blob
    &bulletVdpLocation, // location in vdp when loaded
};
