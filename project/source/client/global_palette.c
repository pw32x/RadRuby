#include "global_palette.h"

u16 global_paletteValues[16] = 
{
    0x0, 
    0x4, 
    0x400, 
    0x440, 
    0x4a, 
    0x40, 
    0x40e, 
    0xe4a, 
    0xea4, 
    0x4ae, 
    0xaa4, 
    0xa0, 
    0xaae, 
    0xeaa, 
    0x4ee, 
    0xeee, 
};
const PaletteResource global_palette = 
{
    PALETTE_RESOURCE_TYPE, 
    global_paletteValues,
};
