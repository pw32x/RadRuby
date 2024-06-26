#include <genesis.h>
#include "walker_big.h"
#include "engine\FrameTriggers.h"
#include "engine\animation_draw.h"
#include "engine\animation_utils.h"


const unsigned short const walker_bigTileData[1024] = // 64 tiles 
{
// tile: 0
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x11,
    0x0000, 0x1cc,
    0x0000, 0x1cc6,
    0x0001, 0xcc6c,
    0x001c, 0xc6c6,
    0x001c, 0x6c6c,
// tile: 1
    0x01c6, 0xc666,
    0x01c1, 0x1116,
    0x1c1c, 0x6191,
    0x11c6, 0x6619,
    0x1161, 0x6619,
    0x1161, 0x1619,
    0x1161, 0x1619,
    0x1166, 0x6919,
// tile: 2
    0x1c16, 0x9191,
    0x1cc1, 0x1116,
    0x01c6, 0xc666,
    0x01cc, 0x6c66,
    0x001c, 0xc666,
    0x001c, 0x6c6c,
    0x0001, 0xc6c6,
    0x0000, 0x1c6c,
// tile: 3
    0x0000, 0x11c,
    0x0000, 0x11,
    0x0000, 0x1f,
    0x0000, 0x1f,
    0x0000, 0x1a,
    0x0000, 0x1a,
    0x0000, 0x1a,
    0x0000, 0x1,
// tile: 4
    0x0001, 0x1111,
    0x111c, 0xcccc,
    0x1c11, 0x1111,
    0xc199, 0x9999,
    0x6619, 0xeeee,
    0x6661, 0x9eee,
    0x6666, 0x1111,
    0x6666, 0x6666,
// tile: 5
    0x6666, 0x6111,
    0x6666, 0x1fff,
    0x6666, 0x1f22,
    0x1666, 0x1f28,
    0x1666, 0x1f22,
    0x1666, 0x1fff,
    0x1666, 0x6111,
    0x1666, 0x6666,
// tile: 6
    0x6666, 0x6666,
    0x6666, 0x6111,
    0x6666, 0x1166,
    0x6666, 0x1666,
    0x6666, 0x6661,
    0x6666, 0x6666,
    0x6666, 0x6666,
    0x6661, 0x1666,
// tile: 7
    0xc61f, 0xf116,
    0xcc1f, 0xf881,
    0x11ff, 0x8899,
    0xf99f, 0xf998,
    0xf989, 0xffff,
    0xaf99, 0xffff,
    0xaaaa, 0xaaaa,
    0x1111, 0x1111,
// tile: 8
    0x1110, 0x0,
    0xccc1, 0x1100,
    0x1666, 0x9611,
    0x9166, 0x6199,
    0xee16, 0x199e,
    0xee16, 0x19ee,
    0x1166, 0x6111,
    0x6666, 0x6666,
// tile: 9
    0x1666, 0x1111,
    0xf161, 0xffff,
    0x2161, 0xf222,
    0x2161, 0xf282,
    0x2161, 0xf222,
    0xf161, 0xffff,
    0x1666, 0x1111,
    0x6666, 0x6666,
// tile: 10
    0x6666, 0x6666,
    0x1111, 0x1111,
    0x6666, 0x6661,
    0x1111, 0x1666,
    0x1999, 0x1166,
    0x1eee, 0x1666,
    0x1eee, 0x1666,
    0x61e1, 0x6669,
// tile: 11
    0x6616, 0x6699,
    0x1119, 0x9911,
    0x88f1, 0x1171,
    0x8ffa, 0x1777,
    0xffaa, 0xa177,
    0xffaa, 0xa177,
    0xaaaa, 0xa177,
    0x1111, 0x1111,
// tile: 12
    0x0000, 0x0,
    0x0000, 0x0,
    0x1111, 0x1000,
    0x9999, 0x9100,
    0xeeee, 0x1000,
    0xeee1, 0x0,
    0x1111, 0x0,
    0x6691, 0x0,
// tile: 13
    0x6699, 0x1000,
    0x1669, 0x1000,
    0x1669, 0x9100,
    0x1666, 0x9100,
    0x1669, 0x9100,
    0x1666, 0x9100,
    0x6669, 0x9100,
    0x6666, 0x9100,
// tile: 14
    0x6669, 0x9100,
    0x6666, 0x9100,
    0x1669, 0x1000,
    0x1669, 0x1000,
    0x6691, 0x0,
    0x6691, 0x0,
    0x6910, 0x0,
    0x9100, 0x0,
// tile: 15
    0x1000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x1000, 0x0,
    0x7100, 0x0,
    0x7100, 0x0,
    0x7100, 0x0,
    0x1000, 0x0,
// tile: 16
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x11,
    0x0000, 0x1cc,
    0x0000, 0x1cc6,
    0x0001, 0xcc6c,
    0x001c, 0xc6c6,
    0x001c, 0x6c6c,
// tile: 17
    0x01c6, 0xc666,
    0x01c1, 0x1116,
    0x1c1c, 0x6191,
    0x11c6, 0x6619,
    0x1161, 0x6619,
    0x1161, 0x1619,
    0x1161, 0x1619,
    0x1166, 0x6919,
// tile: 18
    0x1c16, 0x9191,
    0x1cc1, 0x1116,
    0x01c1, 0x1166,
    0x011f, 0x1c66,
    0x11aa, 0xf161,
    0x1aaf, 0x991f,
    0x1aaf, 0x89ff,
    0x01a9, 0x99f8,
// tile: 19
    0x01aa, 0x9ff9,
    0x001a, 0xaff9,
    0x0001, 0xaaff,
    0x0000, 0x1aff,
    0x0000, 0x1af,
    0x0000, 0x11,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 20
    0x0001, 0x1111,
    0x111c, 0xcccc,
    0x1c11, 0x1111,
    0xc199, 0x9999,
    0x6619, 0xeeee,
    0x6661, 0x9eee,
    0x6666, 0x1111,
    0x6666, 0x6666,
// tile: 21
    0x6666, 0x6111,
    0x6666, 0x1fff,
    0x6666, 0x1f22,
    0x1666, 0x1f28,
    0x1666, 0x1f22,
    0x1666, 0x1fff,
    0x1666, 0x6111,
    0x1666, 0x6666,
// tile: 22
    0x6666, 0x6666,
    0x6666, 0x6111,
    0x6666, 0x1166,
    0x6666, 0x1666,
    0x1666, 0x6661,
    0xf166, 0x6666,
    0x1666, 0x6666,
    0x1116, 0x6666,
// tile: 23
    0x88f1, 0x6666,
    0x8ffa, 0x1969,
    0xffaa, 0xa199,
    0xffaa, 0xa111,
    0xaaaa, 0xa100,
    0x1111, 0x1100,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 24
    0x1110, 0x0,
    0xccc1, 0x1100,
    0x1666, 0x9611,
    0x9166, 0x6199,
    0xee16, 0x199e,
    0xee16, 0x19ee,
    0x1166, 0x6111,
    0x6666, 0x6666,
// tile: 25
    0x1666, 0x1111,
    0xf161, 0xffff,
    0x2161, 0xf222,
    0x2161, 0xf282,
    0x2161, 0xf222,
    0xf161, 0xffff,
    0x1666, 0x1111,
    0x6666, 0x6666,
// tile: 26
    0x6666, 0x6666,
    0x1111, 0x1111,
    0x6666, 0x6661,
    0x1111, 0x1666,
    0x1999, 0x1166,
    0x1eee, 0x1666,
    0x1eee, 0x1666,
    0x61e1, 0x6669,
// tile: 27
    0x6616, 0x6699,
    0x6969, 0x1911,
    0x9991, 0x11a6,
    0x1110, 0xa7a,
    0x0000, 0x177,
    0x0000, 0x17,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 28
    0x0000, 0x0,
    0x0000, 0x0,
    0x1111, 0x1000,
    0x9999, 0x9100,
    0xeeee, 0x1000,
    0xeee1, 0x0,
    0x1111, 0x0,
    0x6691, 0x0,
// tile: 29
    0x6699, 0x1000,
    0x1669, 0x1000,
    0x1669, 0x9100,
    0x1666, 0x9100,
    0x1669, 0x9100,
    0x1666, 0x9100,
    0x6669, 0x9100,
    0x6666, 0x9100,
// tile: 30
    0x6669, 0x9100,
    0x6666, 0x9111,
    0x1669, 0x1771,
    0x1669, 0x1771,
    0x6691, 0x7771,
    0x6691, 0xaa71,
    0x6912, 0xaa71,
    0x9166, 0xaaa1,
// tile: 31
    0x1aaa, 0xaa71,
    0x66aa, 0x7710,
    0x2667, 0x7100,
    0xa677, 0x1000,
    0x7771, 0x0,
    0x7110, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 32
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x11,
    0x0000, 0x1cc,
    0x0000, 0x1cc6,
    0x0001, 0xcc6c,
    0x001c, 0xc6c6,
    0x001c, 0x6c6c,
// tile: 33
    0x01c6, 0xc666,
    0x01c1, 0x1116,
    0x1c1c, 0x6191,
    0x11c6, 0x6619,
    0x1161, 0x6619,
    0x1161, 0x1619,
    0x1161, 0x1619,
    0x1166, 0x6919,
// tile: 34
    0x1c16, 0x9191,
    0x1cc1, 0x1116,
    0x01c6, 0xc666,
    0x01cc, 0x6c66,
    0x111c, 0xc666,
    0x171c, 0x6c6c,
    0x1771, 0xc6c6,
    0x0176, 0x1c6c,
// tile: 35
    0x0177, 0x61cc,
    0x0017, 0x7a11,
    0x0001, 0x77aa,
    0x0000, 0x17aa,
    0x0000, 0x17a,
    0x0000, 0x11,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 36
    0x0001, 0x1111,
    0x111c, 0xcccc,
    0x1c11, 0x1111,
    0xc199, 0x9999,
    0x6619, 0xeeee,
    0x6661, 0x9eee,
    0x6666, 0x1111,
    0x6666, 0x6666,
// tile: 37
    0x6666, 0x6111,
    0x6666, 0x1fff,
    0x6666, 0x1f22,
    0x1666, 0x1f28,
    0x1666, 0x1f22,
    0x1666, 0x1fff,
    0x1666, 0x6111,
    0x1666, 0x6666,
// tile: 38
    0x6666, 0x6666,
    0x6666, 0x6111,
    0x6666, 0x1166,
    0x6666, 0x1666,
    0x6666, 0x6661,
    0x6666, 0x6666,
    0x6666, 0x6666,
    0x6666, 0x6666,
// tile: 39
    0xc666, 0x6666,
    0xccc9, 0x6969,
    0x1119, 0x9999,
    0xaa71, 0x1111,
    0x7777, 0x7100,
    0x1111, 0x1100,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 40
    0x1110, 0x0,
    0xccc1, 0x1100,
    0x1666, 0x9611,
    0x9166, 0x6199,
    0xee16, 0x199e,
    0xee16, 0x19ee,
    0x1166, 0x6111,
    0x6666, 0x6666,
// tile: 41
    0x1666, 0x1111,
    0xf161, 0xffff,
    0x2161, 0xf222,
    0x2161, 0xf282,
    0x2161, 0xf222,
    0xf161, 0xffff,
    0x1666, 0x1111,
    0x6666, 0x6666,
// tile: 42
    0x6666, 0x6666,
    0x1111, 0x1111,
    0x6666, 0x6661,
    0x1111, 0x1666,
    0x1999, 0x1166,
    0x1eee, 0x1661,
    0x1eee, 0x161f,
    0x61e1, 0x661f,
// tile: 43
    0x6616, 0x6691,
    0x6969, 0x1919,
    0x9991, 0x11f9,
    0x1110, 0xfaf,
    0x0000, 0x1aa,
    0x0000, 0x1a,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 44
    0x0000, 0x0,
    0x0000, 0x0,
    0x1111, 0x1000,
    0x9999, 0x9100,
    0xeeee, 0x1000,
    0xeee1, 0x0,
    0x1111, 0x0,
    0x6691, 0x0,
// tile: 45
    0x6699, 0x1000,
    0x1669, 0x1000,
    0x1669, 0x9100,
    0x1666, 0x9100,
    0x1669, 0x9100,
    0x1666, 0x9100,
    0x6669, 0x9100,
    0x6666, 0x9100,
// tile: 46
    0x6669, 0x9100,
    0x6666, 0x1111,
    0x1661, 0xaaa1,
    0x161a, 0xaaa1,
    0x61ff, 0xaaa1,
    0x618f, 0xffa1,
    0x1188, 0xffa1,
    0xf899, 0xfff1,
// tile: 47
    0xffff, 0xffa1,
    0x99ff, 0xaa10,
    0x899a, 0xa100,
    0xf9aa, 0x1000,
    0xaaa1, 0x0,
    0xa110, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 48
    0x0000, 0x0,
    0x0000, 0x0,
    0x0111, 0x1111,
    0x1999, 0x9999,
    0x01ee, 0xeee9,
    0x001e, 0xeeee,
    0x0011, 0x1111,
    0x0019, 0x6666,
// tile: 49
    0x0199, 0x6611,
    0x0196, 0x61ff,
    0x1996, 0x6122,
    0x1966, 0x6128,
    0x1996, 0x6122,
    0x1966, 0x61ff,
    0x1996, 0x6611,
    0x1966, 0x6666,
// tile: 50
    0x1996, 0x6666,
    0x1966, 0x6611,
    0x0196, 0x6116,
    0x0196, 0x6166,
    0x0019, 0x6666,
    0x0019, 0x6666,
    0x0001, 0x9666,
    0x0000, 0x1996,
// tile: 51
    0x0000, 0x199,
    0x0000, 0x11,
    0x0000, 0x17,
    0x0000, 0x177,
    0x0000, 0x1777,
    0x0000, 0x1777,
    0x0000, 0x1777,
    0x0000, 0x111,
// tile: 52
    0x0001, 0x1111,
    0x111c, 0xcccc,
    0x6966, 0x6111,
    0x1666, 0x1999,
    0x9161, 0xeeee,
    0x9161, 0xeeee,
    0x1666, 0x1111,
    0x6666, 0x6666,
// tile: 53
    0x1166, 0x6111,
    0xff16, 0x1fff,
    0x2f16, 0x1222,
    0x2f16, 0x1282,
    0x2f16, 0x1222,
    0xff16, 0x1fff,
    0x1166, 0x6111,
    0x6666, 0x6666,
// tile: 54
    0x6666, 0x6666,
    0x1111, 0x1111,
    0x6666, 0x6666,
    0x6111, 0x1166,
    0x1199, 0x9116,
    0x61ee, 0xe166,
    0x61ee, 0xe166,
    0x661e, 0x1666,
// tile: 55
    0x6661, 0x6661,
    0x9991, 0x1118,
    0x111f, 0x8899,
    0x71af, 0xf889,
    0x1aaa, 0xffff,
    0x1aaa, 0xffff,
    0x1aaa, 0xaaaa,
    0x1111, 0x1111,
// tile: 56
    0x1110, 0x0,
    0xccc1, 0x1100,
    0x1111, 0xc111,
    0x9999, 0x1ccc,
    0xee91, 0x666c,
    0xe916, 0x66c6,
    0x1166, 0x666c,
    0x6666, 0x66c6,
// tile: 57
    0x1666, 0x6666,
    0xf166, 0x6661,
    0xf166, 0x6619,
    0xf166, 0x6191,
    0xf166, 0x6191,
    0xf166, 0x6191,
    0x1666, 0x6191,
    0x6666, 0x6191,
// tile: 58
    0x6666, 0x6619,
    0x1666, 0x6661,
    0x1166, 0x6666,
    0x6166, 0x6666,
    0x6666, 0x6666,
    0x6666, 0x66c6,
    0x6666, 0x666c,
    0x6116, 0x66c6,
// tile: 59
    0x1ff1, 0x6cc1,
    0x8ff1, 0xcc11,
    0x88ff, 0x11f1,
    0x9ff9, 0x9ff1,
    0xff98, 0x9fa1,
    0xff99, 0xfaa1,
    0xaaaa, 0xaaa1,
    0x1111, 0x1110,
// tile: 60
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x1000, 0x0,
    0xc100, 0x0,
    0xcc10, 0x0,
    0x6cc1, 0x0,
    0xc6c1, 0x0,
// tile: 61
    0x6c6c, 0x1000,
    0x111c, 0x1000,
    0x16c1, 0xc100,
    0x666c, 0x1100,
    0x6616, 0x1100,
    0x6116, 0x1100,
    0x6116, 0x1100,
    0x9666, 0x1100,
// tile: 62
    0x1961, 0xc100,
    0x111c, 0xc100,
    0x6c6c, 0x1000,
    0xc6cc, 0x1000,
    0x6cc1, 0x0,
    0xc6c1, 0x0,
    0x6c10, 0x0,
    0xc100, 0x0,
// tile: 63
    0x1000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
};

