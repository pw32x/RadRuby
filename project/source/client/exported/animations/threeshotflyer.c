#include <genesis.h>
#include "threeshotflyer.h"
#include "engine\FrameTriggers.h"
#include "engine\animation_draw.h"
#include "engine\animation_utils.h"


const unsigned short const threeshotflyerTileData[288] = // 18 tiles 
{
// tile: 0
    0x0000, 0xeee,
    0x000e, 0xefff,
    0xeeef, 0xff99,
    0x0999, 0x9999,
    0x0009, 0x99ee,
    0x0001, 0x1111,
    0x0015, 0x55bb,
    0x001b, 0xbbbb,
// tile: 1
    0x0155, 0x555b,
    0x01bb, 0x51f5,
    0x0155, 0x51ff,
    0x01bb, 0x51ff,
    0x0155, 0x551f,
    0x0019, 0x45b1,
    0x0159, 0x9455,
    0x1995, 0x9945,
// tile: 2
    0x1499, 0x591b,
    0x0149, 0x1101,
    0x0011, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 3
    0xee11, 0x1eee,
    0xf15b, 0xb199,
    0x9911, 0x199f,
    0xffff, 0xffff,
    0xeeee, 0xeeee,
    0x5555, 0x5551,
    0x5966, 0x665b,
    0xb596, 0x65bb,
// tile: 4
    0xbb59, 0x5bbb,
    0x5555, 0x5555,
    0x22f1, 0xf22f,
    0x11f1, 0xf11f,
    0xff1b, 0x1fff,
    0x11b5, 0xb111,
    0xb555, 0x55b5,
    0x5544, 0x4555,
// tile: 5
    0x5455, 0x545b,
    0x5999, 0x9951,
    0x1955, 0x5910,
    0x0199, 0x9100,
    0x0144, 0x4100,
    0x0011, 0x1000,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 6
    0xe900, 0x0,
    0x9999, 0x0,
    0xffff, 0xfe00,
    0xffff, 0xe000,
    0xeeee, 0x0,
    0x1110, 0x0,
    0xb555, 0x1000,
    0xbbbb, 0x1000,
// tile: 7
    0x5555, 0x5100,
    0xf15b, 0xb100,
    0xf155, 0x5100,
    0xf15b, 0xb100,
    0x1555, 0x5100,
    0xb549, 0x1000,
    0x5499, 0x5100,
    0x4995, 0x9910,
// tile: 8
    0x1959, 0x9410,
    0x0119, 0x4100,
    0x0001, 0x1000,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 9
    0x0000, 0xeee,
    0x00ee, 0xefff,
    0xefff, 0xffff,
    0x0eee, 0x9999,
    0x0000, 0x999,
    0x0000, 0x1111,
    0x0001, 0x555b,
    0x0001, 0xbbbb,
// tile: 10
    0x0015, 0x5555,
    0x001b, 0xb51f,
    0x0015, 0x551f,
    0x001b, 0xb51f,
    0x0015, 0x5551,
    0x0001, 0x945b,
    0x0015, 0x9945,
    0x0199, 0x5994,
// tile: 11
    0x0149, 0x9591,
    0x0014, 0x9110,
    0x0001, 0x1000,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 12
    0xeee1, 0x11ee,
    0xff1b, 0xb519,
    0x9991, 0x1199,
    0x99ff, 0xffff,
    0x9eee, 0xeeee,
    0x1555, 0x5555,
    0xb596, 0x6665,
    0xbb59, 0x665b,
// tile: 13
    0xbbb5, 0x95bb,
    0x5555, 0x5555,
    0xf22f, 0x1f22,
    0xf11f, 0x1f11,
    0xfff1, 0xb1ff,
    0x111b, 0x5b11,
    0x5b55, 0x555b,
    0x5554, 0x4455,
// tile: 14
    0xb545, 0x5545,
    0x1599, 0x9995,
    0x0195, 0x5591,
    0x0019, 0x9910,
    0x0014, 0x4410,
    0x0001, 0x1100,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 15
    0xe999, 0x0,
    0x9999, 0x9e00,
    0x9fff, 0xfffe,
    0xffff, 0xfee0,
    0xeeee, 0xe000,
    0x1111, 0x1000,
    0xbb55, 0x5100,
    0xbbbb, 0xb100,
// tile: 16
    0xb555, 0x5510,
    0x5f15, 0xbb10,
    0xff15, 0x5510,
    0xff15, 0xbb10,
    0xf155, 0x5510,
    0x1b54, 0x9100,
    0x5549, 0x9510,
    0x5499, 0x5991,
// tile: 17
    0xb195, 0x9941,
    0x1011, 0x9410,
    0x0000, 0x1100,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
};

const Ruby_Sprite threeshotflyerSprite0 = 
{
    -11, // x position offset
    -12, // y position offset
    -1, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const Ruby_Sprite threeshotflyerSprite1 = 
{
    -12, // x position offset
    -12, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 9), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 3), // sgdk sprite size
};

const Ruby_Sprite* const threeshotflyerSpriteArray0[1] = 
{
    &threeshotflyerSprite0,
};

const Ruby_Sprite* const threeshotflyerSpriteArray1[1] = 
{
    &threeshotflyerSprite1,
};

extern const Ruby_Frame threeshotflyerFrame0;
extern const Ruby_Frame threeshotflyerFrame1;





const Ruby_Frame threeshotflyerFrame0 = 
{
    threeshotflyerSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    6, // frame time
    &threeshotflyerFrame1, // next frame
};


const Ruby_Frame threeshotflyerFrame1 = 
{
    threeshotflyerSpriteArray1,
    1, // number of sprites
    0, // frame trigger data offset
    6, // frame time
    &threeshotflyerFrame0, // next frame
};

const Ruby_Frame* const threeshotflyerFrames[2] = 
{
    &threeshotflyerFrame0,
    &threeshotflyerFrame1,
};

const Ruby_AnimationSetup const threeshotflyerSetup = 
{
    Animation_DrawObject,
    AnimationUtils_updateStandardAnimation,
    &threeshotflyerFrame0,
    0,
    6,
};

u16 threeshotflyerVdpLocation;

const Ruby_Animation threeshotflyer = 
{
    STANDARD_ANIMATION_RESOURCE_TYPE,
    &threeshotflyerSetup,
    threeshotflyerFrames,
    2, // number of frames
    24, // width in pixels
    32, // height in pixels
    9, // max tiles per frame
    18, // the total number of tiles in the animation
    (const u32*)threeshotflyerTileData, // start of the sprite data
    NULL, // frame trigger data blob
    &threeshotflyerVdpLocation, // location in vdp when loaded
};
