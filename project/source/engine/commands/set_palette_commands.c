#include "set_palette_commands.h"
#include "genesis.h"
#include "engine/palette_types.h"
#include "pal.h"


void SetPalette0(const Resource* resource)
{
	PaletteResource* paletteResource = (PaletteResource*)resource;
	PAL_setPalette(PAL0, paletteResource->palette, DMA);
	VDP_waitDMACompletion();
}

void SetPalette1(const Resource* resource)
{
	PaletteResource* paletteResource = (PaletteResource*)resource;
	PAL_setPalette(PAL1, paletteResource->palette, DMA);
	VDP_waitDMACompletion();
}

void SetPalette2(const Resource* resource)
{
	PaletteResource* paletteResource = (PaletteResource*)resource;
	PAL_setPalette(PAL2, paletteResource->palette, DMA);
	VDP_waitDMACompletion();
}

void SetPalette3(const Resource* resource)
{
	PaletteResource* paletteResource = (PaletteResource*)resource;
	PAL_setPalette(PAL3, paletteResource->palette, DMA);
	VDP_waitDMACompletion();
}