#include <genesis.h>
#include "explosion.h"
#include "engine\FrameTriggers.h"


const unsigned short const explosionTileData[352] = // 22 tiles 
{
// tile: 0
    0x0000, 0x6666,
    0x0006, 0x69ee,
    0x0066, 0x9eff,
    0x0669, 0xffff,
    0x669f, 0xffff,
    0x69ef, 0xffff,
    0x6eff, 0xffff,
    0x6eff, 0xffff,
// tile: 1
    0x6eff, 0xffff,
    0x6eff, 0xffff,
    0x6eff, 0xffff,
    0x69ef, 0xffff,
    0x069e, 0xffff,
    0x0069, 0xeeff,
    0x0006, 0x9eee,
    0x0000, 0x6666,
// tile: 2
    0x6666, 0x0,
    0xee96, 0x6000,
    0xffee, 0x9600,
    0xffff, 0xe960,
    0xffff, 0xfe66,
    0xffff, 0xfe96,
    0xffff, 0xffe6,
    0xffff, 0xffe6,
// tile: 3
    0xffff, 0xffe6,
    0xffff, 0xffe6,
    0xffff, 0xfe96,
    0xffff, 0xee66,
    0xffff, 0xe960,
    0xffee, 0x9600,
    0xeee9, 0x6000,
    0x6666, 0x0,
// tile: 4
    0x0000, 0x6,
    0x0000, 0x666,
    0x0000, 0x6669,
    0x0006, 0x6699,
    0x0066, 0x699e,
    0x0666, 0x99ee,
    0x0669, 0x9eee,
    0x6699, 0xeeee,
// tile: 5
    0x6699, 0xeeee,
    0x699e, 0xeeee,
    0x699e, 0xeeee,
    0x699e, 0xeeee,
    0x699e, 0xeeee,
    0x669e, 0xeeee,
    0x669e, 0xeeee,
    0x069e, 0xeeee,
// tile: 6
    0x0669, 0xeeee,
    0x0066, 0x9eee,
    0x0006, 0x69ee,
    0x0000, 0x6669,
    0x0000, 0x666,
    0x0000, 0x6,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 7
    0x6666, 0x6660,
    0x6999, 0x9666,
    0x9999, 0x9999,
    0xeeee, 0xeeee,
    0xeeee, 0xeeee,
    0xeeee, 0xeeee,
    0xeeee, 0xeeee,
    0xeeee, 0xeeee,
// tile: 8
    0xeeee, 0xeeee,
    0xeeee, 0xeeee,
    0xeeee, 0xeeee,
    0xeeee, 0xeeee,
    0xeeee, 0xeeee,
    0xeeee, 0xeeee,
    0xeeee, 0xeeee,
    0xeeee, 0xeeee,
// tile: 9
    0xeeee, 0xeeee,
    0xeeee, 0xeeee,
    0xeeee, 0xeeee,
    0x9eee, 0xee99,
    0x6999, 0x9966,
    0x6666, 0x6660,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 10
    0x0000, 0x0,
    0x6000, 0x0,
    0x6600, 0x0,
    0x9660, 0x0,
    0xe966, 0x0,
    0xee96, 0x6000,
    0xeee6, 0x6000,
    0xeee9, 0x6600,
// tile: 11
    0xeee9, 0x6600,
    0xeeee, 0x9600,
    0xeeee, 0x9600,
    0xeeee, 0x9600,
    0xeeee, 0x9600,
    0xeeee, 0x9600,
    0xeeee, 0x9600,
    0xeee9, 0x6000,
// tile: 12
    0xeee9, 0x6000,
    0xee96, 0x0,
    0xe960, 0x0,
    0x6600, 0x0,
    0x6000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 13
    0x0000, 0x0,
    0x0000, 0x666,
    0x0000, 0x6669,
    0x0006, 0x6690,
    0x0066, 0x9000,
    0x0669, 0x0,
    0x0669, 0x0,
    0x0690, 0x0,
// tile: 14
    0x6690, 0x0,
    0x6900, 0x0,
    0x6900, 0x0,
    0x6900, 0x0,
    0x6900, 0x0,
    0x6900, 0x0,
    0x6900, 0x0,
    0x6690, 0x0,
// tile: 15
    0x0690, 0x0,
    0x0669, 0x0,
    0x0669, 0x0,
    0x0066, 0x9000,
    0x0006, 0x6690,
    0x0000, 0x6660,
    0x0000, 0x666,
    0x0000, 0x0,
// tile: 16
    0x6666, 0x6666,
    0x6999, 0x9996,
    0x9000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 17
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 18
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x9900, 0x0,
    0x6666, 0x6666,
// tile: 19
    0x0000, 0x0,
    0x6660, 0x0,
    0x9666, 0x0,
    0x0066, 0x6000,
    0x0000, 0x6600,
    0x0000, 0x9660,
    0x0000, 0x660,
    0x0000, 0x6,
// tile: 20
    0x0000, 0x6,
    0x0000, 0x6,
    0x0000, 0x6,
    0x0000, 0x6,
    0x0000, 0x6,
    0x0000, 0x6,
    0x0000, 0x6,
    0x0000, 0x6,
// tile: 21
    0x0000, 0x60,
    0x0000, 0x60,
    0x0000, 0x660,
    0x0000, 0x6600,
    0x0006, 0x6000,
    0x0066, 0x0,
    0x6660, 0x0,
    0x0000, 0x0,
};

