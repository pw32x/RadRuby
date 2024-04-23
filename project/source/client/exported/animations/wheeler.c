#include <genesis.h>
#include "wheeler.h"
#include "engine\FrameTriggers.h"


const unsigned short const wheelerTileData[1376] = // 86 tiles 
{
// tile: 0
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x5,
    0x0000, 0x53,
    0x0000, 0x535,
    0x0000, 0x5b5,
    0x0000, 0x555,
    0x0000, 0x5b5,
// tile: 1
    0x0000, 0x555,
    0x0000, 0x535,
    0x0000, 0x5b,
    0x0000, 0x5,
    0x0000, 0x0,
    0x0000, 0x5,
    0x0000, 0x5b,
    0x0000, 0x5bb,
// tile: 2
    0x0001, 0x111b,
    0x001a, 0xfff1,
    0x001a, 0xaaff,
    0x0001, 0x11aa,
    0x0005, 0x5511,
    0x0005, 0xbb55,
    0x0000, 0x5bbb,
    0x0033, 0x355b,
// tile: 3
    0x0377, 0x7255,
    0x37aa, 0x1127,
    0x3aa1, 0x5b1a,
    0x3aa1, 0x5b1a,
    0x3fa1, 0x551a,
    0x3ffa, 0x11aa,
    0x03ff, 0xaaaa,
    0x0033, 0x3333,
// tile: 4
    0x0555, 0x5555,
    0x5355, 0xaaaa,
    0x35bb, 0x5aaa,
    0x5bbb, 0xb5a5,
    0xbbbb, 0xbb5f,
    0x5555, 0x5555,
    0x5aaa, 0x111a,
    0xafff, 0x161f,
// tile: 5
    0xafff, 0x1911,
    0xafff, 0x1691,
    0x5aff, 0xf169,
    0xb5ff, 0xff11,
    0x5555, 0x5555,
    0x3333, 0x3300,
    0xb25b, 0x1110,
    0xbb21, 0x66e1,
// tile: 6
    0xbb16, 0x61ee,
    0x1516, 0x1511,
    0xf166, 0x1551,
    0xf166, 0x1551,
    0x1516, 0x1511,
    0x5516, 0x61ee,
    0xb551, 0x66e1,
    0xbb51, 0x1110,
// tile: 7
    0x5530, 0x0,
    0x7773, 0x0,
    0xa3f3, 0x0,
    0xa3f3, 0x0,
    0xa3a3, 0x0,
    0xa3a3, 0x0,
    0x3a30, 0x0,
    0x3300, 0x0,
// tile: 8
    0x5000, 0x0,
    0xa500, 0x0,
    0xaa50, 0x0,
    0x5555, 0x5000,
    0xffff, 0x5000,
    0x5555, 0x5000,
    0xa115, 0x0,
    0x1195, 0x0,
// tile: 9
    0x1165, 0x0,
    0x1695, 0x0,
    0x6950, 0x0,
    0x1500, 0x0,
    0x5000, 0x0,
    0x0000, 0x0,
    0x0111, 0x0,
    0x166e, 0x1000,
// tile: 10
    0x161e, 0xe100,
    0x6101, 0x1100,
    0x6100, 0x0,
    0x6100, 0x0,
    0x6101, 0x1100,
    0x161e, 0xe100,
    0x166e, 0x1000,
    0x0111, 0x0,
// tile: 11
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 12
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x5,
    0x0000, 0x53,
    0x0000, 0x535,
    0x0000, 0x5b5,
    0x0000, 0x555,
    0x0000, 0x5b5,
// tile: 13
    0x0000, 0x555,
    0x0000, 0x535,
    0x0000, 0x5b,
    0x0000, 0x5,
    0x0000, 0x0,
    0x0000, 0x5,
    0x0000, 0x5b,
    0x0000, 0x5bb,
// tile: 14
    0x0001, 0x111b,
    0x001a, 0xfff1,
    0x001a, 0xaaff,
    0x0001, 0x11aa,
    0x0005, 0x5511,
    0x0005, 0xbb55,
    0x0033, 0x5bbb,
    0x0377, 0x355b,
// tile: 15
    0x37aa, 0x1255,
    0x3aa1, 0x5b1a,
    0x3fa1, 0x5b1a,
    0x3fa1, 0x551a,
    0x3faa, 0x11aa,
    0x03fa, 0xaaaa,
    0x0033, 0x3333,
    0x0000, 0x0,
// tile: 16
    0x0555, 0x5555,
    0x5355, 0xaaaa,
    0x35bb, 0x5aaa,
    0x5bbb, 0xb5a5,
    0xbbbb, 0xbb5f,
    0x5555, 0x5555,
    0x5aaa, 0x111a,
    0xafff, 0x161f,
// tile: 17
    0xafff, 0x1911,
    0xafff, 0x1691,
    0x5aff, 0xf169,
    0xb5ff, 0xff11,
    0x5555, 0x5555,
    0x3333, 0x3300,
    0xb25b, 0x1110,
    0xbb21, 0x66e1,
// tile: 18
    0xbb11, 0x66e1,
    0x1516, 0x61ee,
    0xf116, 0x1511,
    0xf116, 0x61ee,
    0x1551, 0x66e1,
    0x5551, 0x1110,
    0xbb55, 0x0,
    0xbb50, 0x0,
// tile: 19
    0x5573, 0x0,
    0xa3a3, 0x0,
    0xa3f3, 0x0,
    0xa3f3, 0x0,
    0xa3a3, 0x0,
    0x3a30, 0x0,
    0x3300, 0x0,
    0x0000, 0x0,
// tile: 20
    0x5000, 0x0,
    0xa500, 0x0,
    0xaa50, 0x0,
    0x5555, 0x5000,
    0xffff, 0x5000,
    0x5555, 0x5000,
    0xa115, 0x0,
    0x1195, 0x0,
// tile: 21
    0x1165, 0x0,
    0x1695, 0x0,
    0x6950, 0x0,
    0x1500, 0x0,
    0x5000, 0x0,
    0x0000, 0x0,
    0x0111, 0x0,
    0x166e, 0x1000,
// tile: 22
    0x166e, 0x1100,
    0x161e, 0xe100,
    0x6101, 0x1100,
    0x161e, 0xe000,
    0x166e, 0x1000,
    0x0111, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 23
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 24
    0x0000, 0x555,
    0x0000, 0x5aaa,
    0x0005, 0xaaaa,
    0x0555, 0x555a,
    0x05ff, 0xfff5,
    0x0555, 0x5555,
    0x0051, 0x1aa1,
    0x0059, 0x11f1,
// tile: 25
    0x0056, 0x1111,
    0x0059, 0x6119,
    0x0005, 0x9696,
    0x0000, 0x5111,
    0x0000, 0x555,
    0x0000, 0x0,
    0x0011, 0x1001,
    0x01e6, 0x611e,
// tile: 26
    0x1ee1, 0x61ee,
    0x1110, 0x1611,
    0x0000, 0x1615,
    0x0000, 0x1615,
    0x1110, 0x1611,
    0x1ee1, 0x61ee,
    0x01e6, 0x611e,
    0x0011, 0x1001,
// tile: 27
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 28
    0x5555, 0x5000,
    0xaa55, 0x3500,
    0xa5bb, 0x5350,
    0x5bbb, 0xb535,
    0xbbbb, 0xbb53,
    0x5555, 0x555b,
    0x11aa, 0xa555,
    0x61ff, 0xfa5b,
// tile: 29
    0x91ff, 0xfa55,
    0x61ff, 0xfa53,
    0x1fff, 0xa5b5,
    0xffff, 0x5b50,
    0x5555, 0x5500,
    0x3333, 0x3350,
    0x11b5, 0x2bb5,
    0x6612, 0xbbbb,
// tile: 30
    0x1661, 0xbbb1,
    0x5161, 0x511f,
    0x5166, 0x1fff,
    0x5166, 0x1faa,
    0x5161, 0x5111,
    0x1661, 0x5555,
    0x6615, 0x5bbb,
    0x1115, 0xbbb5,
// tile: 31
    0x0003, 0x5555,
    0x0037, 0x3772,
    0x003f, 0x3aa1,
    0x003f, 0x3aa1,
    0x003a, 0x3aa1,
    0x003a, 0x3aaa,
    0x0003, 0xa3aa,
    0x0000, 0x3333,
// tile: 32
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x5000, 0x0,
    0x5000, 0x0,
    0x5000, 0x0,
    0x5000, 0x0,
// tile: 33
    0x5000, 0x0,
    0x5000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x5000, 0x0,
// tile: 34
    0x1110, 0x0,
    0xffa1, 0x0,
    0xaaa1, 0x0,
    0x1110, 0x0,
    0x5550, 0x0,
    0xbb50, 0x0,
    0xb500, 0x0,
    0x5333, 0x0,
// tile: 35
    0x2777, 0x3000,
    0x11aa, 0x7300,
    0xb51a, 0xa300,
    0xb51a, 0xa300,
    0x551a, 0xf300,
    0x11af, 0xf300,
    0xaaff, 0x3000,
    0x3333, 0x0,
// tile: 36
    0x0000, 0x555,
    0x0000, 0x5aaa,
    0x0005, 0xaaaa,
    0x0555, 0x555a,
    0x05ff, 0xfff5,
    0x0555, 0x5555,
    0x0051, 0x1aa1,
    0x0059, 0x11f1,
// tile: 37
    0x0056, 0x1111,
    0x0059, 0x6119,
    0x0005, 0x9696,
    0x0000, 0x5111,
    0x0000, 0x555,
    0x0000, 0x0,
    0x0011, 0x1001,
    0x01e6, 0x611e,
// tile: 38
    0x11e6, 0x611e,
    0x1ee1, 0x61ee,
    0x1110, 0x1611,
    0x0ee1, 0x61ee,
    0x01e6, 0x611e,
    0x0011, 0x1001,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 39
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 40
    0x5555, 0x5000,
    0xaa55, 0x3500,
    0xa5bb, 0x5350,
    0x5bbb, 0xb535,
    0xbbbb, 0xbb53,
    0x5555, 0x555b,
    0x11aa, 0xa555,
    0x61ff, 0xfa5b,
// tile: 41
    0x91ff, 0xfa55,
    0x61ff, 0xfa53,
    0x1fff, 0xa5b5,
    0xffff, 0x5b50,
    0x5555, 0x5500,
    0x3333, 0x3350,
    0x11b5, 0x2bb5,
    0x6612, 0xbbbb,
// tile: 42
    0x6611, 0xbbb1,
    0x1661, 0x511f,
    0x5161, 0x1fff,
    0x1661, 0x1faa,
    0x6615, 0x5111,
    0x1115, 0x5555,
    0x0055, 0x5bbb,
    0x0005, 0xbbb5,
// tile: 43
    0x0037, 0x5555,
    0x003a, 0x3aa1,
    0x003f, 0x3aa1,
    0x003f, 0x3aa1,
    0x003a, 0x3aaa,
    0x0003, 0xa3aa,
    0x0000, 0x3333,
    0x0000, 0x0,
// tile: 44
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x5000, 0x0,
    0x5000, 0x0,
    0x5000, 0x0,
    0x5000, 0x0,
// tile: 45
    0x5000, 0x0,
    0x5000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x5000, 0x0,
// tile: 46
    0x1110, 0x0,
    0xffa1, 0x0,
    0xaaa1, 0x0,
    0x1110, 0x0,
    0x5550, 0x0,
    0xbb50, 0x0,
    0xb533, 0x0,
    0x5377, 0x3000,
// tile: 47
    0x21aa, 0x7300,
    0xb51a, 0xa300,
    0xb51a, 0xf300,
    0x551a, 0xf300,
    0x11aa, 0xf300,
    0xaaaf, 0x3000,
    0x3333, 0x0,
    0x0000, 0x0,
// tile: 48
    0x0000, 0x0,
    0x0000, 0x53,
    0x0000, 0x55,
    0x0000, 0x5bb,
    0x0000, 0x555,
    0x0000, 0x55f,
    0x0000, 0x55f,
    0x0000, 0x5ff,
// tile: 49
    0x01e1, 0xe5ff,
    0x1ee1, 0xe5ff,
    0x1615, 0x15ff,
    0x1661, 0x665f,
    0x0166, 0x6105,
    0x001a, 0xf100,
    0x001a, 0xf111,
    0x0001, 0xafff,
// tile: 50
    0x0001, 0x1aaa,
    0x0000, 0x11,
    0x0000, 0x5b,
    0x0000, 0x5b,
    0x0000, 0x5b,
    0x0000, 0x5b,
    0x0000, 0x5b,
    0x0000, 0x5,
// tile: 51
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 52
    0x5555, 0x5555,
    0x5555, 0x5555,
    0x5fff, 0xfff5,
    0x5555, 0x5555,
    0xff11, 0x11ff,
    0xf169, 0x691f,
    0x1691, 0x1691,
    0x1911, 0x1161,
// tile: 53
    0x161f, 0xf191,
    0x1911, 0x1161,
    0x1691, 0x1691,
    0xf169, 0x691f,
    0xff11, 0x11ff,
    0x5555, 0x5555,
    0x3333, 0x3333,
    0x1bbb, 0xbbb1,
// tile: 54
    0x1bbb, 0xbbb1,
    0xbbbb, 0xbbbb,
    0xbbbb, 0xbbbb,
    0xbbbb, 0xbbbb,
    0xbbbb, 0xbbbb,
    0xbbbb, 0xbbbb,
    0xbbbb, 0xbbbb,
    0xbbbb, 0xbbbb,
// tile: 55
    0x5555, 0x5555,
    0x003a, 0xa300,
    0x03aa, 0xaa30,
    0x03aa, 0xaa30,
    0x03aa, 0xaa30,
    0x03aa, 0xaa30,
    0x03aa, 0xaa30,
    0x0033, 0x3300,
// tile: 56
    0x0000, 0x0,
    0x3500, 0x0,
    0x5500, 0x0,
    0xbb50, 0x0,
    0x5550, 0x0,
    0xf550, 0x0,
    0xf550, 0x0,
    0xff50, 0x0,
// tile: 57
    0xff5e, 0x1e10,
    0xff5e, 0x1ee1,
    0xff51, 0x5161,
    0xf566, 0x1661,
    0x5016, 0x6610,
    0x001f, 0xa100,
    0x111f, 0xa100,
    0xfffa, 0x1000,
// tile: 58
    0xaaa1, 0x1000,
    0x1100, 0x0,
    0xb500, 0x0,
    0xb500, 0x0,
    0xb500, 0x0,
    0xb500, 0x0,
    0xb500, 0x0,
    0x5000, 0x0,
// tile: 59
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 60
    0x0000, 0x5555,
    0x0005, 0x355a,
    0x0053, 0x5bb5,
    0x0535, 0xbbbb,
    0x535b, 0xbbbb,
    0x5b55, 0x5555,
    0x5555, 0xaaa1,
    0x5b5a, 0xfff1,
// tile: 61
    0x555a, 0xfff1,
    0x535a, 0xfff1,
    0x05b5, 0xafff,
    0x005b, 0x5fff,
    0x0005, 0x5555,
    0x0000, 0x3333,
    0x0005, 0xbbbb,
    0x005b, 0xbbbb,
// tile: 62
    0x011b, 0xbbbb,
    0x1af1, 0xbbbb,
    0x1af1, 0xb511,
    0x0af1, 0x1166,
    0x01af, 0xf661,
    0x011a, 0xa615,
    0x0051, 0x1661,
    0x0005, 0x5166,
// tile: 63
    0x0003, 0xb511,
    0x0037, 0xaa11,
    0x003a, 0xa15b,
    0x003a, 0xa15b,
    0x003f, 0xa155,
    0x003f, 0xfa11,
    0x0003, 0xffaa,
    0x0000, 0x3333,
// tile: 64
    0x5555, 0x0,
    0xaaaa, 0x5000,
    0xaaaa, 0xa500,
    0x5a55, 0x5555,
    0xb5ff, 0xfff5,
    0x5555, 0x5555,
    0x11aa, 0x1150,
    0x61f1, 0x1950,
// tile: 65
    0x9111, 0x1650,
    0x6911, 0x6950,
    0x1696, 0x9500,
    0xf111, 0x5000,
    0x5555, 0x0,
    0x3333, 0x0,
    0xbbbb, 0x5000,
    0xbbbb, 0xb500,
// tile: 66
    0xbbbb, 0xb500,
    0xbbbb, 0xb500,
    0x1b51, 0x1100,
    0xe116, 0x6e10,
    0xee16, 0x1ee1,
    0x1161, 0x5111,
    0xee16, 0x1ee1,
    0xe116, 0x6e10,
// tile: 67
    0x1551, 0x1100,
    0x2aa3, 0x7300,
    0x1aa3, 0xf300,
    0x1aa3, 0xf300,
    0x1aa3, 0xa300,
    0xaaa3, 0xa300,
    0xaa3a, 0x3000,
    0x3333, 0x0,
// tile: 68
    0x0000, 0x5555,
    0x0005, 0x355a,
    0x0053, 0x5bb5,
    0x0535, 0xbbbb,
    0x535b, 0xbbbb,
    0x5b55, 0x5555,
    0x5555, 0x11aa,
    0x5b51, 0x611f,
// tile: 69
    0x5551, 0x9111,
    0x5351, 0x6911,
    0x05b5, 0x1696,
    0x005b, 0x5111,
    0x0005, 0x5555,
    0x0000, 0x3333,
    0x0005, 0xbbbb,
    0x005b, 0xbbbb,
// tile: 70
    0x011b, 0xbbbb,
    0x1af1, 0xbbbb,
    0x1af1, 0xb511,
    0x0af1, 0x1166,
    0x01af, 0xf661,
    0x011a, 0xa615,
    0x0051, 0x1661,
    0x0005, 0x5166,
// tile: 71
    0x0003, 0xb511,
    0x0037, 0xaa11,
    0x003a, 0xa15b,
    0x003a, 0xa15b,
    0x003f, 0xa155,
    0x003f, 0xfa11,
    0x0003, 0xffaa,
    0x0000, 0x3333,
// tile: 72
    0x5555, 0x0,
    0xaaaa, 0x5000,
    0xaaaa, 0xa500,
    0x5a55, 0x5555,
    0xb5ff, 0xfff5,
    0x5555, 0x5555,
    0x11aa, 0xaa50,
    0x191f, 0xff50,
// tile: 73
    0x161f, 0xff50,
    0x691f, 0xff50,
    0x91ff, 0xf500,
    0x1fff, 0x5000,
    0x5555, 0x0,
    0x3333, 0x0,
    0xbbbb, 0x5000,
    0xbbbb, 0xb500,
// tile: 74
    0xbbbb, 0xb500,
    0xbbbb, 0xb500,
    0x1b51, 0x1100,
    0xe116, 0x6e10,
    0xee16, 0x1ee1,
    0x1161, 0x5111,
    0xee16, 0x1ee1,
    0xe116, 0x6e10,
// tile: 75
    0x1551, 0x1100,
    0x2aa3, 0x7300,
    0x1aa3, 0xf300,
    0x1aa3, 0xf300,
    0x1aa3, 0xa300,
    0xaaa3, 0xa300,
    0xaa3a, 0x3000,
    0x3333, 0x0,
// tile: 76
    0x0005, 0x5555,
    0x005b, 0x5fff,
    0x05b5, 0xafff,
    0x535a, 0xfff1,
    0x555a, 0xfff1,
    0x5b5a, 0xfff1,
    0x5555, 0xaaa1,
    0x5b55, 0x5555,
// tile: 77
    0x535b, 0xbbbb,
    0x0535, 0xbbbb,
    0x0053, 0x5bb5,
    0x0005, 0x355a,
    0x0000, 0x5555,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 78
    0x5555, 0x0,
    0xf111, 0x5000,
    0x1696, 0x9500,
    0x6911, 0x6950,
    0x9111, 0x1650,
    0x61f1, 0x1950,
    0x11aa, 0x1150,
    0x5555, 0x5555,
// tile: 79
    0xb5ff, 0xfff5,
    0x5a55, 0x5555,
    0xaaaa, 0xa500,
    0xaaaa, 0x5000,
    0x5555, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 80
    0x0000, 0x1100,
    0x0016, 0x6e11,
    0x0166, 0x1ee1,
    0x0161, 0x110,
    0x1661, 0x0,
    0x1661, 0x0,
    0x0161, 0x110,
    0x0166, 0x1ee1,
// tile: 81
    0x0016, 0x6e11,
    0x0011, 0x1100,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 82
    0x0033, 0x3333,
    0x03aa, 0xaaaa,
    0x3aaa, 0x11aa,
    0x3aa1, 0x5b1a,
    0x3aa1, 0x5b1a,
    0x3fa1, 0x551a,
    0x3ffa, 0x11aa,
    0x03ff, 0xaaaa,
// tile: 83
    0x0033, 0x3333,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
// tile: 84
    0x3300, 0x0,
    0x3a30, 0x0,
    0xa3a3, 0x0,
    0xa3f3, 0x0,
    0xa3f3, 0x0,
    0xa3a3, 0x0,
    0xa3a3, 0x0,
    0x3a30, 0x0,
// tile: 85
    0x3300, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
    0x0000, 0x0,
};

