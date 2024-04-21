#ifndef VDPTYPES_INCLUDE_H
#define VDPTYPES_INCLUDE_H

#include <genesis.h>
#include <vdp_spr.h>
#include <vdp_tile.h>

#define GET_DIRECTION(tileInfo) (tileInfo & TILE_ATTR_HFLIP_MASK)
#define GET_PRIORITY(tileAttr) ((tileAttr & TILE_ATTR_PRIORITY_MASK) >> 15)

typedef u16 VDPTileIndex;

extern VDPSprite* currentSpriteDef;
extern u8 spriteDrawIndex;

#define MyVDP_resetSprites()\
    currentSpriteDef = vdpSpriteCache;\
    spriteDrawIndex = 0;

#define MyVDP_setLastSprite() \
    if (spriteDrawIndex < SAT_MAX_SIZE)\
    {\
		currentSpriteDef->size_link = 0;\
		currentSpriteDef->attribut = 0;\
        currentSpriteDef->x = 0;\
		currentSpriteDef->y = 0;\
    }\
    highestVDPSpriteIndex = spriteDrawIndex + 1;

#endif