const GGSprite explosionSprite0 = 
{
    16, // x position offset
    32, // y position offset
    32, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const GGSprite explosionSprite1 = 
{
    13, // x position offset
    29, // y position offset
    27, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 4), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const GGSprite explosionSprite2 = 
{
    12, // x position offset
    28, // y position offset
    28, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 13), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const GGSprite explosionSprite3 = 
{
    24, // x position offset
    16, // y position offset
    24, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const GGSprite explosionSprite4 = 
{
    21, // x position offset
    13, // y position offset
    19, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 4), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const GGSprite explosionSprite5 = 
{
    20, // x position offset
    12, // y position offset
    20, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 13), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const GGSprite explosionSprite6 = 
{
    32, // x position offset
    32, // y position offset
    16, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const GGSprite explosionSprite7 = 
{
    29, // x position offset
    29, // y position offset
    11, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 4), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const GGSprite explosionSprite8 = 
{
    28, // x position offset
    28, // y position offset
    12, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 13), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const GGSprite* const explosionSpriteArray0[1] = 
{
    &explosionSprite0,
};

const GGSprite* const explosionSpriteArray1[1] = 
{
    &explosionSprite1,
};

const GGSprite* const explosionSpriteArray2[1] = 
{
    &explosionSprite2,
};

const GGSprite* const explosionSpriteArray3[1] = 
{
    &explosionSprite3,
};

const GGSprite* const explosionSpriteArray4[1] = 
{
    &explosionSprite4,
};

const GGSprite* const explosionSpriteArray5[1] = 
{
    &explosionSprite5,
};

const GGSprite* const explosionSpriteArray6[1] = 
{
    &explosionSprite6,
};

const GGSprite* const explosionSpriteArray7[1] = 
{
    &explosionSprite7,
};

const GGSprite* const explosionSpriteArray8[1] = 
{
    &explosionSprite8,
};

extern const GGFrame explosionFrame0;
extern const GGFrame explosionFrame1;
extern const GGFrame explosionFrame2;
extern const GGFrame explosionFrame3;
extern const GGFrame explosionFrame4;
extern const GGFrame explosionFrame5;
extern const GGFrame explosionFrame6;
extern const GGFrame explosionFrame7;
extern const GGFrame explosionFrame8;





const GGFrame explosionFrame0 = 
{
    explosionSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame1, // next frame
};


const GGFrame explosionFrame1 = 
{
    explosionSpriteArray1,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame2, // next frame
};


const GGFrame explosionFrame2 = 
{
    explosionSpriteArray2,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame3, // next frame
};


const GGFrame explosionFrame3 = 
{
    explosionSpriteArray3,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame4, // next frame
};


const GGFrame explosionFrame4 = 
{
    explosionSpriteArray4,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame5, // next frame
};


const GGFrame explosionFrame5 = 
{
    explosionSpriteArray5,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame6, // next frame
};


const GGFrame explosionFrame6 = 
{
    explosionSpriteArray6,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame7, // next frame
};


const GGFrame explosionFrame7 = 
{
    explosionSpriteArray7,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame8, // next frame
};


const GGFrame explosionFrame8 = 
{
    explosionSpriteArray8,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame0, // loop to next frame. 
};

const GGFrame* const explosionFrames[9] = 
{
    &explosionFrame0,
    &explosionFrame1,
    &explosionFrame2,
    &explosionFrame3,
    &explosionFrame4,
    &explosionFrame5,
    &explosionFrame6,
    &explosionFrame7,
    &explosionFrame8,
};



const GGAnimation explosion = 
{
    STANDARD_ANIMATION_RESOURCE_TYPE,
    explosionFrames,
    9, // number of frames
    64, // width in pixels
    64, // height in pixels
    9, // max tiles per frame
    22, // the total number of tiles in the animation
    (const u32*)explosionTileData, // start of the sprite data
    NULL, // frame trigger data blob
};