const GGSprite wheelerSprite0 = 
{
    2, // x position offset
    0, // y position offset
    -2, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 4), // sgdk sprite size
};

const GGSprite wheelerSprite1 = 
{
    2, // x position offset
    1, // y position offset
    -2, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 12), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 4), // sgdk sprite size
};

const GGSprite wheelerSprite2 = 
{
    0, // x position offset
    0, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 24), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 4), // sgdk sprite size
};

const GGSprite wheelerSprite3 = 
{
    0, // x position offset
    1, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 36), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 4), // sgdk sprite size
};

const GGSprite wheelerSprite4 = 
{
    0, // x position offset
    0, // y position offset
    0, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 48), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(3, 4), // sgdk sprite size
};

const GGSprite wheelerSprite5 = 
{
    4, // x position offset
    0, // y position offset
    4, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 60), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 4), // sgdk sprite size
};

const GGSprite wheelerSprite6 = 
{
    4, // x position offset
    0, // y position offset
    4, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 68), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 4), // sgdk sprite size
};

const GGSprite wheelerSprite7 = 
{
    4, // x position offset
    9, // y position offset
    4, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 76), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const GGSprite wheelerSprite8 = 
{
    8, // x position offset
    11, // y position offset
    8, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 80), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(1, 2), // sgdk sprite size
};

