#ifndef VDP_TILE_MANAGER_INCLUDE_H
#define VDP_TILE_MANAGER_INCLUDE_H

#include "engine/base_types.h"
#include "engine/animation_types.h"
#include "engine/map_types.h"

#define VDP_REGION_MAIN	0
#define VDP_REGION_EXT1 1
#define VDP_REGION_EXT2 2
#define NUM_VDP_REGIONS 3

void VDPTileManager_Init(void);

void VDPTileManager_LoadTilesToVDP(u8 region, const u32* tiles, u16 numTiles, u16* vdpLocation);
void VDPTileManager_LoadTilesToVDPMain(const u32* tiles, u16 numTiles, u16* vdpLocation);

#endif