#include "set_palette_commands.h"
#include "engine/palette_types.h"



void SetBackgroundPalette(const Resource* resource)
{
	PaletteResource* paletteResource = (PaletteResource*)resource;
	SMS_loadBGPalette(paletteResource->palette);
}

void SetSpritePalette(const Resource* resource)
{
	PaletteResource* paletteResource = (PaletteResource*)resource;
	SMS_loadSpritePalette(paletteResource->palette);
}