const GGSprite wheelerSprite9 = 
{
    8, // x position offset
    11, // y position offset
    8, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 1, 80), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(1, 2), // sgdk sprite size
};

const GGSprite wheelerSprite10 = 
{
    6, // x position offset
    12, // y position offset
    2, // x flipped position offset
    TILE_ATTR_FULL(PAL0, 0, 0, 0, 82), // tile attribute and tile offset in sprite tile data
    SPRITE_SIZE(2, 2), // sgdk sprite size
};

const GGSprite* const wheelerSpriteArray0[1] = 
{
    &wheelerSprite0,
};

const GGSprite* const wheelerSpriteArray1[1] = 
{
    &wheelerSprite1,
};

const GGSprite* const wheelerSpriteArray2[1] = 
{
    &wheelerSprite2,
};

const GGSprite* const wheelerSpriteArray3[1] = 
{
    &wheelerSprite3,
};

const GGSprite* const wheelerSpriteArray4[1] = 
{
    &wheelerSprite4,
};

const GGSprite* const wheelerSpriteArray5[1] = 
{
    &wheelerSprite5,
};

const GGSprite* const wheelerSpriteArray6[1] = 
{
    &wheelerSprite6,
};

const GGSprite* const wheelerSpriteArray7[1] = 
{
    &wheelerSprite7,
};

