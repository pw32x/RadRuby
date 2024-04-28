#include <genesis.h>
#include "explosion.h"
#include "engine\FrameTriggers.h"
#include "engine\draw_utils.h"
#include "engine\animation_utils.h"


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

const Ruby_Sprite explosionSprite0 = 
{
    -16, // x position offset
    0, // y position offset
    32, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const Ruby_Sprite explosionSprite1 = 
{
    -19, // x position offset
    -3, // y position offset
    27, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 4), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const Ruby_Sprite explosionSprite2 = 
{
    -20, // x position offset
    -4, // y position offset
    28, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 13), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const Ruby_Sprite explosionSprite3 = 
{
    -8, // x position offset
    -16, // y position offset
    24, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const Ruby_Sprite explosionSprite4 = 
{
    -11, // x position offset
    -19, // y position offset
    19, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 4), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const Ruby_Sprite explosionSprite5 = 
{
    -12, // x position offset
    -20, // y position offset
    20, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 13), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const Ruby_Sprite explosionSprite6 = 
{
    0, // x position offset
    0, // y position offset
    16, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const Ruby_Sprite explosionSprite7 = 
{
    -3, // x position offset
    -3, // y position offset
    11, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 4), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const Ruby_Sprite explosionSprite8 = 
{
    -4, // x position offset
    -4, // y position offset
    12, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 13), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const Ruby_Sprite* const explosionSpriteArray0[1] = 
{
    &explosionSprite0,
};

const Ruby_Sprite* const explosionSpriteArray1[1] = 
{
    &explosionSprite1,
};

const Ruby_Sprite* const explosionSpriteArray2[1] = 
{
    &explosionSprite2,
};

const Ruby_Sprite* const explosionSpriteArray3[1] = 
{
    &explosionSprite3,
};

const Ruby_Sprite* const explosionSpriteArray4[1] = 
{
    &explosionSprite4,
};

const Ruby_Sprite* const explosionSpriteArray5[1] = 
{
    &explosionSprite5,
};

const Ruby_Sprite* const explosionSpriteArray6[1] = 
{
    &explosionSprite6,
};

const Ruby_Sprite* const explosionSpriteArray7[1] = 
{
    &explosionSprite7,
};

const Ruby_Sprite* const explosionSpriteArray8[1] = 
{
    &explosionSprite8,
};

extern const Ruby_Frame explosionFrame0;
extern const Ruby_Frame explosionFrame1;
extern const Ruby_Frame explosionFrame2;
extern const Ruby_Frame explosionFrame3;
extern const Ruby_Frame explosionFrame4;
extern const Ruby_Frame explosionFrame5;
extern const Ruby_Frame explosionFrame6;
extern const Ruby_Frame explosionFrame7;
extern const Ruby_Frame explosionFrame8;





const Ruby_Frame explosionFrame0 = 
{
    explosionSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame1, // next frame
};


const Ruby_Frame explosionFrame1 = 
{
    explosionSpriteArray1,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame2, // next frame
};


const Ruby_Frame explosionFrame2 = 
{
    explosionSpriteArray2,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame3, // next frame
};


const Ruby_Frame explosionFrame3 = 
{
    explosionSpriteArray3,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame4, // next frame
};


const Ruby_Frame explosionFrame4 = 
{
    explosionSpriteArray4,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame5, // next frame
};


const Ruby_Frame explosionFrame5 = 
{
    explosionSpriteArray5,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame6, // next frame
};


const Ruby_Frame explosionFrame6 = 
{
    explosionSpriteArray6,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame7, // next frame
};


const Ruby_Frame explosionFrame7 = 
{
    explosionSpriteArray7,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame8, // next frame
};


const Ruby_Frame explosionFrame8 = 
{
    explosionSpriteArray8,
    1, // number of sprites
    0, // frame trigger data offset
    2, // frame time
    &explosionFrame0, // loop to next frame. 
};

const Ruby_Frame* const explosionFrames[9] = 
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

const Ruby_AnimationSetup const explosionSetup = 
{
    DrawUtils_drawMetasprite,
    AnimationUtils_updateStandardAnimation,
    &explosionFrame0,
    0,
    2,
};

u16 explosionVdpLocation;

const Ruby_Animation explosion = 
{
    STANDARD_ANIMATION_RESOURCE_TYPE,
    &explosionSetup,
    explosionFrames,
    9, // number of frames
    64, // width in pixels
    64, // height in pixels
    9, // max tiles per frame
    22, // the total number of tiles in the animation
    (const u32*)explosionTileData, // start of the sprite data
    NULL, // frame trigger data blob
    &explosionVdpLocation, // location in vdp when loaded
};