const Ruby_Sprite walker_bigSprite0 = 
{
    -16, // x position offset
    -16, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(4, 4), // sgdk sprite size
};

const Ruby_Sprite walker_bigSprite1 = 
{
    -16, // x position offset
    -14, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 16), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(4, 4), // sgdk sprite size
};

const Ruby_Sprite walker_bigSprite2 = 
{
    -16, // x position offset
    -14, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 32), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(4, 4), // sgdk sprite size
};

const Ruby_Sprite walker_bigSprite3 = 
{
    -14, // x position offset
    -16, // y position offset
    -2, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 48), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(4, 4), // sgdk sprite size
};

const Ruby_Sprite walker_bigSprite4 = 
{
    -16, // x position offset
    -14, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 1, 16), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(4, 4), // sgdk sprite size
};

const Ruby_Sprite walker_bigSprite5 = 
{
    -16, // x position offset
    -14, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 1, 32), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(4, 4), // sgdk sprite size
};

const Ruby_Sprite* const walker_bigSpriteArray0[1] = 
{
    &walker_bigSprite0,
};

const Ruby_Sprite* const walker_bigSpriteArray1[1] = 
{
    &walker_bigSprite1,
};

const Ruby_Sprite* const walker_bigSpriteArray2[1] = 
{
    &walker_bigSprite2,
};