const GGSprite* const wheelerSpriteArray8[1] = 
{
    &wheelerSprite8,
};

const GGSprite* const wheelerSpriteArray9[1] = 
{
    &wheelerSprite9,
};

const GGSprite* const wheelerSpriteArray10[1] = 
{
    &wheelerSprite10,
};

extern const GGFrame wheelerFrame0;
extern const GGFrame wheelerFrame1;
extern const GGFrame wheelerFrame2;
extern const GGFrame wheelerFrame3;
extern const GGFrame wheelerFrame4;
extern const GGFrame wheelerFrame5;
extern const GGFrame wheelerFrame6;
extern const GGFrame wheelerFrame7;
extern const GGFrame wheelerFrame8;
extern const GGFrame wheelerFrame9;
extern const GGFrame wheelerFrame10;





const GGFrame wheelerFrame0 = 
{
    wheelerSpriteArray0,
    1, // number of sprites
    0, // frame trigger data offset
    6, // frame time
    &wheelerFrame1, // next frame
};


const GGFrame wheelerFrame1 = 
{
    wheelerSpriteArray1,
    1, // number of sprites
    0, // frame trigger data offset
    6, // frame time
    &wheelerFrame2, // next frame
};


const GGFrame wheelerFrame2 = 
{
    wheelerSpriteArray2,
    1, // number of sprites
    0, // frame trigger data offset
    6, // frame time
    &wheelerFrame3, // next frame
};


