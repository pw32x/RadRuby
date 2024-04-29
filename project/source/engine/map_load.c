#include "map_load.h"
#include "engine/resource_manager.h"
//#include "engine/map_manager.h"
#include "engine/vdptile_manager.h"

#include <string.h>



u16 Load_MapResource(const Resource* resource)
{
	/*
	const Map* map = (const Map*)resource->resource;

	MapManager_mapWidth = map->mapWidth;
	MapManager_mapHeight = map->mapHeight;
	MapManager_mapData = map->mapData;
	MapManager_numTilesets = 0; // we'll leave it to the tile loading to take care of this
	MapManager_metatileLutsDataSize = 0;

	MapManager_mapResource = resource;

	for (u16 loop = 0; loop < METATILE_LUT_DATA_SIZE; loop++)
	{
		MapManager_metatileLutsData[loop] = 0xcc;
	}

	const Resource** tilesetRunner = map->tilesetResources;

	for (u8 loop = 0; loop < map->numTilesets; loop++)
	{
		ResourceManager_LoadResource(*tilesetRunner);

		tilesetRunner++;
	}
	*/

	return NULL;
}

u16 Load_StripMapResource(const Resource* resource)
{
	const Ruby_StripMap* stripMap = (const Ruby_StripMap*)resource;
	//
	////kprintf("type: %d\n", stripMap->resourceType);
	////kprintf("width: %d\n", stripMap->mapWidth);
	////kprintf("height: %d\n", stripMap->mapHeight);
	//
	//MapManager_mapWidth = stripMap->mapWidth;
	//MapManager_mapHeight = stripMap->mapHeight;
	//MapManager_mapData = stripMap->stripMapData;
	//MapManager_numTilesets = 1; // we'll leave it to the tile loading to take care of this
	//MapManager_mapResource = resource;
	//
	//MapManager_terrainMapStrips = stripMap->terrainMap;
	//MapManager_terrainMapWidth = stripMap->terrainMapWidth;
	//MapManager_terrainMapHeight = stripMap->terrainMapHeight;
	//
	////kprintf("strip map data\n");
	////kprintf("resource type: %d\n", MapManager_mapResource->resource->resourceType);
	////kprintf("bank: %d\n", MapManager_mapResource->bankNumber);
	////kprintf("resource: %u\n", (u16)MapManager_mapResource->resource);

	/*
	const u16* MapManager_mapDataRunner = MapManager_mapData;

	kprintf("Load_StripMapResource map\n");

	for (int loop = 0; loop < MapManager_mapWidth; loop++)
	{
		for (int loop2 = 0; loop2 < MapManager_mapHeight; loop2++)
		{
			kprintf("%u, ", *MapManager_mapDataRunner);
			MapManager_mapDataRunner++;
		}

		kprintf("\n");
	}

	const u8* terrainRunner = MapManager_terrainMapStrips;

	for (int loop = 0; loop < MapManager_terrainMapWidth; loop++)
	{
		for (int loop2 = 0; loop2 < MapManager_terrainMapHeight; loop2++)
		{
			kprintf("%u, ", *terrainRunner);
			terrainRunner++;
		}

		kprintf("\n");
	}
	*/

	Load_TilesetResourceSimple(stripMap->tilesetResource);

	return NULL;
}

u16 Load_TilesetResource(const Resource* resource)
{
	/*
	const Tileset* tileset = (const Tileset*)resource->resource;

	VDPTileManager_LoadBackgroundTileset(tileset->tiles, 
										 tileset->numTiles,
										 tileset->vdpLocation);

	MapManager_metatileLuts[MapManager_numTilesets] = (u16*)(MapManager_metatileLutsData + MapManager_metatileLutsDataSize);

	u16 metatileLutDataSize = tileset->numMetatiles * 2 * 4;

	memcpy(MapManager_metatileLuts[MapManager_numTilesets], tileset->metatile_lut, metatileLutDataSize);

	MapManager_metatileLutsDataSize += metatileLutDataSize;

	memcpy(&MapManager_tilesets[MapManager_numTilesets], tileset, sizeof(Tileset));

	MapManager_tilesetVdpLocations[MapManager_numTilesets] = *tileset->vdpLocation;
	MapManager_numTilesets++;
	*/
	return 0;
}

u16 Load_TilesetResourceSimple(const Resource* resource)
{
	const Ruby_Tileset* tileset = (const Ruby_Tileset*)resource;

	VDPTileManager_LoadTilesToVDPMain(tileset->tiles, 
									  tileset->numTiles,
									  tileset->vdpLocation);

	//kprintf("num tiles: %d\n", tileset->numTiles);
	//kprintf("tileset resource type: %d\n", tileset->resourceType);
	//kprintf("vdp location: %d\n", *tileset->vdpLocation);

	return 0;
}

u16 Load_AnimatedTilesetResource(const Resource* resource)
{
	/*
	const AnimatedTileset* animatedTileset = (const AnimatedTileset*)resource->resource;

	u16 vdpLocation = (u16)ResourceManager_LoadResource(animatedTileset->tileAnimationResource);


	MapManager_metatileLuts[MapManager_numTilesets] = (u16*)(MapManager_metatileLutsData + MapManager_metatileLutsDataSize);

	u16 metatileLutDataSize = animatedTileset->numMetatiles * 2 * 4;

	memcpy(MapManager_metatileLuts[MapManager_numTilesets], animatedTileset->metatile_lut, metatileLutDataSize);

	MapManager_metatileLutsDataSize += metatileLutDataSize;

	memcpy(&MapManager_tilesets[MapManager_numTilesets], animatedTileset, sizeof(AnimatedTileset));

	MapManager_tilesetVdpLocations[MapManager_numTilesets] = vdpLocation;
	MapManager_numTilesets++;
	*/
	return 0;
}