const Ruby_Sprite* const walker_bigSpriteArray3[1] = 
{
    &walker_bigSprite3,
};

const Ruby_Sprite* const walker_bigSpriteArray4[1] = 
{
    &walker_bigSprite4,
};

const Ruby_Sprite* const walker_bigSpriteArray5[1] = 
{
    &walker_bigSprite5,
};

extern const Ruby_Frame walker_bigFrame0;
extern const Ruby_Frame walker_bigFrame1;
extern const Ruby_Frame walker_bigFrame2;
extern const Ruby_Frame walker_bigFrame3;
extern const Ruby_Frame walker_bigFrame4;
extern const Ruby_Frame walker_bigFrame5;
extern const Ruby_Frame walker_bigFrame6;
extern const Ruby_Frame walker_bigFrame7;





const Ruby_Frame walker_bigFrame0 = 
{
    walker_bigSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    14, // frame time
    &walker_bigFrame1, // next frame
};


const Ruby_Frame walker_bigFrame1 = 
{
    walker_bigSpriteArray1,
    1, // number of sprites
    0, // frame trigger data offset
    14, // frame time
    &walker_bigFrame2, // next frame
};


const Ruby_Frame walker_bigFrame2 = 
{
    walker_bigSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    14, // frame time
    &walker_bigFrame3, // next frame
};


