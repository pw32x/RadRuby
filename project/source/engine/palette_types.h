#ifndef PALETTE_TYPES_INCLUDE_H
#define PALETTE_TYPES_INCLUDE_H

#include "genesis.h"
#include "resource_types.h"

typedef struct
{
    u8 resourceType;
    const u16* palette;
} PaletteResource;

#endif