#ifndef MAP_COMMANDS_INCLUDE_H
#define MAP_COMMANDS_INCLUDE_H

#include "genesis.h"
#include "engine\map_types.h"

typedef struct
{
	const Ruby_StripMap* map;
	u8 x;		// where in the plane to draw
	u8 y;		// where in the plane to draw
	u8 mapx;	// tile map source x
	u8 mapy;	// tile map source y
	u8 width;	// the width of the map section to draw
	u8 height;  // the height of the map section to draw
} DrawMapInfo;

// [COMMAND "Draw Map" DrawMapInfo]
void DrawMap(const DrawMapInfo* drawMapInfo);

#endif