const Ruby_Frame walker_bigFrame3 = 
{
    walker_bigSpriteArray2,
    1, // number of sprites
    0, // frame trigger data offset
    14, // frame time
    &walker_bigFrame0, // next frame
};


const Ruby_Frame walker_bigFrame4 = 
{
    walker_bigSpriteArray3,
    1, // number of sprites
    0, // frame trigger data offset
    14, // frame time
    &walker_bigFrame5, // next frame
};


const Ruby_Frame walker_bigFrame5 = 
{
    walker_bigSpriteArray4,
    1, // number of sprites
    0, // frame trigger data offset
    14, // frame time
    &walker_bigFrame6, // next frame
};


const Ruby_Frame walker_bigFrame6 = 
{
    walker_bigSpriteArray3,
    1, // number of sprites
    0, // frame trigger data offset
    14, // frame time
    &walker_bigFrame7, // next frame
};


const Ruby_Frame walker_bigFrame7 = 
{
    walker_bigSpriteArray5,
    1, // number of sprites
    0, // frame trigger data offset
    14, // frame time
    &walker_bigFrame4, // next frame
};

const Ruby_Frame* const walker_bigFrames[8] = 
{
    &walker_bigFrame0,
    &walker_bigFrame1,
    &walker_bigFrame2,
    &walker_bigFrame3,
    &walker_bigFrame4,
    &walker_bigFrame5,
    &walker_bigFrame6,
    &walker_bigFrame7,
};

const Ruby_AnimationSetup const walker_bigSetup = 
{
    Animation_DrawObject,
    AnimationUtils_updateStandardAnimation,
    &walker_bigFrame0,
    0,
    14,
};

u16 walker_bigVdpLocation;

const Ruby_Animation walker_big = 
{
    STANDARD_ANIMATION_RESOURCE_TYPE,
    &walker_bigSetup,
    walker_bigFrames,
    8, // number of frames
    32, // width in pixels
    32, // height in pixels
    16, // max tiles per frame
    64, // the total number of tiles in the animation
    (const u32*)walker_bigTileData, // start of the sprite data
    NULL, // frame trigger data blob
    &walker_bigVdpLocation, // location in vdp when loaded
};
