#ifndef VDP_TILE_MANAGER_INCLUDE_H
#define VDP_TILE_MANAGER_INCLUDE_H

#include "engine/base_types.h"
#include "engine/animation_types.h"
#include "engine/map_types.h"

void VDPTileManager_Init(void);

u8 VDPTileManager_LoadSpriteTiles(const u32* tileData, 
								  u16 tileCount,
								  u16* vdpLocation); 

u8 VDPTileManager_ReserveSpriteTilesArea(u16 tileCount, 
										 u16* vdpLocation);

u16 VDPTileManager_LoadBackgroundTileset(const u32* tileData, 
										 u16 tileCount,
										 u16* vdpLocation);




#endif