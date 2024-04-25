#include <genesis.h>
#include "enemy_bullet.h"
#include "engine\FrameTriggers.h"


const unsigned short const enemy_bulletTileData[32] = // 2 tiles 
{
// tile: 0
    0x0066, 0x6600,
    0x0699, 0x9960,
    0x6999, 0x9996,
    0x6999, 0x9996,
    0x6999, 0x9996,
    0x6999, 0x9996,
    0x0699, 0x9960,
    0x0066, 0x6600,
// tile: 1
    0x00aa, 0xaa00,
    0x0a33, 0x33a0,
    0xa333, 0x333a,
    0xa333, 0x333a,
    0xa333, 0x333a,
    0xa333, 0x333a,
    0x0a33, 0x33a0,
    0x00aa, 0xaa00,
};

const GGSprite enemy_bulletSprite0 = 
{
    -4, // x position offset
    -4, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(1, 1), // sgdk sprite size
};

const GGSprite enemy_bulletSprite1 = 
{
    -4, // x position offset
    -4, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 1), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(1, 1), // sgdk sprite size
};

const GGSprite* const enemy_bulletSpriteArray0[1] = 
{
    &enemy_bulletSprite0,
};

const GGSprite* const enemy_bulletSpriteArray1[1] = 
{
    &enemy_bulletSprite1,
};

extern const GGFrame enemy_bulletFrame0;
extern const GGFrame enemy_bulletFrame1;





const GGFrame enemy_bulletFrame0 = 
{
    enemy_bulletSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    4, // frame time
    &enemy_bulletFrame1, // next frame
};


const GGFrame enemy_bulletFrame1 = 
{
    enemy_bulletSpriteArray1,
    1, // number of sprites
    0, // frame trigger data offset
    4, // frame time
    &enemy_bulletFrame0, // loop to next frame. 
};

const GGFrame* const enemy_bulletFrames[2] = 
{
    &enemy_bulletFrame0,
    &enemy_bulletFrame1,
};



const GGAnimation enemy_bullet = 
{
    STANDARD_ANIMATION_RESOURCE_TYPE,
    enemy_bulletFrames,
    2, // number of frames
    8, // width in pixels
    16, // height in pixels
    1, // max tiles per frame
    2, // the total number of tiles in the animation
    (const u32*)enemy_bulletTileData, // start of the sprite data
    NULL, // frame trigger data blob
};
