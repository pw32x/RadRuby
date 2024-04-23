#include "terrain_manager.h"

#include "engine/map_types.h"
//#include "engine/map_manager.h"
//#include "engine/scroll_manager.h"

#include <string.h>

const Ruby_StripMap* TerrainManager_stripMap;

u8 TerrainManager_terrain[TERRAIN_SIDE * TERRAIN_SIDE]; // 192 bytes
const u8* TerrainManager_currentTerrainMapStrip;

void TerrainManager_Init(void)
{
	memset(TerrainManager_terrain, 0, sizeof(TerrainManager_terrain));

	for (u8 loop = 0; loop < TERRAIN_SIDE; loop++)
	{
		TerrainManager_UpdateTerrain(loop);
	}
}

void TerrainManager_Init_Strip(const Ruby_StripMap* stripMap)
{
	TerrainManager_stripMap = stripMap;

	memset(TerrainManager_terrain, 0, sizeof(TerrainManager_terrain));

	TerrainManager_currentTerrainMapStrip = TerrainManager_stripMap->terrainMap;

	for (u8 loop = 0; loop < TERRAIN_SIDE; loop++)
	{
		TerrainManager_UpdateTerrain_Strip(loop);
		TerrainManager_currentTerrainMapStrip += TerrainManager_stripMap->mapHeight;
	}
}

void TerrainManager_UpdateTerrain(u16 mapColumnIndex)
{
	/*
	const u16* mapRunner = MapManager_mapData + mapColumnIndex;
	u8* terrainRunner = TerrainManager_terrain + (mapColumnIndex & TERRAIN_SIDE_MINUS_ONE);

	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;

	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;

	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*/
	
}

void TerrainManager_UpdateTerrain_Strip(u8 mapColumnIndex)
{
	const u8* terrainStripRunner = TerrainManager_currentTerrainMapStrip;

	u8* terrainRunner = TerrainManager_terrain + ((mapColumnIndex & TERRAIN_SIDE_MINUS_ONE) << TERRAIN_SIDE_SHIFT);
	
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
}