#ifndef MAP_TYPES_INCLUDE_H
#define MAP_TYPES_INCLUDE_H

#include "genesis.h"

//#include "engine/base_types.h"
#include "engine/resource_types.h"
//#include "engine/command_types.h"
//#include "engine/gameobject_template_types.h"

//#include "animation_types.h"

// exported format of map values
// terrain_type  | blockmap_index | block_index
// 1111            111              111111111
// 0 - 15          0 - 7            0 - 511

#define MAX_TILES           512
#define MAX_TILESETS        8
#define MAX_TERRAIN_TYPES   16

#define BLOCK_MASK          0x01FF
#define TILESET_INDEX_MASK  0x0E00
#define TERRAIN_TYPE_MASK   0xF000

#define SHORT_TILESET_INDEX_MASK    0x07

#define TILESET_INDEX_SHIFT 9
#define TERRAIN_TYPE_SHIFT 12


#define COMMON_TILESET_PROPERTIES \
    u8 resourceType;\
    const u16* const metatile_lut;\
    const u16 numMetatiles;\
    const u8 breakable

typedef struct
{
    COMMON_TILESET_PROPERTIES;
    const u32* const tiles;
    const u16 numTiles;
    u16* vdpLocation;
} Ruby_Tileset;

typedef struct
{
    COMMON_TILESET_PROPERTIES;
    const Resource* tileAnimationResource;
} Ruby_AnimatedTileset;

typedef struct
{
    u8 resourceType;
    const u16* const mapData;
    const Resource** const tilesetResources;
    u8 numTilesets;
    u16 mapWidth;
    u16 mapHeight;
} Ruby_Map;


typedef struct
{
    u8 resourceType;
    const u16* const stripMapData;
    const Resource* const tilesetResource;
    u16 mapWidth;
    u16 mapHeight;
    const u8* const terrainMap;
    u16 terrainMapWidth;
    u16 terrainMapHeight;
} Ruby_StripMap;


#endif