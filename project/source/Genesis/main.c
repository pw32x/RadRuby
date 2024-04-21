#include "genesis.h"
#include "..\client\exported\animations\ruby.h"
#include "..\client\exported\palettes\global_palette.h"
#include "..\client\generated\tilesets\field_tileset.h"
#include "..\engine\AnimationDraw.h"
#include "..\engine\map_types.h"

void SetupSystem() 
{
	VDP_waitVSync();
	VDP_init();
	VDP_setScreenHeight224();
	VDP_setScreenWidth320();
	VDP_setBGAAddress(0xC000);
	VDP_setBGBAddress(0xE000);
	VDP_setWindowAddress(0xB000);
	VDP_setHScrollTableAddress(0xB800);
	VDP_setSpriteListAddress(0xBC00);
	VDP_setPlaneSize(64,32, TRUE);

	//JOY_init();
	//FadeManager_Init();
	//SceneManager_Init();
	//VDP_waitVSync();

	// register 0x0b sets the scroll mode
	// first two bits sets the horizontal scroll mode (whole layer mode (0x00), tile row mode(0x02), or per-line mode(0x03))
	// third bit (0 or 1) sets the vertical scroll mode (whole layer mode or column mode)
	VDP_setReg(0x0b, 0x02);

	//SetupAudio();
}

void VDPTileManager_LoadGGAnimationToVDP(u16 region, const GGAnimation* animation, VDPTileIndex* vdpTileIndex)
{
	//*vdpTileIndex = vdpRegionTileIndex[region];
	//vdpRegionTileIndex[region] += animation->totalTiles;
	//Assert(vdpRegionTileIndex[region] < vdpRegionMaximum[region], "LoadGGAnim too many tiles loaded in vdp region");

	VDP_loadTileData(animation->allSpriteData, *vdpTileIndex, animation->totalTiles, DMA);

	VDP_waitDMACompletion();
}


void VDPTileManager_LoadTilesetDataToVDP(u16 region, const Ruby_Tileset* tileset, VDPTileIndex* vdpTileIndex)
{
	//*vdpTileIndex = vdpRegionTileIndex[region];
	//vdpRegionTileIndex[region] += tileset->numTile;
	//Assert(vdpRegionTileIndex[region] < vdpRegionMaximum[region], "LoadSpriteData too many tiles loaded in vdp region");

	VDP_loadTileData( (const u32 *)tileset->tiles, *vdpTileIndex, tileset->numTiles, DMA);
	VDP_waitDMACompletion();
}

int main(bool hardReset)
{
	PAL_setPalette(PAL0, global_palette.palette, DMA);
	VDP_waitDMACompletion();

	VDPTileIndex vdpAnimationTileIndex = 1;
	VDPTileManager_LoadGGAnimationToVDP(0, &ruby, &vdpAnimationTileIndex);

	VDPTileIndex vdpTilesetTileIndex = vdpAnimationTileIndex + ruby.totalTiles;
	VDPTileManager_LoadTilesetDataToVDP(0, &field_tileset, &vdpTilesetTileIndex);

	while (TRUE)
	{
		MyVDP_resetSprites();
		GGAnimation_Draw(128, 128, &ruby, 0, vdpAnimationTileIndex);

		MyVDP_setLastSprite();
		VDP_waitVSync();
		VDP_updateSprites(highestVDPSpriteIndex, DMA);
		SYS_doVBlankProcess();
	}

	return 0;
}