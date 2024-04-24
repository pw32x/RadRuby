#ifndef MAP_LOAD_INCLUDE_H
#define MAP_LOAD_INCLUDE_H

#include "genesis.h"
#include "engine/resource_types.h"

u16 Load_MapResource(const Resource* resource);
u16 Load_StripMapResource(const Resource* resource);
u16 Load_TilesetResource(const Resource* resource);
u16 Load_TilesetResourceSimple(const Resource* resource);
u16 Load_AnimatedTilesetResource(const Resource* resource);

#endif