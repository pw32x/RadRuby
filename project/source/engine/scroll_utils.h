#ifndef SCROLL_UTILS_INCLUDE_H
#define SCROLL_UTILS_INCLUDE_H

#include "genesis.h"
#include "engine/base_types.h"
#include "engine/map_types.h"
#include "engine/object_types.h"

void ScrollUtils_buildColumn(u16* buffer);
void ScrollUtils_InitTilemap(void);
void ScrollUtils_InitTilemapStrip(void);

extern u16 ScrollUtils_mapColumnToBuild;


#endif