const GGFrame wheelerFrame3 = 
{
    wheelerSpriteArray3,
    1, // number of sprites
    0, // frame trigger data offset
    6, // frame time
    &wheelerFrame4, // next frame
};


const GGFrame wheelerFrame4 = 
{
    wheelerSpriteArray4,
    1, // number of sprites
    0, // frame trigger data offset
    29, // frame time
    &wheelerFrame5, // next frame
};


const GGFrame wheelerFrame5 = 
{
    wheelerSpriteArray5,
    1, // number of sprites
    0, // frame trigger data offset
    59, // frame time
    &wheelerFrame6, // next frame
};


const GGFrame wheelerFrame6 = 
{
    wheelerSpriteArray6,
    1, // number of sprites
    0, // frame trigger data offset
    59, // frame time
    &wheelerFrame7, // next frame
};


const GGFrame wheelerFrame7 = 
{
    wheelerSpriteArray7,
    1, // number of sprites
    0, // frame trigger data offset
    6, // frame time
    &wheelerFrame8, // next frame
};


const GGFrame wheelerFrame8 = 
{
    wheelerSpriteArray8,
    1, // number of sprites
    0, // frame trigger data offset
    6, // frame time
    &wheelerFrame9, // next frame
};


const GGFrame wheelerFrame9 = 
{
    wheelerSpriteArray9,
    1, // number of sprites
    0, // frame trigger data offset
    6, // frame time
    &wheelerFrame10, // next frame
};


const GGFrame wheelerFrame10 = 
{
    wheelerSpriteArray10,
    1, // number of sprites
    0, // frame trigger data offset
    6, // frame time
    &wheelerFrame0, // loop to next frame. 
};

const GGFrame* const wheelerFrames[11] = 
{
    &wheelerFrame0,
    &wheelerFrame1,
    &wheelerFrame2,
    &wheelerFrame3,
    &wheelerFrame4,
    &wheelerFrame5,
    &wheelerFrame6,
    &wheelerFrame7,
    &wheelerFrame8,
    &wheelerFrame9,
    &wheelerFrame10,
};



const GGAnimation wheeler = 
{
    STANDARD_ANIMATION_RESOURCE_TYPE,
    wheelerFrames,
    11, // number of frames
    24, // width in pixels
    32, // height in pixels
    12, // max tiles per frame
    86, // the total number of tiles in the animation
    (const u32*)wheelerTileData, // start of the sprite data
    NULL, // frame trigger data blob
};
